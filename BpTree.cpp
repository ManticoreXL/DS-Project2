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
	// create new index, data node
	BpTreeNode* iNode = pDataNode->getParent();
	if(iNode == nullptr)
		iNode = new BpTreeIndexNode;
	BpTreeDataNode* dNode1 = new BpTreeDataNode;
	BpTreeDataNode* dNode3 = new BpTreeDataNode;	

	// set link field
	iNode->setParent(pDataNode->getParent());
	iNode->setMostLeftChild(dNode1);

	dNode1->setParent(iNode);
	dNode3->setParent(iNode);

	dNode1->setNext(dNode3);
	dNode3->setParent(dNode1);

	// insert first datamap into first new data node.
	dNode1->insertDataMap(pDataNode->getDataMap()->begin()->first,
						  pDataNode->getDataMap()->begin()->second);
	
	// insert remaining two datamap into second new data node.
	auto i = pDataNode->getDataMap()->begin();
	for(i; i != pDataNode->getDataMap()->end(); ++i)
		dNode3->insertDataMap(i->first, i->second);

	// insert two data nodes into new index node.
	iNode->insertIndexMap(dNode1->getDataMap()->begin()->first, dNode1);
	iNode->insertIndexMap(dNode3->getDataMap()->begin()->first, dNode3);

	// split parent index node if it's necessary.
	if(excessIndexNode(iNode) == false)
		splitIndexNode(iNode);
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
