#include <iostream>

struct Node
{
    int data;
    Node* pNext = nullptr;
};

struct FList
{
    void push_front( int elem )
    {
        pHead = new Node { elem, pHead };
    }

    void pop_front()
    {
        if ( pHead == nullptr )
            throw std::logic_error( "...." );

        Node*   temp    = pHead;
        pHead   = pHead->pNext;
        delete temp;
    }

    Node* insert_after( Node* pAfter, int elem )
    {
        return pAfter->pNext   = new Node { elem, pAfter->pNext };
    }

    int&        front()         { return pHead->data; }
    const int&  front() const   { return pHead->data; }

    Node*   pHead   = nullptr;
};

int main()
{
    FList   lst;

    for ( size_t i = 0; i < 10; i++ )
    {
        lst.push_front( i );
    }

    Node* pCurr = lst.pHead;
    for ( ; pCurr; pCurr = pCurr->pNext )
    {
        std::cout << pCurr->data << ' ';
    }

    // TODO: Delete memory

    return 0;
}
