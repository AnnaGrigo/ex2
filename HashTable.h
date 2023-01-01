#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>

// Hashtable with chain hashing based on a linked list with load factor of 2

// The node on the list
// Contains an array and id

//----Node----
template<class Value>
class Node {
public:
    Value value;
    Node *next;
    int id;

    Node(Value value, int id)
            : value(value), next(nullptr), id(id) {
    }

    Node(Value value, Node<Value> *next, int id)
            : value(value), next(next), id(id) {
    }

    Node(Node<Value> &other) {
        this->value = other.value;
        this->next = other.next;
        this->id = other.id;
    }

    ~Node() = default;
};

// ----Linked list----
template<class Value>
class List {
public:
    Node<Value> *head;

    List(): head(nullptr) {}

    // Adding a Value to the list
    void addToList(Value value, int id);

    // Deleting a Value from the list
    bool deleteValue(int id);

    // Finding and returning a Value by the id
    Node<Value> *find(int id);

    //delete all the list
    void deleteList();
};

template<class Value>
void List<Value>::addToList(Value value, int id) {
    auto *new_node = new Node<Value>(value, this->head, id);
    this->head = new_node;
}

template<class Value>
bool List<Value>::deleteValue(int id) {
    if (this != nullptr) {
        Node<Value> *node = this->head;
        Node<Value> *prev = nullptr;
        while (node != nullptr) {
            if (id == node->id) {
                if (prev == nullptr) {
                    this->head = node->next;
                } else {
                    prev->next = node->next;
                }
                delete node;
                return true;
            }
            prev = node;
            node = node->next;
        }
        return false;
    }
    return true;
}

template<class Value>
Node<Value> *List<Value>::find(int id) {
    if (this->head == nullptr) {
        return nullptr;
    }
    Node<Value> *current = this->head;
    while (current != nullptr) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template<class Value>
void List<Value>::deleteList() {
    Node<Value> *current = this->head;
    Node<Value> *next;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    this->head = nullptr;
}

// ----Hash Table----
template<class Value>
class HashTable {

public:
    int size;
    int Values_amount;
    int load_factor;
    List<Value> *array;

    explicit HashTable();

    ~HashTable();

    Node<Value> *find_HT(int key);

    Node<Value> *operator[](int place);

    const Node<Value> *operator[](int place) const;

    void clear();

    void resize(int to_change);

    bool insert_HT(int id, Value value);

    bool remove_HT(int id);
};


// Constructor
template<class Value>
HashTable<Value>::HashTable()
        : size(10), Values_amount(0), load_factor(2) {
    array = new List<Value>[size]();
}

// Dtor
template<class Value>
HashTable<Value>::~HashTable() {
    this->clear();
}

template<class Value>
Node<Value> *HashTable<Value>::find_HT(int key) {
    if (array[key % size].find(key) == nullptr) {
        return nullptr;
    } else {
        return array[key % size].find(key);
    }
}

template<class Value>
Node<Value> *HashTable<Value>::operator[](int place) {
    if (place >= size || place < 0) {
        return nullptr;
    }
    return array[place];
}

template<class Value>
const Node<Value> *HashTable<Value>::operator[](int place) const {
    if (place >= size || place < 0) {
        return nullptr;
    }
    return array[place];
}

template<class Value>
void HashTable<Value>::clear() {
    for (int i = 0; i < size; i++) {
        if (array[i].head != nullptr) {
            array[i].deleteList();
        }
    }
    delete[] array;
}

template<class Value>
void HashTable<Value>::resize(int to_change) {
    if (to_change == 1) {
        size *= 2;
    } else {
        size /= 2;
    }
}

template<class Value>
bool HashTable<Value>::insert_HT(int id, Value value) {
    if (this->find_HT(id) != nullptr) {
        return false;
    }
    if ((this->load_factor * this->size) < this->Values_amount) {
        Node<Value> *current;
        auto bigger_array = new List<Value>[2 * size]();
        for (int i = 0; i < this->size; i++) {
            if (array[i].head != nullptr) {
                current = array[i].head;
                while (current != nullptr) {
                    bigger_array[current->id % (2 * this->size)].addToList(current->value, current->id);
                    current = current->next;
                }
            }
        }
        this->clear();
        array = bigger_array;
        this->resize(1);
    }
    array[id % this->size].addToList(value, id);
    this->Values_amount++;
    return true;
}


template<class Value>
bool HashTable<Value>::remove_HT(int id) {
    if (this->find_HT(id) == nullptr) {
        return false;
    }
    if ((this->load_factor * this->Values_amount) < this->size) {
        Node<Value> *current;
        auto smaller_array = new List<Value>[this->size / 2]();
        for (int i = 0; i < this->size; i++) {
            if (array[i].head != nullptr) {
                current = array[i].head;
                while (current != nullptr) {
                    smaller_array[current->id % (this->size / 2)].addToList(current->value, current->id);
                    current = current->next;
                }
            }
        }
        this->clear();
        array = smaller_array;
        this->resize(2);
    }
    array[id % this->size].deleteValue(id);
    this->Values_amount--;
    return true;
}


#endif /* HASH_TABLE_H */