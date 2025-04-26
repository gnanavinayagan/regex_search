#define BOOST_TEST_MODULE RegexSearcherTest
#include <boost/test/included/unit_test.hpp>
#include "regex_searcher.hpp"

BOOST_AUTO_TEST_CASE(test_find_all) {
    regex_tools::RegexSearcher searcher("\\d+");
    std::string text = "abc123def456ghi";
    auto results = searcher.findAll(text);
    
    BOOST_REQUIRE_EQUAL(results.size(), 2);
    BOOST_CHECK_EQUAL(results[0], "123");
    BOOST_CHECK_EQUAL(results[1], "456");
}

BOOST_AUTO_TEST_CASE(test_find_first) {
    regex_tools::RegexSearcher searcher("\\d+");
    std::string text = "abc123def456ghi";
    auto result = searcher.findFirst(text);
    
    BOOST_CHECK_EQUAL(result, "123");
}

BOOST_AUTO_TEST_CASE(test_find_no_match) {
    regex_tools::RegexSearcher searcher("\\d+");
    std::string text = "abcdefghi";
    auto results = searcher.findAll(text);
    
    BOOST_CHECK(results.empty());
    BOOST_CHECK_EQUAL(searcher.findFirst(text), "");
}

BOOST_AUTO_TEST_CASE(test_replace_all) {
    regex_tools::RegexSearcher searcher("\\d+");
    std::string text = "abc123def456ghi";
    auto result = searcher.replaceAll(text, "NUM");
    
    BOOST_CHECK_EQUAL(result, "abcNUMdefNUMghi");
}

BOOST_AUTO_TEST_CASE(test_matches_entire) {
    regex_tools::RegexSearcher searcher("\\d+");
    
    BOOST_CHECK(searcher.matchesEntire("123"));
    BOOST_CHECK(!searcher.matchesEntire("abc123"));
    BOOST_CHECK(!searcher.matchesEntire("123abc"));
}

BOOST_AUTO_TEST_CASE(test_set_get_pattern) {
    regex_tools::RegexSearcher searcher("\\d+");
    BOOST_CHECK_EQUAL(searcher.getPattern(), "\\d+");
    
    searcher.setPattern("\\w+");
    BOOST_CHECK_EQUAL(searcher.getPattern(), "\\w+");
    
    // Test with new pattern
    std::string text = "abc123def";
    auto results = searcher.findAll(text);
    BOOST_REQUIRE_EQUAL(results.size(), 1);
    BOOST_CHECK_EQUAL(results[0], "abc123def");
}

BOOST_AUTO_TEST_CASE(test_complex_pattern) {
    regex_tools::RegexSearcher searcher("(\\w+)=(\\d+)");
    std::string text = "key1=123 key2=456 key3=789";
    auto results = searcher.findAll(text);
    
    BOOST_REQUIRE_EQUAL(results.size(), 3);
    BOOST_CHECK_EQUAL(results[0], "key1=123");
    BOOST_CHECK_EQUAL(results[1], "key2=456");
    BOOST_CHECK_EQUAL(results[2], "key3=789");
    
    auto result = searcher.replaceAll(text, "$1->$2");
    BOOST_CHECK_EQUAL(result, "key1->123 key2->456 key3->789");
}
