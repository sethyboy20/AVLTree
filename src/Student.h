#pragma once
#include <string>
class Student {
    std::string name;
    unsigned int gatorID;
    public:
        Student() {
            name = "";
            gatorID = 0;
        }
        Student(std::string name, unsigned int gatorID) {
            this->name = name;
            this->gatorID = gatorID;
        }
        void setName(std::string name) {
            this->name = name;
        }
        std::string getName() {
            return name;
        }
        void setID(unsigned int gatorID) {
            this->gatorID = gatorID;
        }
        int getID() {
            return gatorID;
        }
};