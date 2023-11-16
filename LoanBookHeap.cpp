#include "LoanBookHeap.h"

void LoanBookHeap::heapifyUp(LoanBookHeapNode *pN)
{
    // heapify up for insertion
    while (pN->getLeftChild() != nullptr || pN->getRightChild() != nullptr)
    {
        LoanBookHeapNode* minChild = (pN->getRightChild() == nullptr || pN->getLeftChild() == nullptr
            && pN->getBookData()->getName() < pN->getBookData()->getName())
            ? pN->getLeftChild() : pN->getRightChild();

        if (minChild != nullptr && minChild->getBookData()->getName() < pN->getBookData()->getName())
        {
            swapData(pN->getBookData(), minChild->getBookData());
            pN = minChild;
        }
        else break;
    }
}

void LoanBookHeap::heapifyDown(LoanBookHeapNode *pN)
{
    // heapify for deletion
    while (pN->getLeftChild() != nullptr || pN->getRightChild() != nullptr)
    {
        LoanBookHeapNode* minChild = (pN->getRightChild() == nullptr || pN->getLeftChild() == nullptr
            && pN->getBookData()->getName() < pN->getBookData()->getName())
            ? pN->getLeftChild() : pN->getRightChild();

        if (minChild != nullptr && minChild->getBookData()->getName() < pN->getBookData()->getName())
        {
            swapData(pN->getBookData(), minChild->getBookData());
            pN = minChild;
        }
        else break;
    }
}

bool LoanBookHeap::Insert(LoanBookData* data)
{
    // insert and heapify up
    root = Insert(root, data);
    heapifyUp(root);
    return true;
}

LoanBookHeapNode* LoanBookHeap::Insert(LoanBookHeapNode* node, LoanBookData* data)
{
    // heap is empty, create new node
    if (node == nullptr)
        return new LoanBookHeapNode(data);

    // recursive call at correct direction
    if (data->getName() < node->getBookData()->getName())
        node->setLeftChild(Insert(node->getLeftChild(), data));
    else
        node->setRightChild(Insert(node->getRightChild(), data));

    // return node
    return node;
}

void LoanBookHeap::printHeap()
{
    // use recursive print function
    *fout << "========PRINT_ST========" << endl;
    recursive_print(root);
    *fout << "=========================" << endl << endl;
}

void LoanBookHeap::recursive_print(LoanBookHeapNode* node)
{
    // print heap by inorder traversal
    if (node != nullptr)
    {
        recursive_print(node->getLeftChild());
        *fout << *(node->getBookData());
        recursive_print(node->getRightChild());
    }
}

void LoanBookHeap::swapData(LoanBookData* data1, LoanBookData* data2)
{
    // swap LoanBookData
    LoanBookData* temp = data1;
    data2 = data1;
    data1 = temp;
}