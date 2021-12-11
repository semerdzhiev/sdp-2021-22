#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
    int height;
    Node(int _key) : key(_key), left(NULL), right(NULL), height(0) {}
};

int getHeight(Node* current) {
    if (current == NULL) return 0;
    return current->height;
    //return 1 + std::max(getHeight(current->left), getHeight(current->right));
}

Node* rightRotate(Node* root) {
    Node* leftChild = root->left;
    Node* T2 = leftChild->right;

    leftChild->right = root;
    root->left = T2;
    // we should calculate first the height of root since recursive definition
    root -> height = 1 + max(getHeight(root->left), getHeight(root->right));
    leftChild -> height = 1 + max(getHeight(leftChild->left), getHeight(leftChild->right));
    return leftChild;
}

Node* leftRotate(Node* root) {
    Node* rightChild = root->right;
    Node* T2 = rightChild->left;

    rightChild->left = root;
    root->right = T2;
    // we should calculate first the height of root since recursive definition
    root -> height = 1 + max(getHeight(root->left), getHeight(root->right));
    rightChild -> height = 1 + max(getHeight(rightChild->left), getHeight(rightChild->right));
    return rightChild;
}

int getBalance(Node* root) {
    if (root == NULL) return 0;
    return getHeight(root->left) - getHeight(root->right);
} // 0, 1, -1 . For 2/-2 we should make rotation


// Not working so well with additional adding of same key, because of the rotation
// It could be broken because of the rule T1 < T2 <= T3
Node* insert(Node* current, int key) {
    if (current == NULL) {
        return new Node(key);
    }
    if (key < current->key) {
        current->left = insert(current->left, key);
    } else {
        current->right = insert(current->right, key);
    }

    current->height = 1 + max(getHeight(current->left), getHeight(current->right));

    int balance = getBalance(current);

    // if (balance > 1) {...}
    if (balance > 1 && key < current->left->key) {
        return rightRotate(current);
    }

    //if (balance < -1) {...}
    if (balance < -1 && key > current->right->key) {
        return leftRotate(current);
    }

    if (balance > 1 && key > current->left->key) {
        current->left = leftRotate(current->left);
        return rightRotate(current);
    }

    if (balance < -1 && key < current->right->key) {
        current->right = rightRotate(current->right);
        return leftRotate(current);
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
        if (current -> left == NULL || current->right == NULL) { // We have zero on one child
            Node* child = current -> left == NULL ? current->right : current->left;
            delete current;
            return child;
        } else { // case when we have 2 children
            current->key = getMin(current->right);
            current->right = erase(current->right, current->key);
        }
    }
    if (current == NULL) { return current;}

    current->height = 1 + max(getHeight(current->left), getHeight(current->right));

    int balance = getBalance(current);

    if (balance > 1 && getBalance(current->left) >= 0) {
        return rightRotate(current);
    }

    if (balance > 1 && getBalance(current->left) < 0) {
        current->left = leftRotate(current->left);
        return rightRotate(current);
    }

    if (balance < -1 && getBalance(current->right) <= 0) {
        return leftRotate(current);
    }

    if (balance < -1  && getBalance(current->right) > 0) {
        current->right = rightRotate(current->right);
        return leftRotate(current);
    }

    return current;
}

void inOrderDisplay(Node* current) {
    if (current == NULL) return;
    inOrderDisplay(current->left);
    cout<<"("<<current->key<<" "<<current->height<<") ";
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
    Node* Tree = new Node(15);
    Tree = insert(Tree, 10);
    Tree = insert(Tree, 8);
    Tree = insert(Tree, 7);
    Tree = insert(Tree, 6);
    Tree = insert(Tree, 5);
    Tree = insert(Tree, 4);
    Tree = insert(Tree, 3);
    Tree = insert(Tree, 31);
    Tree = insert(Tree, 32);
    Tree = insert(Tree, 33);
    Tree = insert(Tree, 34);
    Tree = insert(Tree, 35);
    Tree = insert(Tree, 36);
    Tree = insert(Tree, 12);
    Tree = insert(Tree, 37);
    Tree = insert(Tree, 39);
    cout<<getHeight(Tree)<<endl;
    vector<int> s;
    printAllPathsTree(Tree, s);
    // Why we display height in this way?
    inOrderDisplay(Tree);
    cout<<endl;
    Tree = erase(Tree, 7);
    printAllPathsTree(Tree, s);
//    cout<<find(Tree, 6)<<endl;
//    cout<<find(Tree, 25)<<endl;
//    cout<<findIter(Tree, 6)<<endl;
//    cout<<findIter(Tree, 25)<<endl;
//    cout<<getHeight(Tree);
//    cout<<getMin(Tree);
//    inOrderDisplay(Tree);
//    cout<<endl;
//    preOrderDisplay(Tree);
//    cout<<endl;
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

//   int res = 0;
//   getLongestPath(Tree, res);
//   cout<<res<<endl;
//   Memory clean up....
    return 0;
}