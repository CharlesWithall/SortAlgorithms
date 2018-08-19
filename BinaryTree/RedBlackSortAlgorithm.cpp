#include "stdafx.h"
#include "RedBlackSortAlgorithm.h"

#include "BinaryTree.h"
#include "Node.h"

Node* RedBlackSortAlgorithm::Sort(const BinaryTree* const aBinaryTree, Node* aNode, const int /*aNewValue*/)
{
	const bool bothChildrenRed = Node::GetColour(aNode->myLeftNode) == Node::Colour::RED && Node::GetColour(aNode->myRightNode) == Node::Colour::RED;

	if (aNode->myLeftNode && aNode->myLeftNode->myLeftNode)
	{
		if (bothChildrenRed && aNode->myLeftNode->myLeftNode->myColour == Node::Colour::RED)
		{
			aNode->myColour = Node::Colour::RED;
			aNode->myLeftNode->myColour = Node::Colour::BLACK;
			aNode->myRightNode->myColour = Node::Colour::BLACK;
			return aNode;
		}
		else if (Node::GetColour(aNode->myLeftNode) == Node::Colour::RED &&
			Node::GetColour(aNode->myRightNode) == Node::Colour::BLACK &&
			aNode->myLeftNode->myLeftNode->myColour == Node::Colour::RED)
		{
			aNode->myLeftNode->myColour = Node::Colour::BLACK;
			aNode->myColour = Node::Colour::RED;
			return aBinaryTree->RotateRight(aNode);
		}
	}

	if (aNode->myRightNode && aNode->myRightNode->myRightNode)
	{
		if (bothChildrenRed && aNode->myRightNode->myRightNode->myColour == Node::Colour::RED)
		{
			aNode->myColour = Node::Colour::RED;
			aNode->myLeftNode->myColour = Node::Colour::BLACK;
			aNode->myRightNode->myColour = Node::Colour::BLACK;
			return aNode;
		}
		else if (Node::GetColour(aNode->myRightNode) == Node::Colour::RED &&
			Node::GetColour(aNode->myLeftNode) == Node::Colour::BLACK &&
			aNode->myRightNode->myRightNode->myColour == Node::Colour::RED)
		{
			aNode->myRightNode->myColour = Node::Colour::BLACK;
			aNode->myColour = Node::Colour::RED;
			return aBinaryTree->RotateLeft(aNode);
		}
	}

	if (aNode->myRightNode && aNode->myRightNode->myLeftNode)
	{
		if (bothChildrenRed && aNode->myRightNode->myLeftNode->myColour == Node::Colour::RED)
		{
			aNode->myColour = Node::Colour::RED;
			aNode->myLeftNode->myColour = Node::Colour::BLACK;
			aNode->myRightNode->myColour = Node::Colour::BLACK;
			return aNode;
		}
		else if (Node::GetColour(aNode->myRightNode) == Node::Colour::RED &&
			Node::GetColour(aNode->myLeftNode) == Node::Colour::BLACK &&
			aNode->myRightNode->myLeftNode->myColour == Node::Colour::RED)
		{
			aNode->myRightNode->myLeftNode->myColour = Node::Colour::BLACK;
			aNode->myColour = Node::Colour::RED;
			aNode->myRightNode = aBinaryTree->RotateRight(aNode->myRightNode);
			return aBinaryTree->RotateLeft(aNode);
		}
	}

	if (aNode->myLeftNode && aNode->myLeftNode->myRightNode)
	{
		if (bothChildrenRed && aNode->myLeftNode->myRightNode->myColour == Node::Colour::RED)
		{
			aNode->myColour = Node::Colour::RED;
			aNode->myLeftNode->myColour = Node::Colour::BLACK;
			aNode->myRightNode->myColour = Node::Colour::BLACK;
			return aNode;
		}
		else if (Node::GetColour(aNode->myLeftNode) == Node::Colour::RED &&
			Node::GetColour(aNode->myRightNode) == Node::Colour::BLACK &&
			aNode->myLeftNode->myRightNode->myColour == Node::Colour::RED)
		{
			aNode->myLeftNode->myRightNode->myColour = Node::Colour::BLACK;
			aNode->myColour = Node::Colour::RED;
			aNode->myLeftNode = aBinaryTree->RotateLeft(aNode->myLeftNode);
			return aBinaryTree->RotateRight(aNode);
		}
	}

	return aNode;
}
