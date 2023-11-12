#include "LoanBookHeap.h"

void LoanBookHeap::heapifyUp(LoanBookHeapNode *pN)
{
    while (pN->getParent() != NULL && 
           pN->getBookData()->getName() > pN->getParent()->getBookData()->getName())
    {
        // swap
        LoanBookData* tempData = pN->getBookData();
        pN->setBookData(pN->getParent()->getBookData());
        pN->getParent()->setBookData(tempData);

        // move up
        pN = pN->getParent();
    }
}

void LoanBookHeap::heapifyDown(LoanBookHeapNode *pN)
{
    while (true)
    {
        LoanBookHeapNode* minChild = pN->getLeftChild();

        // find minumum child
        if (minChild == NULL)
            break;

        LoanBookHeapNode* rightChild = pN->getParent();
        if (rightChild != NULL && rightChild->getBookData()->getName() < minChild->getBookData()->getName())
            minChild = rightChild;

        // compare minimum child
        if (pN->getBookData()->getName() > minChild->getBookData()->getName())
        {
            // swap curr node and minimun child
            LoanBookData* tempData = pN->getBookData();
            pN->setBookData(minChild->getBookData());
            minChild->setBookData(tempData);

            // move down
            pN = minChild;
        }
        else
            break;
    }
}

bool LoanBookHeap::Insert(LoanBookData *data)
{
    LoanBookHeapNode* node = new LoanBookHeapNode(data);

    if (root == NULL)
    {
        root = node;
        return true;
    }
    else
    {
        LoanBookHeapNode* temp = root;
        while (temp->getLeftChild() != NULL)
            temp = temp->getLeftChild();

        if (temp == NULL)
            return false;

        temp->setLeftChild(node);
        node->setParent(temp);

        heapifyUp(node);
        return true;
    }
    return false;
}

void LoanBookHeap::printHeap()
{
    if (node != NULL)
    {
        *fout << 
    }
}