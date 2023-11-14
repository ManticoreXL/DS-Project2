#include "SelectionTree.h"

bool SelectionTree::Insert(LoanBookData *newData)
{
	return false;
}

SelectionTreeNode* SelectionTree::Insert(SelectionTreeNode* node, LoanBookData* newData)
{
	return nullptr;
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
	return false;
}

SelectionTreeNode* SelectionTree::Delete(SelectionTreeNode* node, string name)
{
	return nullptr;
}

bool SelectionTree::printBookData(int bookCode)
{
	return false;
}

void SelectionTree::printBookData(SelectionTreeNode* node, int bookCode)
{
	
}