#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
    Node(int _key) : key(_key), left(NULL), right(NULL) {}
};

Node* insert(Node* current, int key) {
    if (current == NULL) {
       return new Node(key);
    }
    if (key < current->key) {
        current->left = insert(current->left, key);
    } else {
        current->right = insert(current->right, key);
    }
    return current;
}

bool find(Node* current, int key) {
    if (current == NULL) return false;
    if (current->key == key) return true;
    if (current->key > key) return find(current->left, key);
    return find(current->right, key);
}

bool findIter(Node* current, int key) {
    Node* el = current;
    while (el != NULL) {
       if (el->key==key) return true;
       // cout<<el->key<<" ";
       if (el->key > key) el = el->left;
       else el = el->right;
    }
    return false;
}

int getHeight(Node* current) {
    if (current == NULL) return 0;
    return 1 + max(getHeight(current->left), getHeight(current->right));
}

int getMin(Node* current) {
    if (current == NULL) return 999999; // edge scenario
    if (current->left == NULL) return current->key;
    return getMin(current->left);
}

Node* erase(Node* current, int key) {
    if (current == NULL) {
        return NULL; // case for no existing element
    } else if (key > current->key) {
        current->right = erase(current->right, key);
    } else if(key < current->key) {
        current->left = erase(current->left, key);
    } else {
        if (current -> left == NULL || current->right == NULL) { // We have zero or one child
            Node* child = current -> left == NULL ? current->right : current->left;
            delete current;
            return child;
        } else { // case when we have 2 children
            current->key = getMin(current->right);
            current->right = erase(current->right, current->key);
        }
    }
    return current;
}

void inOrderDisplay(Node* current) {
    if (current == NULL) return;
    inOrderDisplay(current->left);
    cout<<current->key<<" ";
    inOrderDisplay(current->right);
    return;
}

void preOrderDisplay(Node* current) {
    if (current == NULL) return;
    cout<<current->key<<" ";
    preOrderDisplay(current->left);
    preOrderDisplay(current->right);
    return;
}


void printAllPathsTree(Node* current, vector<int> &s) {
    if (current == NULL) {
        return;
    }
    s.push_back(current->key);

    if (current->left == NULL && current->right == NULL) {
        for (int i : s) {cout<<"->"<<i;}
        cout<<endl;
    }

    printAllPathsTree(current->left, s);
    printAllPathsTree(current->right, s);

    s.pop_back();
    return;
}

Node* commonAcc(Node* current, int key1, int key2) {
    if (current == NULL) return NULL;
    if (find(current->left, key1) && find(current->left, key2)) { // Can we optimise this one?
        return commonAcc(current->left, key1, key2);
    }
    if (find(current->right, key1) && find(current->right, key2)) {
        return commonAcc(current->right, key1, key2);
    }
    return current;
}

int getLongestPath(Node* current, int &result) {
    if (current == NULL) return 0;
    int leftSolution = getLongestPath(current->left, result);
    int rightSolution = getLongestPath(current->right, result);
    int maxResult = leftSolution + rightSolution + 1;
    result = max(result, maxResult);
    return max(leftSolution, rightSolution) + 1;

}


int main() {
    Node* Tree = new Node(3);
    insert(Tree,5);
    insert(Tree,-7);
    insert(Tree,9);
    insert(Tree,13);
    insert(Tree,6);
    insert(Tree,20);
    insert(Tree,1);
    insert(Tree,4);
    insert(Tree,-9);

    //insert(Tree,66);
//    cout<<find(Tree, 6)<<endl;
//    cout<<find(Tree, 25)<<endl;
//    cout<<findIter(Tree, 6)<<endl;
//    cout<<findIter(Tree, 25)<<endl;
   // cout<<getHeight(Tree);
   //cout<<getMin(Tree);
    inOrderDisplay(Tree);
    cout<<endl;
    preOrderDisplay(Tree);
    cout<<endl;
//    erase(Tree, 9);
//    erase(Tree, 3);
//
//    erase(Tree, 5);
//    inOrderDisplay(Tree);
//    Node* res = commonAcc(Tree, -9, 1);
//    cout<<res->key<<endl;
//    res = commonAcc(Tree, -9, 20);
//    cout<<res->key<<endl;
//
//    vector <int> s;
//    printAllPathsTree(Tree, s);
int res = 0;
    getLongestPath(Tree, res);
    cout<<res<<endl;
   return 0;
}
