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

    ~SelectionTree() { recursive_delete(root); }

    void recursive_delete(SelectionTreeNode *node)
    {
        // delete by inorder traversal
        if (node != nullptr)
        {
            recursive_delete(node->getLeftChild());
            SelectionTreeNode* temp = node->getRightChild();
            delete node;
            recursive_delete(temp);
        }
    }

    void setRoot(SelectionTreeNode *pN) { this->root = pN; }
    SelectionTreeNode *getRoot() { return root; }

    bool Insert(LoanBookData *newData);
    bool Delete();
    bool printBookData(int bookCode);
};