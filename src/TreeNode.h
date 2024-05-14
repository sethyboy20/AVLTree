#pragma once
#include "Student.h"
class TreeNode {
    public:
        Student student;
        int height = 1;
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;
        TreeNode(std::string name, unsigned int gatorID) {
            student = Student(name, gatorID);
        }
};