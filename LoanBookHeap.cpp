#include "LoanBookHeap.h"

void LoanBookHeap::heapifyUp(LoanBookHeapNode *pN)
{
}

void LoanBookHeap::heapifyDown(LoanBookHeapNode *pN)
{
}

bool LoanBookHeap::Insert(LoanBookData *data)
{
    if (root == nullptr)
    {
        root = new LoanBookHeapNode(data);
        return true;
    }
    else
    {
        LoanBookHeapNode *curr = root;
    }
}