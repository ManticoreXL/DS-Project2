#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "LoanBookData.h"
#include <fstream>
#include <iostream>

class BpTree
{
private:
	BpTreeNode *root;
	int order; // m children
	ofstream *fout;
	int cond;

public:
	BpTree(ofstream *fout, int order = 3)
	{
		root = NULL;
		this->order = order;
		this->fout = fout;
		cond = ceil(order - 1) / 2.0;
	}

	~BpTree()
	{
		recursive_delete(root);
	}

	void recursive_delete(BpTreeNode* node)
	{
		if (node)
		{
			recursive_delete(node->getMostLeftChild());
			if (node->getIndexMap())
				for (auto i = node->getIndexMap()->begin(); i != node->getIndexMap()->end(); i++)
					recursive_delete(i->second);
			else if (node->getDataMap())
				for (auto i = node->getDataMap()->begin(); i != node->getDataMap()->end(); i++)
					delete i->second;

			delete node;			
		}
	}

	/* essential */
	bool Insert(LoanBookData *newData);
	bool excessDataNode(BpTreeNode *pDataNode);
	bool excessIndexNode(BpTreeNode *pIndexNode);
	void splitDataNode(BpTreeNode *pDataNode);
	void splitIndexNode(BpTreeNode *pIndexNode);
	BpTreeNode *getRoot() { return root; }
	BpTreeNode *searchDataNode(string name);

	bool searchBook(string name);
	bool searchRange(string &start, string &end);

	bool linearPrint();
};

#endif
