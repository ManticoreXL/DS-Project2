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
    
    LoanBookHeapNode* curr = root;

    while(curr != nullptr)
    {
        // swap case
        if(curr->getBookData()->getName() > data->getName())
        {
            LoanBookData *temp = curr->getBookData();
            curr->setBookData(data);
            data = temp;
        }
        // downing case
        else if (curr->getBookData()->getName() < data->getName())
        {
            // go to rightchild
            if(curr->getLeftChild()->getBookData()->getName() < data->getName())
                curr = curr->getRightChild();
            // go to leftchild
            else
                curr = curr->getLeftChild();
        }
        // change case
        else
        {
            curr->setBookData(data);
        }
    }
    return false;
}