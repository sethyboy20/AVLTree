#include <iostream>
#include "AVLTree.h"

void AVLTree::insert(std::string name, unsigned int gatorID) { // Insert element
    bool inserted = false;
    root = insertHelper(root, name, gatorID, inserted);

    if (!inserted)
        std::cout << "unsuccessful" << std::endl;
}

TreeNode* AVLTree::insertHelper(TreeNode* root, std::string name, unsigned int gatorID, bool& inserted) {
    if (root == nullptr) { // Place the node once the desired spot is reached
        std::cout << "successful" << std::endl;
        inserted = true;
        numOfNodes++;
        return new TreeNode(name, gatorID);
    }
    else if (gatorID < root->student.getID()) // If ID is less, move to the left side
        root->left = insertHelper(root->left, name, gatorID, inserted);
    else if (gatorID > root->student.getID()) // If ID is greater, move to the right side
        root->right = insertHelper(root->right, name, gatorID, inserted);
    else // Otherwise, return the root
        return root;

    // Set height and balance factor of node
    root->height = getHeight(root);
    int balFactor = getBalFactor(root);

    // Determine the node rotation needed (if any) from balance factor & node placement

    // Left-left imbalance: right rotation
	if (balFactor > 1 && gatorID < root->left->student.getID())
		return rotateRight(root);

	// Right-right imbalance: left rotation
	if (balFactor < -1 && gatorID > root->right->student.getID())
		return rotateLeft(root);

	// Left-right imbalance: left-right rotation
	if (balFactor > 1 && gatorID > root->left->student.getID()) {
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}

	// Right-left imbalance: right-left rotation
	if (balFactor < -1 && gatorID < root->right->student.getID()) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}

	return root;
}

int AVLTree::getBalFactor(TreeNode* root) {
	if (root == nullptr)
		return 0;
	return getHeight(root->left) - getHeight(root->right);
}

int AVLTree::getHeight(TreeNode* root) {
    if (root == nullptr)
        return 0;
    return 1 + std::max(getHeight(root->left), getHeight(root->right));
}

TreeNode* AVLTree::rotateLeft(TreeNode *node)
{
    TreeNode* newTop = node->right;
    TreeNode* temp = newTop->left;
    newTop->left = node;
    node->right = temp;
    return newTop;
}

TreeNode* AVLTree::rotateRight(TreeNode* node)
{
    TreeNode* newTop = node->left;
    TreeNode* temp = newTop->right;
    newTop->right = node;
    node->left = temp;
    return newTop;
}

void AVLTree::remove(unsigned int gatorID) { // Remove node from tree
    root = removeHelper(root, gatorID);
}

TreeNode* AVLTree::removeHelper(TreeNode* root, unsigned int gatorID) {
    if (root == nullptr) { // Node not found
        std::cout << "unsuccessful" << std::endl;
        return nullptr;
    }
    if (gatorID < root->student.getID()) // If ID is less, move to the left side
        root->left = removeHelper(root->left, gatorID);
    else if (gatorID > root->student.getID()) // If ID is greater, move to the right side
        root->right = removeHelper(root->right, gatorID); 
    else { // Node found
        if (root->left == nullptr) { // If node has no children/only right child
            std::cout << "successful" << std::endl;
            numOfNodes--;
            return root->right;
        }
        else if (root->right == nullptr) { // If node has only left child
            std::cout << "successful" << std::endl;
            numOfNodes--;
            return root->left;
        }
        else { // If node has both children
            // Get the inorder successor of the node and move its data to the "removed" node
            TreeNode* temp = getmin(root->right);
            root->student.setName(temp->student.getName());
            root->student.setID(temp->student.getID());

            // Delete the original inorder successor
            root->right = deletemin(root->right);
            std::cout << "successful" << std::endl;
            numOfNodes--;
        }
    }
    return root;
}

TreeNode* AVLTree::getmin(TreeNode* root) {
    // Removal helper function: find the inorder successor of node to be removed
    if (root->left == nullptr)
        return root;
    return getmin(root->left);
}

TreeNode* AVLTree::deletemin(TreeNode* root) {
    // Removal helper function: delete the original inorder successor
    if (root->left == nullptr)
        return root->right;
    root->left = deletemin(root->left);
    return root;
}

void AVLTree::search(unsigned int gatorID) { // Search by Gator ID (integer)
    searchHelper(root, gatorID);
}

void AVLTree::searchHelper(TreeNode* root, unsigned int gatorID) { // Search by Gator ID (integer)
    if (root == nullptr) // If ID not found
        std::cout << "unsuccessful" << std::endl;
    else if (gatorID < root->student.getID()) // If ID is less, move to the left side
        searchHelper(root->left, gatorID);
    else if (gatorID > root->student.getID()) // If ID is greater, move to the right side
        searchHelper(root->right, gatorID);
    else // If ID found
        std::cout << root->student.getName() << std::endl;
}

void AVLTree::search(std::string name) { // Search by name (string)
    bool found = false;
    searchHelper(root, name, found);
    if (!found)
        std::cout << "unsuccessful" << std::endl;
}

void AVLTree::searchHelper(TreeNode* root, std::string name, bool& found) { // Search by name (string)
    // Preorder traversal (Node, Left, Right)
    if (root == nullptr)
        return;
    else {
        // If name is found, print the corresponding ID
        if (name == root->student.getName()) {
            found = true;
            std::string printID = std::to_string(root->student.getID());

            // Add leading zeroes for ID number < 10,000,000
            if (printID.size() < 8) {
                for (int i = 0; i < 8 - printID.size(); i++)
                    std::cout << "0";
            }

            std::cout << printID << std::endl;
        }
        searchHelper(root->left, name, found);
        searchHelper(root->right, name, found);
    }
}

void AVLTree::printInorder() {
    // Print names in inorder traversal (Left, Node, Right)
    int count = 0;
    printInorderHelper(root, count);
    std::cout << std::endl;
}

void AVLTree::printInorderHelper(TreeNode* root, int& count) {
    if (root == nullptr)
        return;
    else {
        printInorderHelper(root->left, count);
        std::cout << root->student.getName();
        count++;
        if (count < numOfNodes)
            std::cout << ", ";
        printInorderHelper(root->right, count);
    }
}

void AVLTree::printPreorder() {
    // Print names in preorder traversal (Node, Left, Right)
    int count = 0;
    printPreorderHelper(root, count);
    std::cout << std::endl;
}

void AVLTree::printPreorderHelper(TreeNode* root, int& count) {
    if (root == nullptr)
        return;
    else {
        std::cout << root->student.getName();
        count++;
        if (count < numOfNodes)
            std::cout << ", ";
        printPreorderHelper(root->left, count);
        printPreorderHelper(root->right, count);
    }
}

void AVLTree::printPostorder() {
    // Print names in postorder traversal (Left, Right, Node)
    int count = 0;
    printPostorderHelper(root, count);
    std::cout << std::endl;
}

void AVLTree::printPostorderHelper(TreeNode* root, int& count) {
    if (root == nullptr)
        return;
    else {
        printPostorderHelper(root->left, count);
        printPostorderHelper(root->right, count);
        std::cout << root->student.getName();
        count++;
        if (count < numOfNodes)
            std::cout << ", ";
    }
}

void AVLTree::printLevelCount() {
    // Print level count/height of tree
    std::cout << getHeight(root) << std::endl;
}

void AVLTree::removeInorder(int N) {
    int count = -1;
    TreeNode* newNode = nullptr;
    
    // Traverse the tree in order to find the node position
    inorderTraverseHelper(root, newNode, N, count);

    if (newNode == nullptr) { // If node does not exist
        std::cout << "unsuccessful" << std::endl;
    }
    else { // Otherwise, begin the removal process
        root = removeHelper(root, newNode->student.getID());
    }
}

void AVLTree::inorderTraverseHelper(TreeNode* root, TreeNode*& newNode, int N, int& count) {
    if (root == nullptr)
        return;
    else {
        inorderTraverseHelper(root->left, newNode, N, count);
        // Increase the count for each node encountered
        count++;
        // Once N is reached, set the pointer to node to be removed
        if (count == N) {
            newNode = root;
        }
        inorderTraverseHelper(root->right, newNode, N, count);
    }
}

// FOR UNIT TESTING
std::vector<std::string> AVLTree::inorder() {
    std::vector<std::string> names;

    inorderHelper(root, names);

    return names;
}

// FOR UNIT TESTING
void AVLTree::inorderHelper(TreeNode* root, std::vector<std::string>& names) {
    if (root == nullptr)
        return;
    else {
        inorderHelper(root->left, names);
        names.push_back(root->student.getName());
        inorderHelper(root->right, names);
    }
}

// FOR UNIT TESTING
TreeNode* AVLTree::getRoot() {
    return root;
}