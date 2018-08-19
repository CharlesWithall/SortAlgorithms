#include "stdafx.h"

#include "BinaryTree.h"
#include "Node.h"

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

void BinaryTree::InsertNode(const int aValue)
{
	myRootNode = InsertNode(myRootNode, aValue);
}

Node* BinaryTree::InsertNode(Node* aRootNode, const int aValue)
{
	if (aRootNode == NULL)
	{
		return new Node(aValue);
	}

	if (aValue < aRootNode->myValue)
	{
		aRootNode->myLeftNode = InsertNode(aRootNode->myLeftNode, aValue);
	}
	else if (aValue > aRootNode->myValue)
	{
		aRootNode->myRightNode = InsertNode(aRootNode->myRightNode, aValue);
	}
	else
	{
		std::cout << "ERROR: Trying to add a value to the binary tree that already exists. Value is: " << aValue << std::endl;
		return aRootNode;
	}

	if (MySortFunction)
	{
		return MySortFunction(aRootNode);
	}
	
	return aRootNode;
}

Node* BinaryTree::SearchFor(const int aValue)
{
	return SearchFor(aValue, myRootNode);
}

Node* BinaryTree::SearchFor(const int aValue, Node* aSearchNode)
{
	if (aSearchNode->myValue == aValue)
	{
		return aSearchNode;
	}

	else if (aSearchNode->myValue > aValue && aSearchNode->myLeftNode)
	{
		return SearchFor(aValue, aSearchNode->myLeftNode);
	}

	else if (aSearchNode->myValue < aValue && aSearchNode->myRightNode)
	{
		return SearchFor(aValue, aSearchNode->myRightNode);
	}

	return nullptr;
}

void BinaryTree::DeleteNode(const int aValue)
{
	myRootNode = DeleteNode(myRootNode, aValue);
}

Node* BinaryTree::DeleteNode(Node* aRootNode, const int aValue)
{
	if (aRootNode == nullptr)
	{
		return aRootNode;
	}
	
	if (aValue < aRootNode->myValue)
	{
		aRootNode->myLeftNode = DeleteNode(aRootNode->myLeftNode, aValue);
	}
	else if (aValue > aRootNode->myValue)
	{
		aRootNode->myRightNode = DeleteNode(aRootNode->myRightNode, aValue);
	}
	else
	{
		if (aRootNode->myLeftNode == nullptr || aRootNode->myRightNode == nullptr)
		{
			Node* successorNode = aRootNode->myLeftNode ? aRootNode->myLeftNode : aRootNode->myRightNode;

			if (!successorNode)
			{
				delete(aRootNode);
				aRootNode = nullptr;
			}
			else
			{
				*aRootNode = *successorNode;
				delete(successorNode);
			}
		}
		else
		{
			Node* successorNode = aRootNode->myRightNode;
			while (successorNode->myLeftNode != nullptr)
			{
				successorNode = successorNode->myLeftNode;
			}

			aRootNode->myValue = successorNode->myValue;
			aRootNode->myRightNode = DeleteNode(aRootNode->myRightNode, successorNode->myValue);
		}
	}

	if (MySortFunction)
	{
		return MySortFunction(aRootNode);
	}

	return aRootNode;
}