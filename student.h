#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Student {
public:
    Student(const std::string& name, int age, const std::string& school)
        : name(name), age(age), school(school) {}

    std::string name;
    int age;
    std::string school;

    json toJson() const {
        json j;
        j["name"] = name;
        j["age"] = age;
        j["school"] = school;
        return j;
    }
};

#endif
