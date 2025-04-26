#include "regex_searcher.hpp"
#include <boost/algorithm/string.hpp>

namespace regex_tools {

RegexSearcher::RegexSearcher(const std::string& pattern) 
    : pattern_(pattern), pattern_str_(pattern) {
}

std::vector<std::string> RegexSearcher::findAll(const std::string& text) const {
    std::vector<std::string> results;
    boost::regex_iterator<std::string::const_iterator> it(text.begin(), text.end(), pattern_);
    boost::regex_iterator<std::string::const_iterator> end;
    
    while (it != end) {
        results.push_back(it->str());
        ++it;
    }
    
    return results;
}

std::string RegexSearcher::findFirst(const std::string& text) const {
    boost::smatch match;
    if (boost::regex_search(text, match, pattern_)) {
        return match.str();
    }
    return "";
}

std::string RegexSearcher::replaceAll(const std::string& text, const std::string& replacement) const {
    return boost::regex_replace(text, pattern_, replacement);
}

bool RegexSearcher::matchesEntire(const std::string& text) const {
    return boost::regex_match(text, pattern_);
}

void RegexSearcher::setPattern(const std::string& pattern) {
    pattern_str_ = pattern;
    pattern_ = boost::regex(pattern);
}

std::string RegexSearcher::getPattern() const {
    return pattern_str_;
}

} // namespace regex_tools
