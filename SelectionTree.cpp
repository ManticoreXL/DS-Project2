#include "SelectionTree.h"

bool SelectionTree::Insert(LoanBookData *newData)
{
	int bookCode = newData->getCode();
	if (bookCode != 0 && bookCode % 100 != 0)
	{
		throw "bool SelectionTree::Insert(LoanBookData *newData) - invalid bookCode.";
		return false;
	}

	// insert data into heap
	SelectionTreeNode* curr = (bookCode == 0) ? runs[0] : runs[bookCode / 100];
	curr->getHeap()->Insert(newData);

	// replay selection tree
	while (curr->getParent() != nullptr)
	{
		if (curr->getBookData() == nullptr || curr->getBookData()->getName() > newData->getName())
		{
			// set node's data to newData and go up
			curr->setBookData(newData);
			curr = curr->getParent();
		}
		else
			// no swap, go up
			curr = curr->getParent();

		// last stage of replay
		if (curr == root)
		{
			if (curr->getBookData() == nullptr || curr->getBookData()->getName() > newData->getName())
			{
				// set node's data to newData and go up
				curr->setBookData(newData);
				return true;
			}
			else
			{
				// no swap, go up
				curr = curr->getParent();
				return true;
			}
		}
	}

	return false;
}

bool SelectionTree::Delete()
{
	if (root->getBookData() == nullptr)
	{
		throw "bool SelectionTree::Delete() - stree is empty.";
		return false;
	}

	// get run that matches code
	int bookCode = root->getCode();
	SelectionTreeNode* curr = (bookCode == 0) ? runs[0] : runs[bookCode / 100];

	// delete heap's root
	if (curr->getHeap()->Delete() == false)
		return false;

	// get new lowest data and set as heap's root
	curr->setBookData(curr->getHeap()->getRoot()->getBookData());

	// replay selection tree
	while (curr->getParent() != nullptr)
	{
		if (curr->getParent()->getBookData() == nullptr || curr->getParent()->getBookData()->getName() > curr->getBookData()->getName())
		{
			curr->getParent()->setBookData(curr->getBookData());
			curr = curr->getParent();
		}
		else
			curr = curr->getParent();
	}

	return true;
}

bool SelectionTree::printBookData(int bookCode)
{
	if (root->getBookData() == nullptr)
	{
		throw "bool SelectionTree::printBookData(int bookCode) - stree is empty.";
		return false;
	}

	// find run and print heap
	SelectionTreeNode* curr = (bookCode == 0) ? runs.front() : runs[bookCode / 100];
	curr->getHeap()->printHeap();

	return true;
}