#pragma once

class BinaryTree;
struct Node;

namespace BinaryTreeSort
{
	// This class is exported from the SortAlgorithms.dll
	class __declspec(dllexport) Algorithms
	{
	public:
		// Returns replacement root node for 'aNode' after performing an AVL Sort
		static Node* AVLSort(Node* aNode);
		
		// Return replacement root node for 'aNode' after performing a Red/Black Sort
		static Node* RedBlackTreeSort(Node* aNode);
	};

	class __declspec(dllexport) Utils
	{
	public:
		// Gets if the node is black - returns true by default if no data can be found
		static bool RedBlackTreeGetNodeIsBlack(const Node* aNode);
	};
}
