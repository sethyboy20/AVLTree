#pragma once
#include "TreeNode.h"
#include <vector>

class AVLTree {
    unsigned int numOfNodes = 0;
    TreeNode* root = nullptr;
    TreeNode* insertHelper(TreeNode* root, std::string name, unsigned int gatorID, bool& inserted);
    TreeNode* rotateHelper();
    TreeNode* removeHelper(TreeNode* root, unsigned int gatorID);
    void searchHelper(TreeNode* root, unsigned int gatorID);
    void searchHelper(TreeNode* root, std::string name, bool& found);
    int getHeight(TreeNode* root);
    int getBalFactor(TreeNode* root);
    TreeNode* rotateLeft(TreeNode* node);
    TreeNode* rotateRight(TreeNode* node);
    TreeNode* getmin(TreeNode* root);
    TreeNode* deletemin(TreeNode* root);
    void printInorderHelper(TreeNode* root, int& count);
    void printPreorderHelper(TreeNode* root, int& count);
    void printPostorderHelper(TreeNode* root, int& count);
    void inorderTraverseHelper(TreeNode* root, TreeNode*& newNode, int N, int& count);
    void inorderHelper(TreeNode* root, std::vector<std::string>& names); // FOR UNIT TESTING
    public:
        void insert(std::string name, unsigned int gatorID);
        void remove(unsigned int gatorID);
        void search(unsigned int gatorID);
        void search(std::string name);
        void printInorder();
        void printPreorder();
        void printPostorder();
        void printLevelCount();
        void removeInorder(int N);
        std::vector<std::string> inorder(); // FOR UNIT TESTING
        TreeNode* getRoot(); // FOR UNIT TESTING
};