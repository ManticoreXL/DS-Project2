#include "LoanBookHeap.h"

void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) {

}

void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) {

}

bool LoanBookHeap::Insert(LoanBookData* data) {
    if(root == nullptr){   
        root = new LoanBookHeapNode(data);
        return true;
    }

    string dname = data->getName();
    LoanBookHeapNode *temp = root;

    while(temp != nullptr){
        if(temp->getBookData()->getName() > dname) {
            temp = temp->getLeftChild();
        }
        else {
            temp = temp->getRightChild();
        }
    }

    while()
}