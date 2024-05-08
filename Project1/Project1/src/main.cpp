#include <iostream>
#include <string>
#include <sstream>
#include "AVLTree.h"
/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

int main() {
	AVLTree tree; // Create tree
	int numCommands = 0;
	// Get number of commands; if < 0, terminate
	std::string command;
	getline(std::cin, command);
	try  {
		numCommands = std::stoi(command);
		if (numCommands < 1)
			throw std::runtime_error("unsuccessful");
	}
	catch (std::invalid_argument excpt) {
		std::cout << "unsuccessful" << std::endl;
	}
	catch (std::out_of_range excpt) {
		std::cout << "unsuccessful" << std::endl;
	}
	catch (std::runtime_error excpt) {
		std::cout << excpt.what() << std::endl;
	}

	for (int i = 0; i < numCommands; i++) {
		try {
			// Get next command line
			getline(std::cin, command);
			std::istringstream stream(command);
			
			// Get action from command line
			std::string action;
			getline(stream, action, ' ');

			if (action == "insert") { // Insert element into tree
				std::string dummy;
				std::string name;
				std::string tempID;
				unsigned int gatorID;

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
			else if (action == "remove") { // Remove element from tree
				std::string tempID;
				unsigned int gatorID;

				getline(stream, tempID);

				// UF Gator IDs must be of length 8
				if (tempID.size() != 8)
					throw std::runtime_error("unsuccessful");

				// Convert ID to integer
				gatorID = std::stoi(tempID);

				// Remove the element from the tree
				tree.remove(gatorID);
			}
			else if (action == "search") { // Search element in the tree
				std::string dummy;
				std::string query;
				unsigned int gatorID;
				getline(stream, dummy, '"');

				if (dummy != "") { // If no quotations, assume query is an ID
					// Search by UF Gator ID (integer)
					query = dummy;

					// UF Gator IDs must be of length 8
					if (query.size() != 8)
						throw std::runtime_error("unsuccessful");

					gatorID = std::stoi(query);

					tree.search(gatorID);
				}
				else { // Search by name (string)
					getline(stream, query, '"');

					// Names must contain only A-Z, a-z or spaces
					for (int i = 0; i < query.size(); i++) {
						if (query[i] != ' ' && (query[i] < 'A' || query[i] > 'Z') && (query[i] < 'a' || query[i] > 'z')) {
							throw std::runtime_error("unsuccessful");
							break;
						}
					}

					tree.search(query);
				}
			}
			else if (action == "printInorder") // Print inorder traversal
				tree.printInorder();
			else if (action == "printPreorder") // Print preorder traversal
				tree.printPreorder();
			else if (action == "printPostorder") // Print postorder traversal
				tree.printPostorder();
			else if (action == "printLevelCount") // Print level count/height of tree
				tree.printLevelCount();
			else if (action == "removeInorder") { // Remove an element by its in order position
				std::string tempN;
				int N;

				getline(stream, tempN);

				// Get the desired position to check
				N = std::stoi(tempN);

				// Remove the desired element from the tree
				tree.removeInorder(N);
			}
			else
				std::cout << "unsuccessful" << std::endl;
		}
		catch (std::invalid_argument excpt) {
			std::cout << "unsuccessful" << std::endl;
		}
		catch (std::out_of_range excpt) {
			std::cout << "unsuccessful" << std::endl;
		}
		catch (std::runtime_error excpt) {
			std::cout << excpt.what() << std::endl;
		}	
	}

    return 0;
}