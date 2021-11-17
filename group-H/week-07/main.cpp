#include <iostream>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
    Node(int value) : key(value), left(NULL), right(NULL) {}
};

Node* insert(Node* current, int key) {
    if (current == NULL) {
        return new Node(key);
    }
    if (key >= current->key) {
        current->right = insert(current->right, key);
    } else {
        current->left = insert(current->left, key);
    }
    return current;
}

Node* find(Node* current, int key) {
    if (current == NULL) {
        return NULL;
    }
    if(current->key == key) {
        return current;
    }
    if (key >= current->key) {
        return find(current->right, key);
    }
    return find(current->left, key);
}

int getMax(Node* current) {
    if (current == NULL) { return -1; } // edge scenario
    if (current->right == NULL) {
        return current->key;
    }
    return getMax(current->right);
}

int getMaxIter(Node* current) {
    if (current == NULL) { return -1; } // edge scenario
    while(current->right != NULL) {
        current=current->right;
    }
    return current->key;
}

int getHeight (Node* current) {
    if (current == NULL) return 0;
    return 1 + max(getHeight(current->left), getHeight(current->right));
}

int main() {
    Node* node = new Node(4);
    insert(node, 2);
    insert(node, 6);

    insert(node, 9);
    insert(node, 5);
    cout<<(find(node, 6) != NULL)<<endl;

    cout<<(find(node, 100) != NULL)<<endl;
    cout<<getMax(node)<<endl;
    cout<<getMaxIter(node)<<endl;
    cout<<getHeight(node)<<endl;
    return 0;
}
