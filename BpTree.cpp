#include "BpTree.h"

bool BpTree::Insert(LoanBookData *newData)
{
	if (root == nullptr)
	{
		root = new BpTreeIndexNode;
		root->insertDataMap(newData->getName(), nullptr);
	}
	else
	{
		return Insert(root, newData);
	}
	return true;
}

bool BpTree::Insert(BpTreeNode *node, LoanBookData *newData)
{
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
	BpTreeDataNode *temp = new BpTreeDataNode();
	temp->setNext(pDataNode->getNext());
	pDataNode->setNext(temp);
}

void BpTree::splitIndexNode(BpTreeNode *pIndexNode)
{
}

BpTreeNode *BpTree::searchDataNode(string name)
{
	BpTreeNode *pCur = root;
	return pCur;
}

bool BpTree::searchBook(string name)
{
}

bool BpTree::searchRange(string start, string end)
{
}
