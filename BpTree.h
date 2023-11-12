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

public:
	BpTree(ofstream *fout, int order = 3)
	{
		root = NULL;
		this->order = order;
		this->fout = fout;
	}

	~BpTree()
	{
	}

	/* essential */
	bool Insert(LoanBookData *newData);
	bool Insert(BpTreeNode* node, LoanBookData* newData);
	bool excessDataNode(BpTreeNode *pDataNode);
	bool excessIndexNode(BpTreeNode *pIndexNode);
	bool splitDataNode(BpTreeNode *pDataNode);
	bool splitIndexNode(BpTreeNode *pIndexNode);
	BpTreeNode *getRoot() { return root; }
	BpTreeNode *searchDataNode(string name);

	bool searchBook(string name);
	bool searchRange(string start, string end);

	bool linearPrint();
};

#endif
