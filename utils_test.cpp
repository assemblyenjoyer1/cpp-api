#include <gtest/gtest.h>
#include "utils.h"
#include <sstream>

TEST(utils, convert_vector_to_json)
{
    std::string key1 = "foo";
    std::string value1 = "bar";
    std::string key2 = "schluessel";
    std::string value2 = "wert";
    std::string key3 = "testkey";
    std::string value3 = "testvalue";
    std::string key4 = "bar";
    std::string value4 = "foo";

    std::vector<std::unordered_map<std::string, std::string>> input_vector = {
        {{key1, value1}, {key2, value2}},
        {{key3, value3}, {key4, value4}}};

    nlohmann::json expected_json_array = nlohmann::json::array();
    nlohmann::json entry1 = { {key1, value1}, {key2, value2} };
    nlohmann::json entry2 = { {key3, value3}, {key4, value4} };
    expected_json_array.push_back(entry1);
    expected_json_array.push_back(entry2);
    std::string expected = expected_json_array.dump();
    
    std::string result = api::convert_vector_to_json(input_vector);

    EXPECT_EQ(result, expected);
}