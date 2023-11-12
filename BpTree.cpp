#include "BpTree.h"

bool BpTree::Insert(LoanBookData *newData)
{
	// BpTree is empty, create a new data node as the root
	if (root == NULL)
	{
		root = new BpTreeDataNode();
		root->insertDataMap(newData->getName(), newData);
		return true;
	}
	// find the location and insert
	else
	{
		BpTreeNode* dataNode = searchDataNode(newData->getName());
		return Insert(dataNode, newData);
	}
}

bool BpTree::Insert(BpTreeNode* node, LoanBookData* newData)
{
	BpTreeDataNode* curr = dynamic_cast<BpTreeDataNode*>(node);

	// insert data into data map
	curr->insertDataMap(newData->getName(), newData);

	// curr has more data than order
	if (excessDataNode(curr))
	{
		//todo
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

bool BpTree::splitDataNode(BpTreeNode *pDataNode)
{
	// create new index, data node
	BpTreeIndexNode *iNode = dynamic_cast<BpTreeIndexNode*>(pDataNode->getParent());

	// there is only a data node
	if (iNode == NULL)
	{
		iNode = new BpTreeIndexNode;
		root = iNode;
	}

	// create two data node to link
	BpTreeDataNode *dNodeL = new BpTreeDataNode;
	BpTreeDataNode *dNodeR = new BpTreeDataNode;

	// set link field
	iNode->setMostLeftChild(dNodeL);


}

bool BpTree::splitIndexNode(BpTreeNode *pIndexNode)
{
	BpTreeIndexNode *pNode = dynamic_cast<BpTreeIndexNode*>(pIndexNode->getParent());
	if (pNode == NULL)
		pNode = new BpTreeIndexNode;
	BpTreeIndexNode *iNode1 = new BpTreeIndexNode;
	BpTreeIndexNode *iNode3 = new BpTreeIndexNode;

	// set link field
	pNode->setParent(pIndexNode->getParent());
	pNode->setMostLeftChild(iNode1);

	iNode1->setParent(pNode);
	iNode3->setParent(pNode);

	// first element is already connected by mostleftchild pointer.
	// insert second element into parent index node.
	pNode->insertIndexMap(pIndexNode->getIndexMap()->begin()->first,
						  iNode3);

	// insert first and second element into parent index node.
	pIndexNode->getMostLeftChild()->setParent(iNode1);
	auto i = pIndexNode->getIndexMap()->begin();
	iNode1->insertIndexMap(i->first, i->second);

	// insert third and fourth element into
	(++i)->second->setParent(iNode3);
	iNode3->setMostLeftChild(i->second);
	iNode3->insertIndexMap((++i)->first, i->second);

	// split parent index node if it's necessary
	if (excessIndexNode(pNode) == false)
		splitIndexNode(pNode);

	return pNode;
}

BpTreeNode *BpTree::searchDataNode(string name)
{
	BpTreeNode* curr = root;

	// move to most left data node
	while (curr->isLeaf() == false)
		curr = curr->getMostLeftChild();

	BpTreeDataNode* dcurr = dynamic_cast<BpTreeDataNode*>(curr);

	// search data node's map
	// if there is not data to search, move to next data node by link field
	do
	{
		auto i = dcurr->getDataMap()->begin();

		for (i; i != dcurr->getDataMap()->end(); i++)
			if (i->first == name) return dcurr;

		dcurr = dynamic_cast<BpTreeDataNode*>(dcurr->getNext());
	} while (curr != NULL);

	// return the location to insert
	return dcurr;
}

bool BpTree::searchBook(string name)
{
	BpTreeNode *curr = root;

	// move to most left data node
	while (curr->isLeaf() == false)
		curr = curr->getMostLeftChild();

	// linear search using data node's link field
	while (curr != NULL)
	{
		// first, search current data node's map
		auto i = curr->getDataMap()->begin();
		for (i; i != curr->getDataMap()->end(); i++)
		{
			if (i->first == name)
				return true;
		}
		// move to next data node
		curr = curr->getNext();
	}

	// failed to find node
	return curr;
}

bool BpTree::searchRange(string start, string end)
{
	BpTreeNode *curr = root;
	if (curr == NULL)
		throw "bool BpTree::searchRange(string start, string end)";

	bool exstart = false;
	bool exend = false;

	// move to most left data node
	while (curr->isLeaf() == false)
		curr = curr->getMostLeftChild();

	// linear search using data node's link field
	while (curr != NULL)
	{
		// find start point
		auto i = curr->getDataMap()->begin();
		for (i; i != curr->getDataMap()->end(); i++)
		{
			if (i->first > start)
			{
				exstart = true;
				break;
			}
		}
		curr = curr->getNext();
	}

	// todo: extract data between start and end.

	return false;
}

bool BpTree::linearPrint()
{
	BpTreeNode *curr = root;

	if (curr == NULL)
	{
		throw "bool BpTree::linearPrint() - BpTree is empty.";
		return false;
	}

	while(curr->isLeaf() == false)
		curr = curr->getMostLeftChild();

	while (curr)
	{
		auto i = curr->getDataMap()->begin();

		for (i; i != curr->getDataMap()->end(); i++)
		{
			*fout << i->second << endl;
		}
	}

	return false;
}