#pragma once
#include "SelectionTreeNode.h"
#include <fstream>
#include <iostream>

class SelectionTree
{
private:
    SelectionTreeNode *root;
    ofstream *fout;
    vector<SelectionTreeNode*> runs;

public:
    SelectionTree(ofstream *fout)
    {
        this->fout = fout;
        this->root = new SelectionTreeNode();
        INIT(root, 3);        
    }

    void INIT(SelectionTreeNode* node, int height)
    {
        // create selection tree node and heaps
        if (height == 0)
        {
            LoanBookHeap* heap = new LoanBookHeap(fout);
            runs.push_back(node);
            node->setHeap(heap);
        }
        else
        {
            node->setLeftChild(new SelectionTreeNode);
            node->getLeftChild()->setParent(node);
            node->setRightChild(new SelectionTreeNode);
            node->getRightChild()->setParent(node);
            INIT(node->getLeftChild(), height - 1);
            INIT(node->getRightChild(), height - 1);
        }
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