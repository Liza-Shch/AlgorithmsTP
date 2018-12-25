#include <iostream>
#include <queue>
#include <stack>
#include <cassert>

template <class T>
class BinaryNode {
public:
    T key;
    BinaryNode* left;
    BinaryNode* right;

    BinaryNode() {}
    BinaryNode(const T& key, BinaryNode* left = nullptr, BinaryNode* right = nullptr):
            key(key), left(left), right(right) {};
    ~BinaryNode() = default;
    BinaryNode(const BinaryNode& other) = delete;
    BinaryNode(BinaryNode&& other) = delete;
    BinaryNode operator=(const BinaryNode& other) = delete;
    BinaryNode operator=(BinaryNode&& other) = delete;
};

template <class T>
class TreapNode {
public:
    T key;
    int priority;
    TreapNode* left;
    TreapNode* right;

    TreapNode() {}
    TreapNode(const T& key, int priority, TreapNode* left, TreapNode* right):
            key(key), priority(priority), left(left), right(right) {};
    ~TreapNode() = default;
    TreapNode(const TreapNode& other) = delete;
    TreapNode(TreapNode&& other) = delete;
    TreapNode operator=(const TreapNode& other) = delete;
    TreapNode operator=(TreapNode&& other) = delete;
};

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

template <class TNode>
void PostOrder(TNode*& root, void action(TNode*&)) {
    assert(root);
    std::stack<TNode*> stack;
    stack.push(root);
    TNode* current = root->left;
    TNode* right_visited = nullptr;
    while (!stack.empty()) {
        if (current) {
            stack.push(current);
            current = current->left;
        } else {
            current = stack.top();
            if (current->right && current->right != right_visited) {
                current = current->right;
            } else {
                action(current);
                right_visited = current;
                stack.pop();
                current = nullptr;
            }
        }
    }
}

template <class TNode>
int MaxLayerNodeCount(const TNode* root) {
    assert(root);
    std::queue<const TNode*> queue;
    const TNode* current = root;
    int maxLayerNodeCount = 1;
    int currentLayerNodeCount = 0;
    queue.push(current);
    queue.push(nullptr);
    while (!queue.empty()) {
        current = queue.front();
        if (current) {
            if (current->left) {
                queue.push(current->left);
                currentLayerNodeCount++;
            }
            if (current->right) {
                queue.push(current->right);
                currentLayerNodeCount++;
            }
            queue.pop();
        } else {
            if (maxLayerNodeCount < currentLayerNodeCount) {
                maxLayerNodeCount = currentLayerNodeCount;
            }
            currentLayerNodeCount = 0;
            queue.pop();
            if (queue.empty()) {
                break;
            }
            queue.push(nullptr);
        }
    }

    return maxLayerNodeCount;
}

template <class T, class TComparator = Comparator<T>>
class BinaryTree {
private:
    BinaryNode<T>* root;
    TComparator compare;
    static void clear(BinaryNode<T>*& node) { delete node; }

public:
    BinaryTree(): root(nullptr) {}
    BinaryTree(const BinaryTree& other) = delete;
    BinaryTree(BinaryTree&& other) = delete;
    ~BinaryTree() { PostOrder<BinaryNode<T>>(root, clear); }
    BinaryTree operator=(const BinaryTree& other) = delete;
    BinaryTree operator=(BinaryTree&& other) = delete;

    void Add(T insertValue);
    int MaxLayerWidth() { return MaxLayerNodeCount<BinaryNode<T>>(root); }
};

template <class T, class TComparator>
void BinaryTree<T, TComparator>::Add(T insertValue) {
    if (!root) {
        root = new BinaryNode<T>(insertValue);
        return;
    }
    BinaryNode<T>* current = root;
    BinaryNode<T>* parent = nullptr;
    while(current) {
        parent = current;
        current = compare(insertValue, current->key) ? current->left : current->right;
    }

    (compare(insertValue, parent->key) ? parent->left : parent->right) = new BinaryNode<T>(insertValue);
}

template <class T, class TComparator = Comparator<T>>
class Treap {
private:
    TreapNode<T> *root;
    TComparator compare;
    static void clear(TreapNode<T>*& node) { delete node; }
    void split(TreapNode<T>* current, int key, TreapNode<T>*& left, TreapNode<T>*& right);
    TreapNode<T>* merge(TreapNode<T>* left, TreapNode<T>* right);

public:
    Treap(): root(nullptr) {}
    Treap(const Treap& other) = delete;
    Treap(Treap&& other) = delete;
    ~Treap(){ PostOrder<TreapNode<T>>(root, clear); }
    Treap operator=(const Treap& other) = delete;
    Treap operator=(Treap&& other) = delete;

    void Add(const T& key, int priority);
    int MaxLayerWidth() { return MaxLayerNodeCount<TreapNode<T>>(root); }
};

template <class T, class TComparator>
void Treap<T ,TComparator>::split(TreapNode<T>* current, int key, TreapNode<T>*& left, TreapNode<T>*& right) {
    if (current == nullptr) {
        left = nullptr;
        right = nullptr;
    } else if (current->key < key) {
        split(current->right, key, current->right, right);
        left = current;
    } else {
        split(current->left, key, left, current->left);
        right = current;
    }
}

template <class T, class TComparator>
TreapNode<T>* Treap<T, TComparator>::merge(TreapNode<T> *left, TreapNode<T> *right) {
    if (left == 0 || right == 0) {
        return left == 0 ? right: left;
    }
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

template <class T, class TComparator>
void Treap<T, TComparator>::Add(const T &key, int priority) {
    TreapNode<T>* current = root;
    TreapNode<T>* parent = nullptr;
    while (current && current->priority >= priority) {
        parent = current;
        current = compare(key, current->key) ? current->left: current->right;
    }

    TreapNode<T>* left = nullptr;
    TreapNode<T>* right = nullptr;
    split(current, key, left, right);
    current = new TreapNode<T>(key, priority, left, right);

    if (!parent) {
        root = current;
        return;
    }

    (compare(parent->key, key) ? parent->right : parent->left) = current;
}

int main() {
    BinaryTree<int> bst;
    Treap<int> treap;
    int count = 0;
    std::cin >> count;
    int key = 0;
    int priority = 0;
    for (int i = 0; i < count; i++) {
        std::cin >> key >> priority;
        bst.Add(key);
        treap.Add(key, priority);
    }
    std::cout << treap.MaxLayerWidth()- bst.MaxLayerWidth();
    return 0;
}
