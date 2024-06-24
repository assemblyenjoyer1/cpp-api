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

TEST(utils, create_response_200_plain)
{
    const std::string status = "200 OK";
    const std::string body = "I am a test body";
    std::ostringstream responseSS;
    responseSS << "HTTP/1.1 " << status << "\r\n"
    << "Content-Type: text/plain\r\n"
    << "Content-Length: " << body.length() << "\r\n"
    << "\r\n" << body;
    const std::string expectedResponse = responseSS.str();

    const std::string result = api::create_response(api::status_code::OK, body, api::content_type::PLAIN);

    EXPECT_EQ(result, expectedResponse);
}

TEST(utils, create_response_404_plain)
{
    const std::string status = "404 NOT FOUND";
    const std::string body = "I am a test body";
    std::ostringstream responseSS;
    responseSS << "HTTP/1.1 " << status << "\r\n"
    << "Content-Type: text/plain\r\n"
    << "Content-Length: " << body.length() << "\r\n"
    << "\r\n" << body;
    const std::string expectedResponse = responseSS.str();

    const std::string result = api::create_response(api::status_code::NOT_FOUND, body, api::content_type::PLAIN);

    EXPECT_EQ(result, expectedResponse);
}

TEST(utils, create_response_200_html)
{
    const std::string status = "200 OK";
    const std::string body = "I am a test body";
    std::ostringstream responseSS;
    responseSS << "HTTP/1.1 " << status << "\r\n"
    << "Content-Type: text/html\r\n"
    << "Content-Length: " << body.length() << "\r\n"
    << "\r\n" << body;
    const std::string expectedResponse = responseSS.str();

    const std::string result = api::create_response(api::status_code::OK, body, api::content_type::HTML);

    EXPECT_EQ(result, expectedResponse);
}