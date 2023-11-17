#pragma once
#include "LoanBookData.h"
#include "LoanBookHeapNode.h"

class LoanBookHeap
{
private:
    LoanBookHeapNode *root;
    ofstream *fout;

public:
    LoanBookHeap(ofstream *fout) 
    { 
        this->root = nullptr;
        this->fout = fout;
    };

    ~LoanBookHeap() { recursive_delete(root); }

    void recursive_delete(LoanBookHeapNode* node)
    {
        // delete by inorder traversal
        if (node != nullptr)
        {
            recursive_delete(node->getLeftChild());
            LoanBookHeapNode* temp = node->getRightChild();
            delete node;
            recursive_delete(temp);
        }
    }

    void setRoot(LoanBookHeapNode *pN) { this->root = pN; }
    LoanBookHeapNode *getRoot() { return root; }

    void heapifyUp(LoanBookHeapNode *pN);
    void heapifyDown(LoanBookHeapNode *pN);

    bool Insert(LoanBookData *data);
    LoanBookHeapNode* Insert(LoanBookHeapNode *node, LoanBookData *data);

    bool Delete();

    void printHeap();
    void recursive_print(LoanBookHeapNode *node);

    void swapData(LoanBookData *data1, LoanBookData *data2);

    LoanBookHeapNode* findLastNode(LoanBookHeapNode* node);
};
