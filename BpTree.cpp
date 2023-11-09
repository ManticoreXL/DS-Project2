#include "BpTree.h"

bool BpTree::Insert(LoanBookData *newData)
{
	if (root == NULL)
	{
		root = new BpTreeDataNode();
		root->insertDataMap(newData->getName(), newData);
		return true;
	}

	BpTreeNode *curr = searchDataNode(newData->getName());

	if (curr->getParent() == NULL) // part 1: there's only a data node
	{
		if (excessDataNode(curr) == true) // insert
			curr->insertDataMap(newData->getName(), newData);
		else // split and insert
		{
			splitDataNode(curr);
			if (root->getMostLeftChild()->getDataMap()->begin()->first > newData->getName())
			{
				// case 1: newData is eariler than mostLeftChild
				curr = root->getMostLeftChild();
				curr->insertDataMap(newData->getName(), newData);
				return true;
			}
			else
			{
				// case 2: newData is later than mostLeftChild
				curr = root->getIndexMap()->begin()->second;
				curr->insertDataMap(newData->getName(), newData);
				return true;
			}
		}
	}
	else // part 2: indexnode is existing over curr
	{
		if (excessDataNode(curr) == true) // insert
		{
			curr->insertDataMap(newData->getName(), newData);
			return true;
		}
		else // split and insert
		{
			BpTreeNode *parent = curr->getParent();
			splitDataNode(curr);

			auto i = parent->getIndexMap()->begin();
			for (i; i != parent->getIndexMap()->end(); i++)
			{
				if (i->first < newData->getName())
				{
					i->second->insertDataMap(newData->getName(), newData);
					return true;
				}
			}
		}
	}

	// failed to insert. return false.
	return false;
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
	BpTreeNode *iNode = pDataNode->getParent();
	if (iNode == nullptr)
	{
		iNode = new BpTreeIndexNode;
		root = iNode;
	}
	BpTreeDataNode *dNode1 = new BpTreeDataNode;
	BpTreeDataNode *dNode3 = new BpTreeDataNode;

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
	for (i; i != pDataNode->getDataMap()->end(); ++i)
		dNode3->insertDataMap(i->first, i->second);

	// first data node is already connected by mostleftchild pointer.
	// insert second data node to new index node.
	iNode->insertIndexMap(dNode3->getDataMap()->begin()->first, dNode3);

	// split parent index node if it's necessary.
	if (excessIndexNode(iNode) == false)
		splitIndexNode(iNode);
}

void BpTree::splitIndexNode(BpTreeNode *pIndexNode)
{
	BpTreeNode *pNode = pIndexNode->getParent();
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
}

BpTreeNode *BpTree::searchDataNode(string name)
{
	BpTreeNode *curr = root;

	// move to most left data node
	while (curr->isLeaf() == false)
		curr = curr->getMostLeftChild();

	// using data nodes' link field to find fit location to insert

	do
	{
		auto i = curr->getDataMap()->begin();
		for (i; i != curr->getDataMap()->end(); i++)
		{
			if (i->first > name) // found fit location to insert
				return curr;
		}
		curr = curr->getNext();
	} while (curr != NULL && curr->getNext() != NULL);

	// name is the latest name in BpTree. return most right child.
	return curr;
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
	return false;
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

vector<LoanBookData *> &BpTree::linearPrint()
{
	vector<LoanBookData *> bookList;

	BpTreeNode *curr = root;

	// move to leaf node
	while (curr->isLeaf() == false)
		curr = curr->getMostLeftChild();

	while (curr != NULL)
	{
		auto i = curr->getDataMap()->begin();

		for (i; i != curr->getDataMap()->end(); i++)
		{
			bookList.push_back(i->second);
		}
		curr = curr->getNext();
	}

	return bookList;
}