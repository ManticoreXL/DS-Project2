#include "BpTree.h"

bool BpTree::Insert(LoanBookData *newData)
{
	BpTreeNode* curr = searchDataNode(newData->getName());

	if(excessDataNode(curr))
		curr->insertDataMap(newData->getName(), newData);
	else
	{

	}

}

bool BpTree::excessDataNode(BpTreeNode *pDataNode)
{
	if (pDataNode->getDataMap()->size() > order - 1)
		return true; // order is equal to the number of elements
	else
		return false;
}

bool BpTree::excessIndexNode(BpTreeNode *pIndexNode)
{
	if (pIndexNode->getIndexMap()->size() > order - 1)
		return true; // order is equal to the number of elements
	else
		return false;
}
void BpTree::splitDataNode(BpTreeNode *pDataNode)
{
}

void BpTree::splitIndexNode(BpTreeNode *pIndexNode)
{
}

BpTreeNode *BpTree::searchDataNode(string name)
{
	BpTreeNode* curr = root;

	while(curr->isLeaf() != false)
	{
			BpTreeNode* child = curr->getMostLeftChild();
	}

	return curr;
}

bool BpTree::searchBook(string name)
{
}

bool BpTree::searchRange(string start, string end)
{
}
