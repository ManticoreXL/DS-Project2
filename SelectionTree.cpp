#include "SelectionTree.h"

bool SelectionTree::Insert(LoanBookData *newData)
{
	root = Insert(root, newData);
	return true;
}

SelectionTreeNode* SelectionTree::Insert(SelectionTreeNode* node, LoanBookData* newData)
{
	// if stree is empty
	if (node == nullptr)
	{
		SelectionTreeNode* newNode = new SelectionTreeNode();
		newNode->setBookData(newData);
		return newNode;
	}
	
	// insert direction decision
	if (newData->getName() < node->getBookData()->getName())
		node->setLeftChild(Insert(node->getLeftChild(), newData));
	else
		node->setRightChild(Insert(node->getRightChild(), newData));

	// update heap if necessary
	if (node->getHeap() != NULL)
		node->getHeap()->Insert(newData);

	return node;
}

// move to left most node of stree
SelectionTreeNode* SelectionTree::findMinNode(SelectionTreeNode* node)
{
	while (node->getLeftChild() != nullptr)
		node = node->getLeftChild();

	return node;
}

bool SelectionTree::Delete()
{
	if (root != NULL)
	{
		root = Delete(root, root->getBookData()->getName());
		return true;
	}
	else 
	{
		throw "bool SelectionTree::Delete() - stree is empty.";
		return false;
	}
}

SelectionTreeNode* SelectionTree::Delete(SelectionTreeNode* node, string name)
{
	// there is no node to delete
	if (node == NULL)
		return node;

	// search for the node to be deleted
	if (name < node->getBookData()->getName())
		node->setLeftChild(Delete(node->getLeftChild(), name));
	else if (name > node->getBookData()->getName())
		node->setRightChild(Delete(node->getLeftChild(), name));
	else // node to be deleted is found
	{
		if (node->getLeftChild() == NULL)
		{
			SelectionTreeNode* temp = node->getRightChild();
			delete node;
			return temp;
		}
		else if (node->getRightChild() == NULL)
		{
			SelectionTreeNode* temp = node->getLeftChild();
			delete node;
			return temp;
		}
		// node has two children
		SelectionTreeNode* temp = findMinNode(node->getRightChild());
		node->setBookData(temp->getBookData());
		node->setRightChild(Delete(node->getRightChild(), temp->getBookData()->getName()));
	}

	// update heap if necessary
	if (node->getHeap() != NULL)
		node->getHeap()->heapifyUp(node->getHeap()->getRoot());

	return node;
}

bool SelectionTree::printBookData(int bookCode)
{
	printBookData(root, bookCode);
	return true;
}

void SelectionTree::printBookData(SelectionTreeNode* node, int bookCode)
{
	if (node == NULL)
	{
		throw "void SelectionTree::printBookData(SelectionTreeNode* node, int bookCode) - stree is empty.";
		return;
	}

	if (bookCode < node->getBookData()->getCode())
		printBookData(node->getLeftChild(), bookCode);
	else if (bookCode > node->getBookData()->getCode())
		printBookData(node->getRightChild(), bookCode);
	else
	{
		if (node->getLeftChild() != NULL && node->getRightChild()->getHeap() != NULL);
			//node->getLeftChild()->getHeap()->printHeap();
		else
			throw "void SelectionTree::printBookData(SelectionTreeNode* node, int bookCode) - No heap data";
	}
}