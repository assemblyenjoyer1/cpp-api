#include <gtest/gtest.h>
#include "server.h"
#include <iostream>

TEST(server, get_response_for_test)
{
    std::string expectedBody = "Hello this is a test endpoint!";
    std::string expectedResponse = create_response("200 OK", expectedBody);
    std::string result = get_response_for_test();
    EXPECT_EQ(result, expectedResponse);
}
