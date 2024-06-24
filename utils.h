#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <unordered_map>

namespace api
{
    std::string convert_vector_to_json(std::vector<std::unordered_map<std::string, std::string>> vector);
}