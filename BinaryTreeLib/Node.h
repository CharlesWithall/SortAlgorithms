#pragma once

#include <algorithm>

struct NodeExtension
{
	virtual ~NodeExtension() = 0 {};
};

struct Node
{
	Node(int aValue)
		: myLeftNode(nullptr)
		, myRightNode(nullptr)
		, myExtension(nullptr)
		, myValue(aValue)
	{
	}

	~Node()
	{
		delete myExtension;
	}

	Node* myLeftNode;
	Node* myRightNode;
	NodeExtension* myExtension;
	int myValue;

	static Node* RotateLeft(Node* aParentNode)
	{
		Node* pivotNode = aParentNode->myRightNode;
		Node* pivotNodeLeft = pivotNode->myLeftNode;

		pivotNode->myLeftNode = aParentNode;
		aParentNode->myRightNode = pivotNodeLeft;

		return pivotNode;
	}

	static Node* RotateRight(Node* aParentNode)
	{
		Node* pivotNode = aParentNode->myLeftNode;
		Node* pivotNodeRight = pivotNode->myRightNode;

		pivotNode->myRightNode = aParentNode;
		aParentNode->myLeftNode = pivotNodeRight;

		return pivotNode;
	}
};
