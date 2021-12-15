#include <iostream>

// -------------------------------- NODE ------------------------------------

template<typename T>
BinarySearchTree<T>::BSTNode::BSTNode(T data, BSTNode* left, BSTNode* right): data(data), left(NULL), right(NULL) {}

// -------------------------------- TREE ------------------------------------

// ---------------------------- CLEAR HELPER

template<typename T>
void BinarySearchTree<T>::clear() {
	clearSubtree(root);
}

template<typename T>
void BinarySearchTree<T>::clearSubtree(BSTNode*& currRoot) {
	if(currRoot == NULL) {
		return;
	}

	if(currRoot->left != NULL) {
		clearSubtree(currRoot->left);
	}

	if(currRoot->right != NULL) {
		clearSubtree(currRoot->right);
	}

	delete currRoot;
	currRoot = NULL;
}

// --------------------------- COPY HELPER

template<typename T>
void BinarySearchTree<T>::copy(const BinarySearchTree& other) {
	clear();
	copySubtree(root, other.root);
}

template<typename T>
void BinarySearchTree<T>::copySubtree(BSTNode*& currRoot, BSTNode* otherCurrRoot) {
	if(otherCurrRoot == NULL) {
		return;
	}

	currRoot = new BSTNode(otherCurrRoot->data);

	if(otherCurrRoot->left != NULL) {
		copySubtree(currRoot->left, otherCurrRoot->left);
	}

	if(otherCurrRoot->right != NULL) {
		copySubtree(currRoot->right, otherCurrRoot->right);
	}
}

// --------------------------- BIG FOUR

template<typename T>
BinarySearchTree<T>::BinarySearchTree(): root(NULL) {}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& other): root(NULL) {
	copy(other);
}

template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree& other) {
	if(this != &other) {
		copy(other);
	}
	return *this;
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
	clear();
}

// ---------------------------- ADD

template<typename T>
void BinarySearchTree<T>::add(const T& data) {
	add(data, root);
}

template<typename T>
void BinarySearchTree<T>::add(const T& data, BSTNode*& currRoot) {
	if(currRoot == NULL) {
		currRoot = new BSTNode(data);
		return;
	}

	if(currRoot->data < data) {
		return add(data, currRoot->right);
	} else {
		return add(data, currRoot->left);
	}
}

// ------------------------- REMOVE

template<typename T>
void BinarySearchTree<T>::remove(const T& data) {
    if(root->data != data) {
        return remove(data, root);
    }

    root = removeBSTNode(root);
}

template<typename T>
void BinarySearchTree<T>::remove(const T& data, BSTNode*& currRoot) {
	if(currRoot == NULL) {
		throw;
	}

	if(currRoot->left != NULL && currRoot->left->data == data) {
		currRoot->left = removeBSTNode(currRoot->left);
        return;
	} else if(currRoot->right != NULL && currRoot->right->data == data) {
		currRoot->right = removeBSTNode(currRoot->right);
		return;
	}

	if(currRoot->data < data) {
		return remove(data, currRoot->right);
	} else {
		return remove(data, currRoot->left);
	}
}

template<typename T>
typename BinarySearchTree<T>::BSTNode * BinarySearchTree<T>::removeBSTNode(BinarySearchTree<T>::BSTNode* node) {
	if(node->left != NULL && node->right != NULL) {
		node->data = getAndRemoveMin(node->right, node);
		return node;
	}

	if(node->left != NULL || node->right != NULL) {
		BinarySearchTree<T>::BSTNode* newRoot = (node->left != NULL) ? node->left : node->right;
		delete node;
		return newRoot;
	}

	delete node;
	return NULL;
}

template<typename T>
T BinarySearchTree<T>::getAndRemoveMin(BSTNode* node, BSTNode*& parent) {
	if(node->left != NULL) {
		if(node->left->left == NULL) {
			T oldBSTNodeValue = node->left->data;
			node->left = node->left->right;
			delete node->left;
			return oldBSTNodeValue;
		} else {
			return getAndRemoveMin(node->left, node);
		}
	} else {
		T oldBSTNodeValue = node->data;
		parent->right = node->right;
		delete node;
		return oldBSTNodeValue;
	}
}

// ------------------------ PRINT

template<typename T>
void BinarySearchTree<T>::print() {
	if(root != NULL) {
		printSubtree(root);
	}
}

template<typename T>
void BinarySearchTree<T>::printSubtree(BSTNode* currRoot) {
	if(currRoot->left != NULL) {
		printSubtree(currRoot->left);
	}
	std::cout<< currRoot->data<< std::endl;
	if(currRoot->right != NULL) {
		printSubtree(currRoot->right);
	}
}

// ------------------------ FIND

template<typename T>
T* BinarySearchTree<T>::getElement(const T& data) {
	return getElement(data, root);
}

template<typename T>
T* BinarySearchTree<T>::getElement(const T& data, BSTNode* currRoot) {
	if(currRoot == NULL) {
		return NULL;
	}

	if(currRoot->data < data) {
		return getElement(data, currRoot->right);
	} else if(currRoot->data > data) {
		return getElement(data, currRoot->left);
	} else {
		return &(currRoot->data);
	}
}


