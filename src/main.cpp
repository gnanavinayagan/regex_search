#include "regex_searcher.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

void printHelp() {
    std::cout << "Regex Search Tool - A utility for regex searching using Boost" << std::endl;
    std::cout << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "  regex_search [command] [pattern] [text]" << std::endl;
    std::cout << "  regex_search [command] [pattern] -f [filename]" << std::endl;
    std::cout << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  find     - Find all matches of pattern in text" << std::endl;
    std::cout << "  first    - Find first match of pattern in text" << std::endl;
    std::cout << "  replace  - Replace all occurrences of pattern with text" << std::endl;
    std::cout << "  match    - Check if pattern matches entire text" << std::endl;
    std::cout << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "  regex_search find \"\\d+\" \"abc123def456\"" << std::endl;
    std::cout << "  regex_search replace \"(\\d+)\" \"num=$1\" \"abc123def456\"" << std::endl;
    std::cout << "  regex_search find \"\\w+\" -f input.txt" << std::endl;
}

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return "";
    }
    
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    return content;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printHelp();
        return 1;
    }

    std::string command = argv[1];
    
    if (command == "--help" || command == "-h") {
        printHelp();
        return 0;
    }
    
    if (argc < 4) {
        std::cerr << "Error: Not enough arguments" << std::endl;
        printHelp();
        return 1;
    }
    
    std::string pattern = argv[2];
    std::string text;
    
    // Check if input is from a file
    if (std::string(argv[3]) == "-f") {
        if (argc < 5) {
            std::cerr << "Error: Missing filename" << std::endl;
            return 1;
        }
        text = readFile(argv[4]);
        if (text.empty()) {
            return 1;
        }
    } else {
        text = argv[3];
        
        // If command is replace, we need one more argument
        if (command == "replace" && argc < 5) {
            std::cerr << "Error: Missing replacement text" << std::endl;
            return 1;
        }
    }
    
    try {
        regex_tools::RegexSearcher searcher(pattern);
        
        if (command == "find") {
            auto results = searcher.findAll(text);
            std::cout << "Found " << results.size() << " matches:" << std::endl;
            for (const auto& match : results) {
                std::cout << "  " << match << std::endl;
            }
        } else if (command == "first") {
            auto result = searcher.findFirst(text);
            if (!result.empty()) {
                std::cout << "First match: " << result << std::endl;
            } else {
                std::cout << "No match found" << std::endl;
            }
        } else if (command == "replace") {
            std::string replacement = argv[4];
            std::string result = searcher.replaceAll(text, replacement);
            std::cout << "Result: " << result << std::endl;
        } else if (command == "match") {
            bool matches = searcher.matchesEntire(text);
            std::cout << "Pattern " << (matches ? "matches" : "does not match") << " the entire text" << std::endl;
        } else {
            std::cerr << "Error: Unknown command '" << command << "'" << std::endl;
            printHelp();
            return 1;
        }
    } catch (const boost::regex_error& e) {
        std::cerr << "Regex error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
