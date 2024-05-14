## AVL Tree
A program that stores data using an AVL binary search tree.

## Usage
Run ```make run``` to build and start the program.

Valid commands:

```insert "<name>" <id>```: Insert an entry onto the tree

Ex: ```insert "Seth" 12345678```

```remove <id>```: Remove an entry from the tree

Ex:  ```remove 12345678```

```search <id>```: Search an entry by ID
```search <name>```: Search an entry by name

Ex: ```search <id>```, ```search "Seth"```

```printInorder```: Print the tree entries using an in-order traversal.

```printPreorder```: Print the tree entries using an pre-order traversal.

```printPostorder```: Print the tree entries using an post-order traversal.

```printLevelCount```: Print the nubmer of levels of the tree.

```removeInOrder <num>```: Remove an element by its in-order position

Ex: ```removeInOrder 3```

Run ```make test``` to perform the program's unit tests.
