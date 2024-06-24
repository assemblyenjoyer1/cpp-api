#include <gtest/gtest.h>
#include "server.h"
#include <iostream>
#include <sstream>

TEST(server, get_response_for_test)
{
    const std::string expectedBody = "Hello this is a test endpoint!";
    const std::string expectedResponse = create_response("200 OK", expectedBody);
    
    const std::string result = get_response_for_test();
    
    EXPECT_EQ(result, expectedResponse);
}

TEST(server, get_response_for_404)
{
    const std::string expectedBody = "404 Not Found. Endpoint does not exist.";
    const std::string expectedResponse = create_response("404 Not Found", expectedBody);
    
    const std::string result = get_response_for_404();

    EXPECT_EQ(result, expectedResponse);
}

TEST(server, create_response)
{
    const std::string status = "200 OK";
    const std::string body = "I am a test body";
    std::ostringstream responseSS;
    responseSS << "HTTP/1.1 " << status << "\r\n"
    << "Content-Type: text/plain\r\n"
    << "Content-Length: " << body.length() << "\r\n"
    << "\r\n" << body;
    const std::string expectedResponse = responseSS.str();

    const std::string result = create_response(status, body);

    EXPECT_EQ(result, expectedResponse);
}
