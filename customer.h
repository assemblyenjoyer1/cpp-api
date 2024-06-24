#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Customer {
public:
    Customer(const std::string& name, const std::string& contact_person, int phone_number)
        : name(name), contact_person(contact_person), phone_number(phone_number) {}

    std::string name;
    std::string contact_person;
    int phone_number;

    json toJson() const {
        json j;
        j["name"] = name;
        j["contact_person"] = contact_person;
        j["phone_number"] = phone_number;
        return j;
    }
};

#endif
