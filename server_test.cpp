#include <gtest/gtest.h>
#include "server.h"
#include <iostream>
#include <sstream>

TEST(server, get_response_for_test)
{
    const std::string expectedBody = "Hello this is a test endpoint!";
    const std::string expectedResponse = api::create_response(api::status_code::OK, expectedBody, api::content_type::PLAIN);
    
    const std::string result = get_response_for_test();
    
    EXPECT_EQ(result, expectedResponse);
}

TEST(server, get_response_for_404)
{
    const std::string expectedBody = "404 Not Found. Endpoint does not exist.";
    const std::string expectedResponse = api::create_response(api::status_code::NOT_FOUND, expectedBody, api::content_type::PLAIN);
    
    const std::string result = get_response_for_404();

    EXPECT_EQ(result, expectedResponse);
}


