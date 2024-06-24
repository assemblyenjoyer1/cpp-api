#include "utils.h"

std::string api::convert_vector_to_json(std::vector<std::unordered_map<std::string, std::string>> vector)
{
    nlohmann::json j;

    for (const auto &entry : vector)
    {
        nlohmann::json entry_json;

        for (const auto &pair : entry)
        {
            entry_json[pair.first] = pair.second;
        }

        j.push_back(entry_json);
    }

    return j.dump();
}

std::string status_code_to_string(api::status_code status)
{
    switch (status)
    {
    case api::status_code::OK:
        return "200 OK";
    case api::status_code::ERROR:
        return "400 ERROR";
    case api::status_code::NOT_FOUND:
        return "404 NOT FOUND";
    case api::status_code::UNAUTHORIZED:
        return "401 UNAUTHORIZED";
    default:
        return "UNKNOWN";
    }
}

std::string content_type_to_string(api::content_type type)
{
    switch (type)
    {
    case api::content_type::PLAIN:
        return "text/plain";
    case api::content_type::HTML:
        return "text/html";
    default:
        return "UNKOWN";
    }
}

std::string api::create_response(const status_code &status, const std::string &body, const content_type &type)
{
    std::string status_str = status_code_to_string(status);
    std::string content_type_str = content_type_to_string(type);

    std::string response = "HTTP/1.1 " + status_str + "\r\n";
    response += "Content-Type: " + content_type_str + "\r\n";
    response += "Content-Length: " + std::to_string(body.length()) + "\r\n";
    response += "\r\n" + body;
    return response;
}