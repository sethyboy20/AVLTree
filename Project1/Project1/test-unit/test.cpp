//#include "../src/main.cpp"
#define CATCH_CONFIG_MAIN
#include "../src/AVLTree.cpp"
#include "../src/AVLTree.h"
#include "catch.hpp"

/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

TEST_CASE("Left Right Rotation", "[flag]"){
	
		AVLTree tree;
		tree.insert("Jack", 12324534);
		tree.insert("Brian", 3434535);
		tree.insert("Cam", 10565656);
		tree.insert("Seth", 1000132);
		tree.insert("Mary", 2976464);
		std::vector<std::string> actualOutput = tree.inorder();
		std::vector<std::string> expectedOutput = {"Seth", "Mary", "Brian", "Cam", "Jack"};

	REQUIRE(expectedOutput.size() == actualOutput.size());
	REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("Right Left Rotation", "[flag]"){
	
		AVLTree tree;
		tree.insert("Seth", 1000132);
		tree.insert("Brian", 3434535);
		tree.insert("Mary", 2976464);
		tree.insert("Jack", 12324534);
		tree.insert("Cam", 10565656);
		
		std::vector<std::string> actualOutput = tree.inorder();
		std::vector<std::string> expectedOutput = {"Seth", "Mary", "Brian", "Cam", "Jack"};

	REQUIRE(expectedOutput.size() == actualOutput.size());
	REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("Adding/Removing 1,000 Nodes", "[flag]"){
	
		AVLTree tree;
		for (int i = 1; i < 1001; i++)
			tree.insert("A", i);
		
		for (int i = 999; i >= 0; i--)
			tree.removeInorder(i);

		std::vector<std::string> actualOutput = tree.inorder();
		std::vector<std::string> expectedOutput = {};

	REQUIRE(expectedOutput.size() == actualOutput.size());
	REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("Checking/Removing Root Node", "[flag]"){
	
		AVLTree tree;
		tree.insert("Jack", 12324534);
		tree.insert("Brian", 3434535);
		tree.insert("Cam", 10565656);
		tree.insert("Seth", 1000132);
		tree.insert("Mary", 2976464);
		tree.insert("Joseph", 42424256);
		tree.insert("Paul", 842);
		tree.insert("Debra", 31314535);
		tree.insert("Steve", 32);
		tree.insert("Mark", 182356);

		REQUIRE(tree.getRoot()->student.getID() == 10565656);
		tree.remove(10565656);
		REQUIRE(tree.getRoot()->student.getID() == 12324534);
		std::vector<std::string> actualOutput = tree.inorder();
		std::vector<std::string> expectedOutput = {"Steve", "Paul", "Mark", "Seth", "Mary", "Brian", "Jack", "Debra", "Joseph"};

		REQUIRE(expectedOutput.size() == actualOutput.size());
		REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("Reading Insert Commands", "[flag]"){
	
		AVLTree tree;
		std::string dummy;
		std::string name;
		std::string tempID;
		unsigned int gatorID;
		std::vector<std::string> commands;
		commands.push_back("insert \"Dom\" 83131443");
		commands.push_back("insert \"Miss Sophia Catarina Melina Freschetta the Third\" 42424212");
		commands.push_back("insert \"Tommy\" -42445353");
		commands.push_back("insert Dave 32334222");
		commands.push_back("insert \"Gary\" 0");
		std::vector<bool> success = {true, true, true, true, true};

		for (int i = 0; i < commands.size(); i++) {
			try {
				std::istringstream stream(commands[i]);
				getline(stream, dummy, ' ');
				getline(stream, dummy, '"');
				getline(stream, name, '"');
				getline(stream, dummy, ' ');
				getline(stream, tempID);

				// Names must contain only A-Z, a-z or spaces
				for (int i = 0; i < name.size(); i++) {
					if (name[i] != ' ' && (name[i] < 'A' || name[i] > 'Z') && (name[i] < 'a' || name[i] > 'z')) {
						throw std::runtime_error("unsuccessful");
						break;
					}
				}

				// UF Gator IDs must be of length 8
				if (tempID.size() != 8)
					throw std::runtime_error("unsuccessful");

				// Convert ID to integer
				gatorID = std::stoi(tempID);

				// Insert element into the tree
				tree.insert(name, gatorID);
			}
			catch (std::invalid_argument excpt) {
				success[i] = false;
				std::cout << "unsuccessful" << std::endl;
			}
			catch (std::out_of_range excpt) {
				success[i] = false;
				std::cout << "unsuccessful" << std::endl;
			}
			catch (std::runtime_error excpt) {
				success[i] = false;
				std::cout << excpt.what() << std::endl;
			}	
		}

		REQUIRE(success[0] == true);
		REQUIRE(success[1] == true);
		REQUIRE(success[2] == false);
		REQUIRE(success[3] == false);
		REQUIRE(success[4] == false);
}

