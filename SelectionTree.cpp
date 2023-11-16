#include "SelectionTree.h"

bool SelectionTree::Insert(LoanBookData *newData)
{
	SelectionTreeNode* curr = root;

	if (curr == nullptr)
	{
		// create new node, heap. and set heap link.
		curr = new SelectionTreeNode;
		curr->setBookData(newData);

		LoanBookHeap* newHeap = new LoanBookHeap(fout);
		newHeap->Insert(newData);
		curr->setHeap(newHeap);
		return true;
	}

	// move to insertion location
	while (curr != nullptr)
	{
		if (curr->getLeftChild() && curr->getRightChild())
		{
			// curr has two children
			if (curr->getCode() > newData->getCode())
				curr = curr->getLeftChild();
			else if (curr->getCode() < newData->getCode())
				curr = curr->getRightChild();
			else break;
		}
		else
			// curr has a child or no child
			curr = (curr->getLeftChild() == nullptr) ? curr->getRightChild() : curr->getLeftChild();
	}

	if (curr->getCode() == newData->getCode())
	{
		// run already exists. insert data into heap.
		curr->getHeap()->Insert(newData);
	}
	else
	{
		// run does not exists. create new heap.
		if (curr->getParent() == nullptr)
		{
			// create new node and parent node
			SelectionTreeNode* pNode = new SelectionTreeNode();
			SelectionTreeNode* node = new SelectionTreeNode();
			node->setBookData(newData);

			// set link field
			curr->setParent(pNode);
			node->setParent(pNode);

			if (node->getCode() > curr->getCode())
			{
				pNode->setLeftChild(curr);
				pNode->setRightChild(node);
			}
			else
			{
				pNode->setLeftChild(node);
				pNode->setRightChild(curr);
			}

			// create new heap and set link
			LoanBookHeap* newHeap = new LoanBookHeap(fout);
			newHeap->Insert(newData);
			node->setHeap(newHeap);

			return true;
		}
		else
		{
			SelectionTreeNode* pNode = curr->getParent();
			if (pNode->getLeftChild() && pNode->getRightChild())
			{
				// todo: go upper 2 more level
			}
			else
			{
				curr = (pNode->getLeftChild() == nullptr)
					? pNode->getRightChild()
					: pNode->getLeftChild();

				// create new node and set data
				curr = new SelectionTreeNode();
				curr->setBookData(newData);
				curr->setParent(pNode);

				// create new heap and set link
				LoanBookHeap* newHeap = new LoanBookHeap(fout);
				newHeap->Insert(newData);
				curr->setHeap(newHeap);
			}
		}
	}

	return false;
}

bool SelectionTree::Delete()
{
	// todo
	return false;
}

bool SelectionTree::printBookData(int bookCode)
{
	SelectionTreeNode* curr = root;

	if (curr == nullptr)
	{
		throw "bool SelectionTree::printBookData(int bookCode) - stree is empty.";
		return false;
	}

	// search node that have same code
	while (curr != nullptr)
	{
		if (curr->getBookData()->getCode() < bookCode)
			curr = curr->getLeftChild();
		else if (curr->getBookData()->getCode() > bookCode)
			curr = curr->getRightChild();
		else // found. print heap
			curr->getHeap()->printHeap();
	}

	return false;
}