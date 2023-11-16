#include "BpTree.h"

bool BpTree::Insert(LoanBookData *newData)
{
	// if bptree is empty, create a new datanode and insert data
	if (root == nullptr)
		root = new BpTreeDataNode();

	// move to data node to insert
	BpTreeNode* curr = searchDataNode(newData->getName());

	// if newdata already exists in curr (ADD)
	auto i = curr->getDataMap()->find(newData->getName());
	if (i != curr->getDataMap()->end())
	{
		// update loan count and return true.
		i->second->updateCount();
		*fout << "========ADD========" << endl;
		*fout << *(i->second);
		*fout << "====================" << endl << endl;
		delete newData;

		//if (i->second->check())
			// delete and move to stree

		return true;
	}

	// insert data into curr
	curr->insertDataMap(newData->getName(), newData);
	if (!excessDataNode(curr)) // no need to split
		return true;

	// else, split curr
	splitDataNode(curr);

	// split parent of curr if it's necessary.
	while (curr->getParent())
	{
		curr = curr->getParent();
		if (!excessIndexNode(curr)) // no need to split parent of curr
			break; 
		else // split parent of curr
			splitIndexNode(curr);
	}

	// if curr was a only data node, set curr as root
	if (curr->getParent() == nullptr)
		root = curr;

	return true;
}

bool BpTree::excessDataNode(BpTreeNode *pDataNode)
{
	if (pDataNode->getDataMap()->size() > order - 1)
		return true; // order is equal to the number of elements
	else
		return false; // no need to split data node
}

bool BpTree::excessIndexNode(BpTreeNode *pIndexNode)
{
	if (pIndexNode->getIndexMap()->size() > order - 1)
		return true; // order is equal to the number of elements
	else
		return false; // no need to split index node
}

void BpTree::splitDataNode(BpTreeNode *pDataNode)
{
	if (pDataNode == nullptr)
	{
		throw "void BpTree::splitDataNode(BpTreeNode *pDataNode) - node is null";
		return;
	}

	// new data node (will be left child of index node)
	BpTreeNode* dNode = new BpTreeDataNode();

	// set link field
	if (pDataNode->getPrev())
	{
		pDataNode->getPrev()->setNext(dNode);
		dNode->setParent(pDataNode->getPrev());
	}

	// connect dNode and pDataNode
	dNode->setNext(pDataNode);
	pDataNode->setPrev(dNode);

	auto movdata = pDataNode->getDataMap()->begin();

	// move pDataNode's data to dNode
	for (int i = 0; i < split; i++)
	{
		dNode->insertDataMap(movdata->first, movdata->second);
		string movstr = movdata->first;
		movdata++;
		pDataNode->deleteMap(movstr);
	}

	// new parent node
	auto pNode = pDataNode->getParent();

	if (pNode == nullptr) // pDataNode is a only data node
	{
		BpTreeNode* iNode = new BpTreeIndexNode();

		// set link field to parent index node
		iNode->setMostLeftChild(dNode);
		iNode->insertIndexMap(pDataNode->getDataMap()->begin()->first, pDataNode);
		dNode->setParent(iNode);
		pDataNode->setParent(iNode);
	}
	else
	{
		pNode->insertIndexMap(pDataNode->getDataMap()->begin()->first, pDataNode);

		auto movindex = pNode->getIndexMap()->find(pDataNode->getDataMap()->begin()->first);

		// move pNode's index map to pNode
		if (movindex == pNode->getIndexMap()->begin())
			pNode->setMostLeftChild(dNode);
		else // insert in front of found location
			(--movindex)->second = pDataNode;

		// set link field
		dNode->setParent(pNode);
	}
}

void BpTree::splitIndexNode(BpTreeNode *pIndexNode)
{
	// another index node (will be left child of pNode)
	BpTreeNode* LCNode = new BpTreeIndexNode();

	// set link field
	LCNode->setMostLeftChild(pIndexNode->getMostLeftChild());
	LCNode->getMostLeftChild()->setParent(LCNode);

	auto temp = pIndexNode->getIndexMap()->begin();

	string movindex;
	for (int i = 0; i < split; i++)
	{
		// move pIndexNode's index map to LCNode
		LCNode->insertIndexMap(temp->first, temp->second);
		temp->second->setParent(LCNode);
		movindex = (temp++)->first;
		pIndexNode->deleteMap(movindex);
	}
	
	pIndexNode->setMostLeftChild(temp->second);
	movindex = temp->first;
	pIndexNode->deleteMap(movindex);

	// get parent node
	BpTreeNode* pNode = pIndexNode->getParent();

	if (pNode == nullptr) // pIndexNode is a only index node
	{
		BpTreeNode* iNode = new BpTreeIndexNode;

		// set link field and insert index map
		iNode->setMostLeftChild(LCNode);
		iNode->insertIndexMap(movindex, pIndexNode);

		LCNode->setParent(iNode);
		pIndexNode->setParent(iNode);
		root = iNode; // set iNode as root
	}
	else
	{
		// update pNode
		pNode->insertIndexMap(movindex, pIndexNode);

		auto i = pNode->getIndexMap()->find(movindex);

		// first element
		if (i == pNode->getIndexMap()->begin())
			pNode->setMostLeftChild(LCNode);
		else 
			// insert in front of found location
			(--i)->second = LCNode;

		// set link field
		LCNode->setParent(pNode);
	}

	return;
}

BpTreeNode* BpTree::searchDataNode(string name)
{
	// start from root
	BpTreeNode* curr = root;

	// move to most left data node
	while (curr != nullptr && curr->getMostLeftChild())
	{
		auto i = curr->getIndexMap()->begin();

		if (name < i->first) // move another index node
			curr = curr->getMostLeftChild();
		else // find 
		{
			for (i; i != curr->getIndexMap()->end(); i++)
				if (name < i->first)
					break;
			curr = (--i)->second;
		}
	}

	// return location to insert
	return curr;
}

bool BpTree::searchBook(string name)
{
	// start from root
	BpTreeNode* curr = root;

	if (curr == nullptr)
	{
		throw "bool BpTree::searchBook(string name) - bptree is empty.";
		return false;
	}

	// move to most left data node
	while (curr->getMostLeftChild() != nullptr)
		curr = curr->getMostLeftChild();

	// linear search at bottom
	while (curr != nullptr)
	{
		// search current data map
		for (auto i = curr->getDataMap()->begin(); i != curr->getDataMap()->end(); i++)
		{
			if (i->first == name)
			{
				*fout << "========SEARCH_BP========" << endl;
				*fout << *(i->second);
				*fout << "==========================" << endl << endl;
				return true;
			}
		}
		// move to next data node
		curr = curr->getNext();
	}

	// failed to find book
	return false;
}

bool BpTree::searchRange(string& start, string& end)
{
	// start from root
	BpTreeNode* curr = root;

	if (curr == nullptr)
	{
		throw "bool BpTree::searchRange(string start, string end) - bptree is empty.";
		return false;
	}

	// swap if it's necessary
	if (start > end)
	{
		string temp = start;
		start = end;
		end = temp;
	}

	// at least one book must be found
	bool succ = false;

	// move to most left data node
	while (curr->getMostLeftChild() != nullptr)
		curr = curr->getMostLeftChild();

	// print books within search range
	*fout << "========SEARCH_BP========" << endl;
	while (curr != nullptr)
	{
		for (auto i = curr->getDataMap()->begin(); i != curr->getDataMap()->end(); i++)
		{
			if (i->first >= start) // book found
			{
				*fout << *(i->second);
				succ = true;
			}
			if (i->first > end) // stop range search
			{
				*fout << "==========================" << endl << endl;
				return true;
			}
		}
		curr = curr->getNext();
	}
	*fout << "==========================" << endl << endl;

	return succ;
}

bool BpTree::linearPrint()
{
	// start from root
	BpTreeNode* curr = root;

	if (curr == nullptr)
	{
		throw "bool BpTree::linearPrint() - bptree is empty.";
		return false;
	}

	// move to most left data node
	while (curr->getMostLeftChild() != nullptr)
		curr = curr->getMostLeftChild();

	// linear print
	*fout << "========PRINT_BP========" << endl;
	while (curr != nullptr)
	{
		for (auto i = curr->getDataMap()->begin(); i != curr->getDataMap()->end(); i++)
			*fout << *(i->second);

		curr = curr->getNext();
	}
	*fout << "========================" << endl << endl;

	return true;
}