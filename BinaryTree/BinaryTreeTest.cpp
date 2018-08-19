#include "stdafx.h"

#include "../BinaryTreeLib/BinaryTree.h"
#include "../BinaryTreeLib/Node.h"

#include "../SortAlgorithms/SortAlgorithms.h"

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <windows.h>

void DrawTree(const Node* aRootNode, int anIndex);

int main()
{
	BinaryTree binaryTree(&BinaryTreeSort::Algorithms::AVLSort);
	const int numberOfIntegers = 300;
	std::vector<int> arrayOfIntegers;

	for (int i = 0; i < numberOfIntegers; ++i)
	{
		arrayOfIntegers.push_back(i + 1);
	}

	std::random_shuffle(std::begin(arrayOfIntegers), std::end(arrayOfIntegers));

	for (int i = 0; i < numberOfIntegers; ++i)
	{
		binaryTree.InsertNode(arrayOfIntegers[i]);
	}

	DrawTree(binaryTree.GetRootNode(), 0);

	return 0;
}

void DrawTree(const Node* aRootNode, int anIndex)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!aRootNode)
	{
		return;
	}

	DrawTree(aRootNode->myRightNode, anIndex + 1);

	std::string indent = "";

	for (int i = 0; i < anIndex; ++i)
	{
		indent += "   ";
	}

	SetConsoleTextAttribute(hConsole, BinaryTreeSort::Utils::RedBlackTreeGetNodeIsBlack(aRootNode) ? 15 : 12);
	std::cout << indent << aRootNode->myValue << std::endl;

	DrawTree(aRootNode->myLeftNode, anIndex + 1);
}