#include <iostream>
#include <cassert>

template <class T>
bool compare(const T value1, const T value2) {}

template<>
bool compare<int>(const int value1, const int value2) {
    return (value1 <= value2);
}

template <class T>
class Comparator {
public:
    bool operator()(const T value1, const T value2) const { return compare(value1, value2); }
};

template <class T, class TComparator = Comparator<T>>
class BinaryTree {
private:
    struct Node {
        T value;
        Node* left;
        Node* right;
        Node* parent;
        bool visited;

        Node(): left(nullptr), right(nullptr), parent(nullptr), visited(false) {}
        Node(const T& value, Node* parent = nullptr):
                value(value), left(nullptr), right(nullptr), parent(parent), visited(false) {}
        ~Node() {}
        Node(const Node& other) = delete;
        Node(Node&& other) = delete;
        Node operator=(const Node& other) = delete;
        Node operator=(Node&& other) = delete;
    };

    Node* root = nullptr;
    TComparator compare;

public:
    BinaryTree() {}
    BinaryTree(const BinaryTree& other) = delete;
    BinaryTree(BinaryTree&& other) = delete;
    ~BinaryTree() {}
    BinaryTree operator=(const BinaryTree& other) = delete;
    BinaryTree operator=(BinaryTree&& other) = delete;

    void Add(int insertValue);
    void InOrder();
    void PrintNode(const Node* node);
};

template <class T, class TComparator>
void BinaryTree<T, TComparator>::Add(int insertValue) {
    if (!root) {
        root = new Node(insertValue);
        return;
    }
    Node* parent = root;
    while(parent) {
        if (compare(parent->value, insertValue)) {
            if (parent->right) {
                parent = parent->right;
            } else {
                parent->right = new Node(insertValue, parent);
                break;
            }
        } else {
            if (parent->left) {
                parent = parent->left;
            } else {
                parent->left = new Node(insertValue, parent);
                break;
            }
        }
    }
}

template <class T, class TComparator>
void BinaryTree<T, TComparator>::InOrder() {
    assert(root);
    Node* parent = root;
    while (parent) {
        while (parent->left && !parent->visited) {
            parent = parent->left;
        }

        parent->visited = true;
        PrintNode(parent);

        while(parent && (!parent->right || parent->right->visited)) {
            if (!parent->right && !parent->visited) {
                parent->visited = true;
                PrintNode(parent);
            }
            parent = parent->parent;
        }
        if (parent && parent->right) {
            if (!parent->visited) {
                parent->visited = true;
                PrintNode(parent);
            }
            parent = parent->right;
        }
    }
}

template <class T, class TComparator>
void BinaryTree<T, TComparator>::PrintNode(const Node* node) {
    std::cout << node->value << ' ';
}

int main() {
    BinaryTree<int> binaryTree;
    int size = 0;
    std::cin >> size;
    int value = 0;
    for (int i = 0; i < size; i++) {
        std::cin >> value;
        binaryTree.Add(value);
    }
    binaryTree.InOrder();
    return 0;
}