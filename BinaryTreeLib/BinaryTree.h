#pragma once

struct Node;

class BinaryTree
{
public:
	BinaryTree()
		: myRootNode(nullptr)
		, MySortFunction(nullptr)
	{
	}

	BinaryTree(Node* aSortFunction(Node* aNode))
		: myRootNode(nullptr)
	{
		MySortFunction = aSortFunction;
	}

	const Node* const GetRootNode() const { return myRootNode; }
	void DeleteNode(const int aValue);
	void InsertNode(const int aValue);
	Node* SearchFor(const int aValue);

private:
	Node* DeleteNode(Node* aRootNode, const int aValue);
	Node* InsertNode(Node* aPivotNode, const int aValue);
	Node* SearchFor(const int aValue, Node* aSearchNode);

	Node* (*MySortFunction)(Node* aNode);

	Node* myRootNode;
};