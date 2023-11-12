#include "BpTree.h"

bool BpTree::Insert(LoanBookData *newData)
{
	// if bptree is empty
	if (root == NULL)
	{
		root = new BpTreeDataNode();
		root->insertDataMap(newData->getName(), newData);
		return true;
	}

	BpTreeNode* curr = searchDataNode(newData->getName());

	if (curr == NULL)
		return false;

	dynamic_cast<BpTreeDataNode*>(curr)->insertDataMap(newData->getName(), newData);

	if (excessDataNode(curr))
		return splitDataNode(curr);

	return true;
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
	BpTreeDataNode* newDNode = new BpTreeDataNode();

	auto dMap = dynamic_cast<BpTreeDataNode*>(pDataNode)->getDataMap();
	auto i = dMap->begin();
	advance(i, dMap->size() / 2);

	while (i != dMap->end())
	{
		newDNode->insertDataMap(i->first, i->second);
		i = dMap->erase(i);
	}

	newDNode->setNext(dynamic_cast<BpTreeDataNode*>(pDataNode)->getNext());
	dynamic_cast<BpTreeDataNode*>(pDataNode)->setNext(newDNode);
	newDNode->setPrev(dynamic_cast<BpTreeDataNode*>(pDataNode));

	BpTreeIndexNode* pIndexNode = dynamic_cast<BpTreeIndexNode*>(pDataNode->getParent());
	pIndexNode->insertIndexMap(newDNode->getDataMap()->begin()->first, newDNode);

	return true;
}

bool BpTree::splitIndexNode(BpTreeNode *pIndexNode)
{
	BpTreeIndexNode* newINode = new BpTreeIndexNode();

	auto iMap = dynamic_cast<BpTreeIndexNode*>(pIndexNode)->getIndexMap();
	auto i = iMap->begin();
	advance(i, iMap->size() / 2);

	while (i != iMap->end())
	{
		newINode->insertIndexMap(i->first, i->second);
		i = iMap->erase(i);
	}

	newINode->setNext(dynamic_cast<BpTreeIndexNode*>(pIndexNode)->getNext());
	dynamic_cast<BpTreeIndexNode*>(pIndexNode)->setNext(newINode);
	newINode->setPrev(dynamic_cast<BpTreeIndexNode*>(pIndexNode));

	BpTreeIndexNode* pINode = dynamic_cast<BpTreeIndexNode*>(pIndexNode->getParent());
	pINode->insertIndexMap(newINode->getIndexMap()->begin()->first, newINode);

	return true;
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
	while (dcurr != NULL)
	{
		auto i = dcurr->getDataMap()->begin();

		for (i; i != dcurr->getDataMap()->end(); i++)
			if (i->first == name) return dcurr;

		dcurr = dynamic_cast<BpTreeDataNode*>(dcurr->getNext());
	}

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
	BpTreeNode* curr = root;

	while (curr->isLeaf() == false)
	{
		auto iMap = dynamic_cast<BpTreeIndexNode*>(curr)->getIndexMap();
		auto i = iMap->upper_bound(start);

		if (i == iMap->begin())
			i = iMap->begin();
		else
			--i;

		curr = i->second;
	}

	while (curr != NULL && curr->isLeaf())
	{
		auto dMap = dynamic_cast<BpTreeDataNode*>(curr)->getDataMap();

		for (auto i = dMap->lower_bound(start); i != dMap->end() && i->first <= end; ++i)
			*fout << *(i->second);

		curr = dynamic_cast<BpTreeDataNode*>(curr)->getNext();
	}

	return true;
}

bool BpTree::linearPrint()
{
	BpTreeNode* curr = root;

	while (curr != NULL && curr->isLeaf() == false)
		curr = dynamic_cast<BpTreeDataNode*>(curr)->getMostLeftChild();

	while (curr != NULL && curr->isLeaf())
	{
		auto dMap = dynamic_cast<BpTreeDataNode*>(curr)->getDataMap();

		for (auto i = dMap->begin(); i != dMap->end(); ++i)
			*fout << *(i->second);

		curr = dynamic_cast<BpTreeDataNode*>(curr)->getNext();

	}

	return true;
}