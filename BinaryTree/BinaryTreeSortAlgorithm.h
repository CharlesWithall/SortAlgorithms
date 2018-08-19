#pragma once

class BinaryTree;
struct Node;

class BinaryTreeSortAlgorithm
{
public:
	BinaryTreeSortAlgorithm() {};
	virtual ~BinaryTreeSortAlgorithm() {};
	virtual Node* Sort(const BinaryTree* const aBinaryTree, Node* aNode, const int aNewValue) = 0;
	static Node* AVLSort(const BinaryTree* const aBinaryTree, Node* aNode, const int aNewValue);
	static Node* RedBlackTreeSort(const BinaryTree* const aBinaryTree, Node* aNode, const int aNewValue);
};
