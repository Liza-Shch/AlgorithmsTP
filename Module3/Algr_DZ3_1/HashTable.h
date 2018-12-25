//
// Created by liza_shch on 14.12.18.
//

#ifndef ALGR_DZ3_1_HASHTABLE_H
#define ALGR_DZ3_1_HASHTABLE_H

#include "Hasher.h"
#include <iostream>
#include <cassert>
#include <vector>

template <class T, class THash=Hasher<T>>
class HashTable {
public:
    HashTable();
    HashTable(const HashTable& other) = delete;
    HashTable(HashTable&& other) { *this = std::move(other); }
    ~HashTable() { clear(); }

    HashTable& operator=(const HashTable& other) = delete;
    HashTable& operator=(HashTable&& other);

    bool Add(const T& item);
    bool Has(const T& item) const;
    bool Remove(const T& item);

private:
    struct Node {
        T Item;
        bool deleted;

        Node() {};
        Node(const T& item, bool deleted = false) : Item(item), deleted(deleted) {}
        Node(const Node& other) {
            Item = other.Item;
            deleted = other.deleted;
        }
        Node(Node&& other) = delete;
        ~Node() {}

        Node& operator=(const Node& other) = delete;
        Node& operator=(Node&& other) {
            *this = std::move(other);
            return *this;
        }
    };

    std::vector<Node*> table = nullptr;
    THash hash;
    const float fillingIndex = 0.75;
    int currentSize = 0;
    int bufferSize = 8;

    void rehashing();
    void clear();
};

template <class T, class THash>
HashTable<T, THash>::HashTable(): table(bufferSize) {
    for (int i = 0; i < bufferSize; i++) {
        table.push_back(nullptr);
    }
}

template <class T, class THash>
HashTable<T, THash>& HashTable<T, THash>::operator=(HashTable&& other) {
    table = other.table;
    other.table = nullptr;
}

template <class T, class THash>
void HashTable<T, THash>::rehashing() {
    int newBufferSize = bufferSize * 2;
    std::vector<Node*> newTable(newBufferSize);
    for (int i = 0; i < bufferSize; i++) {
        if (table[i] && !table[i]->deleted) {
            for (int newTableIterator = 0; newTableIterator < newBufferSize; newTableIterator++) {
                int key = hash(table[i]->Item, newBufferSize, newTableIterator);
                if (!newTable[key] || newTable[key]->deleted) {
                    newTable[key] = table[i];
                    break;
                }
            }
        }
    }

    table = newTable;
    bufferSize = newBufferSize;
}

template <class T, class THash>
void HashTable<T, THash>::clear() {
    for (auto& item : table) {
        delete item;
    }
}

template <class T, class THash>
bool HashTable<T, THash>::Add(const T& item) {
    if (Has(item)) {
        return false;
    }

    if (currentSize / bufferSize > fillingIndex) {
        rehashing();
    }

    for (int i = 0; i < bufferSize; i++) {
        int key = hash(item, bufferSize, i);
        if (!table[key] || table[key]->deleted) {
            table[key] = new Node(item);
            currentSize++;
            return true;
        }
    }

    return false;
}

template <class T, class THash>
bool HashTable<T, THash>::Remove(const T& item) {
    for (int i = 0; i < bufferSize; i++) {
        int key = hash(item, bufferSize, i);
        if (!table[key]) {
            return false;
        }
        if (!table[key]->deleted && table[key]->Item == item) {
            table[key]->deleted = true;
            currentSize--;
            return true;
        }
    }

    return false;
}

template <class T, class THash>
bool HashTable<T, THash>::Has(const T& item) const {
    for (int i = 0; i < bufferSize; i++) {
        int key = hash(item, bufferSize, i);
        if (!table[key] || table[key]->Item == item && table[key]->deleted) {
            return false;
        }
        if (table[key]->Item == item) {
            return true;
        }
    }

    return false;
}

#endif //ALGR_DZ3_1_HASHTABLE_H
