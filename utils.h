#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <fstream>
#include <iostream>

namespace api
{
    enum class status_code
    {
        OK,
        ERROR,
        NOT_FOUND,
        UNAUTHORIZED
    };

        enum class content_type {
        PLAIN,
        HTML
    };

    std::string convert_vector_to_json(std::vector<std::unordered_map<std::string, std::string>> vector);
    std::string create_response(const status_code &status, const std::string &body, const content_type &type);
    std::string read_file_to_string(const std::string& file_path);
}