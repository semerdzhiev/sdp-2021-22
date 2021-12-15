#include <iostream>

#include "minHeap.h"
#include "Tree.hpp"
#include "BinaryTree.h"

using namespace std;

int main() {
    /*MinHeap<int> pq;

    pq.push(3);
    pq.push(2);
    pq.push(15);

    cout << "Size is " << pq.size() << endl;
    cout << pq.top() << " ";
    pq.pop();

    cout << pq.top() << " ";
    pq.pop();

    pq.push(5);
    pq.push(4);
    pq.push(45);

    cout << endl << "Size is " << pq.size() << endl;
    for(; !pq.empty(); pq.pop()) {
        cout << pq.top() << " ";
    }*/

    BinaryTree<int> bt;
    bt.head =
        new Node<int>(5,
            new Node<int>(3, 
                new Node<int>(1, nullptr, nullptr),
                new Node<int>(4, nullptr, nullptr)
            ),
            new Node<int>(7, nullptr, nullptr)
        );
    cout << isBST(bt.head)<< endl;

    Tree<int> t;
    t.head = new Tree<int>::Node(5);
    for (int i = 0; i < 10; ++i) {
        t.head->children.push_back(new Tree<int>::Node(i*5 + 1));
    }
    t.head->children[4]->children.push_back(new Tree<int>::Node(10));

    //t.print();

    return 0;
}
