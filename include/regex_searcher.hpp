#pragma once

#include <string>
#include <vector>
#include <boost/regex.hpp>

namespace regex_tools {

class RegexSearcher {
public:
    /**
     * @brief Construct a new Regex Searcher object with a regex pattern
     * 
     * @param pattern The regex pattern to search for
     */
    explicit RegexSearcher(const std::string& pattern);

    /**
     * @brief Find all matches of the pattern in the text
     * 
     * @param text The text to search in
     * @return std::vector<std::string> List of matched strings
     */
    std::vector<std::string> findAll(const std::string& text) const;

    /**
     * @brief Find first match of the pattern in the text
     * 
     * @param text The text to search in
     * @return std::string The first match or empty string if no match
     */
    std::string findFirst(const std::string& text) const;

    /**
     * @brief Replace all occurrences of the pattern with replacement text
     * 
     * @param text The text to search in
     * @param replacement The replacement text
     * @return std::string The text with replacements
     */
    std::string replaceAll(const std::string& text, const std::string& replacement) const;

    /**
     * @brief Check if the pattern matches the entire text
     * 
     * @param text The text to match against
     * @return true If the pattern matches the entire text
     * @return false If the pattern does not match the entire text
     */
    bool matchesEntire(const std::string& text) const;

    /**
     * @brief Set a new pattern for the searcher
     * 
     * @param pattern The new regex pattern
     */
    void setPattern(const std::string& pattern);

    /**
     * @brief Get the current pattern
     * 
     * @return std::string The current regex pattern
     */
    std::string getPattern() const;

private:
    boost::regex pattern_;
    std::string pattern_str_;
};

} // namespace regex_tools
