#pragma once
#include "SelectionTreeNode.h"

#include <fstream>
#include <iostream>

class SelectionTree
{
private:
    SelectionTreeNode *root;
    ofstream *fout;

public:
    SelectionTree(ofstream *fout)
    {
        this->root = NULL;
        this->fout = fout;
    }

    ~SelectionTree()
    {
        inorder_delete(root);
    }

    void inorder_delete(SelectionTreeNode *node)
    {
        delete node->getLeftChild();
        SelectionTreeNode *temp = node->getRightChild();
        delete node;
        delete temp;
    }

    void setRoot(SelectionTreeNode *pN) { this->root = pN; }
    SelectionTreeNode *getRoot() { return root; }

    bool Insert(LoanBookData *newData);
    bool Delete();
    bool printBookData(int bookCode);
};