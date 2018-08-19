#include "stdafx.h"
#include "AVLSortAlgorithm.h"

#include "BinaryTree.h"
#include "Node.h"

Node* AVLSortAlgorithm::Sort(const BinaryTree* const aBinaryTree, Node* aNode, const int aNewValue)
{
	int balance = Node::GetBalanceFactor(aNode);

	// Left Left
	if (balance > 1 && aNewValue < aNode->myLeftNode->myValue)
	{
		return aBinaryTree->RotateRight(aNode);
	}

	// Right Right 
	if (balance < -1 && aNewValue > aNode->myRightNode->myValue)
	{
		return aBinaryTree->RotateLeft(aNode);
	}

	// Left Right
	if (balance > 1 && aNewValue > aNode->myLeftNode->myValue)
	{
		aNode->myLeftNode = aBinaryTree->RotateLeft(aNode->myLeftNode);
		return aBinaryTree->RotateRight(aNode);
	}

	// Right Left
	if (balance < -1 && aNewValue < aNode->myRightNode->myValue)
	{
		aNode->myRightNode = aBinaryTree->RotateRight(aNode->myRightNode);
		return aBinaryTree->RotateLeft(aNode);
	}

	return aNode;
}
