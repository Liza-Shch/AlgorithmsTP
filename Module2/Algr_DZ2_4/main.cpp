#include <iostream>
#include <cassert>

template <class T>
struct Node {
    T key;
    int height;
    int count;
    Node* left;
    Node* right;

    Node() {}
    Node(T key) : key(key), height(1), count(1), left(nullptr), right(nullptr) {}
    ~Node() {}
    Node(const Node& other): key(other.key), height(other.height), count(other.count),
                             left(other.left), right(other.right) {}

    Node(Node&& other): key(other.key), height(other.height), count(other.count),
                        left(other.left), right(other.right) {
        other.key = 0;
        other.height = 0;
        other.count = 0;
        other.left = nullptr;
        other.right = nullptr;
    }
    Node operator=(const Node& other) {
        if (this != &other) {
            key = other.key;
            height = other.height;
            count = other.count;
            left = other.left;
            right = other.right;
        }
        return *this;
    }
    Node operator=(Node&& other) {
        if (this != &other) {
            key = other.key;
            height = other.height;
            count = other.count;
            left = other.left;
            right = other.right;
            other.key = 0;
            other.height = 0;
            other.count = 0;
            other.left = nullptr;
            other.right = nullptr;
        }
        return *this;
    }
};

template <class T>
class AVLTree {
private:
    Node<T>* root;
    int height(Node<T>* node) { return node ? node->height : 0; }
    int count(Node<T>* node) { return node ? node->count : 0; }
    int bFactor(Node<T>* node) { return height(node->right) - height(node->left); }
    void fixHeight(Node<T>* node);
    Node<T>* rotateLeft(Node<T>* node);
    Node<T>* rotateRight(Node<T>* node);
    Node<T>* balance(Node<T>* node);
    Node<T>* insert(Node<T>* node, T key);
    Node<T>* remove(Node<T>* node, T key);
    Node<T>* findMax(Node<T>* node);
    Node<T>* removeMax(Node<T>* node);
    void clear(Node<T>* node) {
        if (!node) {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }
public:
    AVLTree() {root = nullptr; }
    ~AVLTree() { clear(root); }
    Node<T>* Add(T key);
    Node<T>* Delete(T key);
    T KStatistic(int k);
};

template <class T>
void AVLTree<T>::fixHeight(Node<T> *node) {
    int heightLeft = height(node->left);
    int heightRight = height(node->right);
    node->height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
    node->count = node->left ? node->left->count + 1 : 0;
    node->count += node->right ? node->right->count + 1 : 0;
}

template <class T>
Node<T>* AVLTree<T>::rotateLeft(Node<T> *node) {
    Node<T>* root = node->right;
    node->right = root->left;
    root->left = node;
    fixHeight(node);
    fixHeight(root);
    return root;
}

template <class T>
Node<T>* AVLTree<T>::rotateRight(Node<T> *node) {
    Node<T>* root = node->left;
    node->left = root->right;
    root->right = node;
    fixHeight(node);
    fixHeight(root);
    return root;
}

template <class T>
Node<T>* AVLTree<T>::balance(Node<T> *node) {
    fixHeight(node);
    int nodeBFactor = bFactor(node);
    if (nodeBFactor == 2) {
        if (bFactor(node->right) < 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    if (nodeBFactor == -2) {
        if (bFactor(node->left) > 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    return node;
}

template <class T>
Node<T>* AVLTree<T>::insert(Node<T>* node, T key) {
    if (!node) {
        return new Node<T>(key);
    }
    if (key < node->key) {
        node->left = insert(node->left, key);
    } else {
        node->right = insert(node->right, key);
    }
    return balance(node);
}

template <class T>
Node<T>* AVLTree<T>::Add(T key) {
    root = insert(root, key);
}

template <class T>
Node<T>* AVLTree<T>::findMax(Node<T>* node) {
    return node->right ? findMax(node->right) : node;
}

template <class T>
Node<T>* AVLTree<T>::removeMax(Node<T> *node) {
    if (!node->right) {
        return node->left;
    }
    node->right = removeMax(node->right);
    return balance(node);
}

template <class T>
Node<T>* AVLTree<T>::remove(Node<T> *node, T key) {
    if (!node) {
        return nullptr;
    }
    if (key < node->key) {
        node->left = remove(node->left, key);
    } else if (key > node->key) {
        node->right = remove(node->right, key);
    } else {
        Node<T>* left = node->left;
        Node<T>* right = node->right;
        delete node;
        if (!left) {
            return right;
        }
        Node<T>* max = findMax(left);
        max->left = removeMax(left);
        max->right = right;
        return balance(max);
    }
    return balance(node);
}

template <class T>
Node<T>* AVLTree<T>::Delete(T key) {
    root = remove(root, key);
}

template <class T>
T AVLTree<T>::KStatistic(int k) {
    assert(root);
    Node<T>* node = root;
    int kNode = k - 1;
    while (kNode != k) {
        if (k < kNode) {
            node = node->left;
            if (!node) {
                return node->key;
            }
            kNode = count(node->left);
        } else {
            node = node->right;
            if (!node) {
                return node->key;
            }
            kNode = count(node->left) - 1;
            //k = k -
        }
    }

    return node->key;
}

int main() {
    AVLTree<int> avlTree;
    int count = 0;
    std::cin >> count;
    int key = 0;
    int k = 0;
    for (int i = 0; i < count; i++) {
        std::cin >> key >> k;
        if (key > 0) {
            avlTree.Add(key);
        } else {
            avlTree.Delete(-key);
        }
        std::cout << avlTree.KStatistic(k) << ' ';
    }
    return 0;
}