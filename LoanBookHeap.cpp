#include "LoanBookHeap.h"
#include <queue>

void LoanBookHeap::heapifyUp(LoanBookHeapNode *pN)
{
    // heapify up for insertion
    while (pN->getLeftChild() != nullptr || pN->getRightChild() != nullptr)
    {
        LoanBookHeapNode* minChild = (pN->getRightChild() == nullptr || pN->getLeftChild() == nullptr
            && pN->getBookData()->getName() < pN->getBookData()->getName())
            ? pN->getLeftChild() : pN->getRightChild();

        if (minChild != nullptr && minChild->getBookData()->getName() > pN->getBookData()->getName())
        {
            swapData(pN->getBookData(), minChild->getBookData());
            pN = minChild;
        }
        else break;
    }
}

void LoanBookHeap::heapifyDown(LoanBookHeapNode *pN)
{
    // heapify up for deletion
    while (pN->getLeftChild() != nullptr || pN->getRightChild() != nullptr)
    {
        LoanBookHeapNode* minChild = (pN->getRightChild() == nullptr || pN->getLeftChild() == nullptr
            && pN->getBookData()->getName() < pN->getBookData()->getName())
            ? pN->getLeftChild() : pN->getRightChild();

        if (minChild != nullptr && minChild->getBookData()->getName() > pN->getBookData()->getName())
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
    {
        // insert left
        node->setLeftChild(Insert(node->getLeftChild(), data));
        node->getLeftChild()->setParent(node);
    }
    else
    {
        // insert right
        node->setRightChild(Insert(node->getRightChild(), data));
        node->getRightChild()->setParent(node);
    }

    // return node
    return node;
}

bool LoanBookHeap::Delete()
{
    if (root == nullptr)
    {
        throw "bool LoanBookHeap::Delete() - heap is empty.";
        return false;
    }

    // find last location of heap
    LoanBookHeapNode* curr = findLastNode(root);

    if (curr == root)
    {
        // simple delete
        delete root;
        root = nullptr;
    }
    else
    {
        // find successor and delete
        LoanBookHeapNode* pNode = curr->getParent();

        if (pNode->getLeftChild() == curr)
            pNode->setLeftChild(nullptr);
        else
            pNode->setRightChild(nullptr);

        swapData(curr->getBookData(), pNode->getBookData());

        delete curr;
    }
    
    // resort heap
    heapifyDown(root);

    return true;
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
        if (node->getLeftChild() != nullptr)
            recursive_print(node->getLeftChild());
        if (node->getBookData() != nullptr)
            *fout << *(node->getBookData());
        if(node->getRightChild() != nullptr)
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

LoanBookHeapNode* LoanBookHeap::findLastNode(LoanBookHeapNode* node)
{
    // find last heap node
    if (node == nullptr)
        return nullptr;

    // use queue to save backtracking point
    queue<LoanBookHeapNode*> q;
    q.push(node);

    LoanBookHeapNode* lastNode = nullptr;

    // find last node
    while (!q.empty())
    {
        // save backtracking pount
        lastNode = q.front();
        q.pop();

        // push left child
        if (lastNode->getLeftChild() != nullptr)
            q.push(lastNode->getLeftChild());
        // push right child
        if (lastNode->getRightChild() != nullptr)
            q.push(lastNode->getRightChild());
    }

    return lastNode;
}