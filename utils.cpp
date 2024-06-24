#include "utils.h"


std::string api::convert_vector_to_json(std::vector<std::unordered_map<std::string, std::string>> vector) {
    nlohmann::json j;

    for (const auto& entry : vector) {
        nlohmann::json entry_json;

        for (const auto& pair : entry) {
            entry_json[pair.first] = pair.second;
        }

        j.push_back(entry_json);
    }

    return j.dump();
}