#include "stdafx.h"
#include "SortAlgorithms.h"

#include "../BinaryTreeLib/BinaryTree.h"
#include "../BinaryTreeLib/Node.h"

namespace BinaryTreeSort
{
#undef max
	struct AVLNodeExtension : NodeExtension
	{
		AVLNodeExtension()
			: myHeight(1)
		{

		}

		static int GetBalanceFactor(Node* aNode)
		{
			return aNode ? GetHeight(aNode->myLeftNode) - GetHeight(aNode->myRightNode) : 0;
		}

		static int GetHeight(Node* aNode)
		{
			if (aNode)
			{
				if (AVLNodeExtension* avlData = static_cast<AVLNodeExtension*>(aNode->myExtension))
				{
					return avlData->myHeight;
				}
			}
			
			return 0;
		}

		static Node* RotateLeft(Node* aParentNode)
		{
			Node* rotatedNode = Node::RotateLeft(aParentNode);

			static_cast<AVLNodeExtension*>(rotatedNode->myLeftNode->myExtension)->myHeight = std::max(GetHeight(rotatedNode->myLeftNode->myLeftNode), GetHeight(rotatedNode->myLeftNode->myRightNode)) + 1;
			static_cast<AVLNodeExtension*>(rotatedNode->myExtension)->myHeight = std::max(GetHeight(rotatedNode->myLeftNode), GetHeight(rotatedNode->myRightNode)) + 1;

			return rotatedNode;
		}

		static Node* RotateRight(Node* aParentNode)
		{
			Node* rotatedNode = Node::RotateRight(aParentNode);

			static_cast<AVLNodeExtension*>(rotatedNode->myRightNode->myExtension)->myHeight = std::max(GetHeight(rotatedNode->myRightNode->myLeftNode), GetHeight(rotatedNode->myRightNode->myRightNode)) + 1;
			static_cast<AVLNodeExtension*>(rotatedNode->myExtension)->myHeight = std::max(GetHeight(rotatedNode->myLeftNode), GetHeight(rotatedNode->myRightNode)) + 1;

			return rotatedNode;
		}

		int myHeight;
	};

	struct RedBlackNodeExtension : NodeExtension
	{
		enum Colour
		{
			RED,
			BLACK
		};

		RedBlackNodeExtension()
			: myColour(RED)
		{	
		}

		Colour myColour;

		static Colour GetColour(const Node* aNode)
		{
			if (aNode)
			{
				if (RedBlackNodeExtension* rbData = dynamic_cast<RedBlackNodeExtension*>(aNode->myExtension))
				{
					return rbData->myColour;
				}
			}

			return Colour::BLACK;
		}

		static void SetColour(Node* aNode, Colour aColour)
		{
			if (aNode)
			{
				if (RedBlackNodeExtension* rbData = static_cast<RedBlackNodeExtension*>(aNode->myExtension))
				{
					rbData->myColour = aColour;
				}
			}
		}
	};

	Node* Algorithms::AVLSort(Node* aNode)
	{
		if (!aNode)
		{
			return aNode;
		}

		if (!aNode->myExtension)
		{
			aNode->myExtension = new AVLNodeExtension();
		}

		AVLNodeExtension* avlNodeExtension = static_cast<AVLNodeExtension*>(aNode->myExtension);

		avlNodeExtension->myHeight = std::max(AVLNodeExtension::GetHeight(aNode->myLeftNode), AVLNodeExtension::GetHeight(aNode->myRightNode)) + 1;

		int balance = AVLNodeExtension::GetBalanceFactor(aNode);

		// Left Left
		if (balance > 1 && AVLNodeExtension::GetBalanceFactor(aNode->myLeftNode) >= 0)
		{
			return AVLNodeExtension::RotateRight(aNode);
		}

		// Right Right 
		if (balance < -1 && AVLNodeExtension::GetBalanceFactor(aNode->myRightNode) <= 0)
		{
			return AVLNodeExtension::RotateLeft(aNode);
		}

		// Left Right
		if (balance > 1 && AVLNodeExtension::GetBalanceFactor(aNode->myLeftNode) < 0)
		{
			aNode->myLeftNode = AVLNodeExtension::RotateLeft(aNode->myLeftNode);
			return AVLNodeExtension::RotateRight(aNode);
		}

		// Right Left
		if (balance < -1 && AVLNodeExtension::GetBalanceFactor(aNode->myRightNode) > 0)
		{
			aNode->myRightNode = AVLNodeExtension::RotateRight(aNode->myRightNode);
			return AVLNodeExtension::RotateLeft(aNode);
		}

		return aNode;
	}

	Node* Algorithms::RedBlackTreeSort(Node* aNode)
	{
		if (!aNode)
		{
			return aNode;
		}

		if (!aNode->myExtension)
		{
			aNode->myExtension = new RedBlackNodeExtension();
		}

		const bool bothChildrenRed = RedBlackNodeExtension::GetColour(aNode->myLeftNode) == RedBlackNodeExtension::Colour::RED && RedBlackNodeExtension::GetColour(aNode->myRightNode) == RedBlackNodeExtension::Colour::RED;

		if (aNode->myLeftNode && aNode->myLeftNode->myLeftNode)
		{
			if (bothChildrenRed && RedBlackNodeExtension::GetColour(aNode->myLeftNode->myLeftNode) == RedBlackNodeExtension::Colour::RED)
			{
				RedBlackNodeExtension::SetColour(aNode, RedBlackNodeExtension::Colour::RED);
				RedBlackNodeExtension::SetColour(aNode->myLeftNode, RedBlackNodeExtension::Colour::BLACK);
				RedBlackNodeExtension::SetColour(aNode->myRightNode, RedBlackNodeExtension::Colour::BLACK);
				return aNode;
			}
			else if (RedBlackNodeExtension::GetColour(aNode->myLeftNode) == RedBlackNodeExtension::Colour::RED &&
				RedBlackNodeExtension::GetColour(aNode->myRightNode) == RedBlackNodeExtension::Colour::BLACK &&
				RedBlackNodeExtension::GetColour(aNode->myLeftNode->myLeftNode) == RedBlackNodeExtension::Colour::RED)
			{
				RedBlackNodeExtension::SetColour(aNode->myLeftNode, RedBlackNodeExtension::Colour::BLACK);
				RedBlackNodeExtension::SetColour(aNode, RedBlackNodeExtension::Colour::RED);
				return Node::RotateRight(aNode);
			}
		}

		if (aNode->myRightNode && aNode->myRightNode->myRightNode)
		{
			if (bothChildrenRed && RedBlackNodeExtension::GetColour(aNode->myRightNode->myRightNode) == RedBlackNodeExtension::Colour::RED)
			{
				RedBlackNodeExtension::SetColour(aNode, RedBlackNodeExtension::Colour::RED);
				RedBlackNodeExtension::SetColour(aNode->myLeftNode, RedBlackNodeExtension::Colour::BLACK);
				RedBlackNodeExtension::SetColour(aNode->myRightNode, RedBlackNodeExtension::Colour::BLACK);
				return aNode;
			}
			else if (RedBlackNodeExtension::GetColour(aNode->myRightNode) == RedBlackNodeExtension::Colour::RED &&
				RedBlackNodeExtension::GetColour(aNode->myLeftNode) == RedBlackNodeExtension::Colour::BLACK &&
				RedBlackNodeExtension::GetColour(aNode->myRightNode->myRightNode) == RedBlackNodeExtension::Colour::RED)
			{
				RedBlackNodeExtension::SetColour(aNode->myRightNode, RedBlackNodeExtension::Colour::BLACK);
				RedBlackNodeExtension::SetColour(aNode, RedBlackNodeExtension::Colour::RED);
				return Node::RotateLeft(aNode);
			}
		}

		if (aNode->myRightNode && aNode->myRightNode->myLeftNode)
		{
			if (bothChildrenRed && RedBlackNodeExtension::GetColour(aNode->myRightNode->myLeftNode) == RedBlackNodeExtension::Colour::RED)
			{
				RedBlackNodeExtension::SetColour(aNode, RedBlackNodeExtension::Colour::RED);
				RedBlackNodeExtension::SetColour(aNode->myLeftNode, RedBlackNodeExtension::Colour::BLACK);
				RedBlackNodeExtension::SetColour(aNode->myRightNode, RedBlackNodeExtension::Colour::BLACK);
				return aNode;
			}
			else if (RedBlackNodeExtension::GetColour(aNode->myRightNode) == RedBlackNodeExtension::Colour::RED &&
				RedBlackNodeExtension::GetColour(aNode->myLeftNode) == RedBlackNodeExtension::Colour::BLACK &&
				RedBlackNodeExtension::GetColour(aNode->myRightNode->myLeftNode) == RedBlackNodeExtension::Colour::RED)
			{
				RedBlackNodeExtension::SetColour(aNode->myRightNode->myLeftNode, RedBlackNodeExtension::Colour::BLACK);
				RedBlackNodeExtension::SetColour(aNode, RedBlackNodeExtension::Colour::RED);
				aNode->myRightNode = Node::RotateRight(aNode->myRightNode);
				return Node::RotateLeft(aNode);
			}
		}

		if (aNode->myLeftNode && aNode->myLeftNode->myRightNode)
		{
			if (bothChildrenRed && RedBlackNodeExtension::GetColour(aNode->myLeftNode->myRightNode) == RedBlackNodeExtension::Colour::RED)
			{
				RedBlackNodeExtension::SetColour(aNode, RedBlackNodeExtension::Colour::RED);
				RedBlackNodeExtension::SetColour(aNode->myLeftNode, RedBlackNodeExtension::Colour::BLACK);
				RedBlackNodeExtension::SetColour(aNode->myRightNode, RedBlackNodeExtension::Colour::BLACK);
				return aNode;
			}
			else if (RedBlackNodeExtension::GetColour(aNode->myLeftNode) == RedBlackNodeExtension::Colour::RED &&
				RedBlackNodeExtension::GetColour(aNode->myRightNode) == RedBlackNodeExtension::Colour::BLACK &&
				RedBlackNodeExtension::GetColour(aNode->myLeftNode->myRightNode) == RedBlackNodeExtension::Colour::RED)
			{
				RedBlackNodeExtension::SetColour(aNode->myLeftNode->myRightNode, RedBlackNodeExtension::Colour::BLACK);
				RedBlackNodeExtension::SetColour(aNode, RedBlackNodeExtension::Colour::RED);
				aNode->myLeftNode = Node::RotateLeft(aNode->myLeftNode);
				return Node::RotateRight(aNode);
			}
		}

		return aNode;
	}

	bool Utils::RedBlackTreeGetNodeIsBlack(const Node* aNode)
	{
		return (RedBlackNodeExtension::GetColour(aNode) == RedBlackNodeExtension::Colour::BLACK);
	}
}
