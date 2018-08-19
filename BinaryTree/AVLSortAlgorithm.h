#pragma once

#include "BinaryTreeSortAlgorithm.h"

class AVLSortAlgorithm : public BinaryTreeSortAlgorithm
{
public:
	virtual Node* Sort(const BinaryTree* const aBinaryTree, Node* aNode, const int aNewValue) override;
};
