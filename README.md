# Binary-search-tree
A binary search tree (BST) is a binary tree data structure in which each node has at most two child nodes, and the values of the nodes on the left subtree are less than or equal to the value of the parent node, while the values of the nodes on the right subtree are greater than or equal to the value of the parent node.

This ordering property makes it efficient to perform operations such as searching, inserting, and deleting elements in the tree. To search for a value in a BST, we start at the root node and compare the value to be searched with the value of the current node. If the value matches, the search is successful. If the value is less than the current node value, we move to the left subtree, otherwise we move to the right subtree. We repeat this process until we either find the value or reach a leaf node, indicating that the value is not present in the tree.

BSTs have a number of applications in computer science, including in databases, compilers, and as the underlying data structure for many algorithms. They have a worst-case time complexity of O(n) for operations such as searching, inserting, and deleting, but on average, these operations can be performed in O(log n) time, where n is the number of nodes in the tree.

## Insert a new element into a BST

To insert a new element into a BST, we follow a similar process. We start at the root node and compare the value to be inserted with the value of the current node. If the value is less than the current node value and the left child is null, we create a new node as the left child of the current node with the value to be inserted. If the left child is not null, we repeat the process with the left child. If the value is greater than or equal to the current node value and the right child is null, we create a new node as the right child of the current node with the value to be inserted. If the right child is not null, we repeat the process with the right child.

## Delete an element from a BST (three cases to consider)

1.  The node to be deleted has no children. In this case, we simply remove the node from the tree.
2.  The node to be deleted has one child. In this case, we replace the node with its child.
3.  The node to be deleted has two children. In this case, we replace the node with its successor (the smallest node in the right subtree) or its predecessor (the largest node in the left subtree) and delete the successor or predecessor from the tree.
