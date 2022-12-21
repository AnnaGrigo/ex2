#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>

// Hashtable with chain hashing based on a linked list

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
        this->value(other.value);
        this->next(other.next);
        this->id(other.id);
    }

    ~Node() = default;
};

// ----Linked list----
template<class Value>
class List {
public:
    Node<Value> *head;

    List()
            : head(nullptr) {
    }

    // Adding an Value to the list
    void addToList(Value value, int id);

    // Deleting an Value from the list
    bool deleteValue(int id);

    // Finding and returning an Value by the id
    Node<Value> *find(int id);
};

template<class Value>
void List<Value>::addToList(Value value, int id) {
    auto *a = new Node<Value>(value, this->head, id);
    this->head = a;
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
    if (this == nullptr) {
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

// ----Hash Table----
template<class Value>
class HashTable {

private:
    int size;
    int Values_amount;
    int load_factor;

public:
    List<Value> *array;

    HashTable(int size, int sizing_up_down);

    ~HashTable();

    Value findAndReturn(int key);

    int getSize() const;

    int getCapacity() const;

    bool isEmpty() const;

    Node<Value> *operator[](int place);

    const Node<Value> *operator[](int place) const;

    void clear();

    void resize(int to_change);

    bool insert_Value(int id, Value value);

    bool remove_Value(int id);
};

// Constructor
template<class Value>
HashTable<Value>::HashTable(int size, int sizing_up_down)
        : size(size), Values_amount(0), load_factor(sizing_up_down) {
    array = new List<Value> *[size]();
}

// Dtor
template<class Value>
HashTable<Value>::~HashTable() {
    this->clear();
}

template<class Value>
Value HashTable<Value>::findAndReturn(int key) {
    if (array[key % size]->find(key) == nullptr) {
        return nullptr;
    } else {
        return array[key % size]->find(key)->value;
    }
}

template<class Value>
int HashTable<Value>::getSize() const {
    return size;
}

template<class Value>
int HashTable<Value>::getCapacity() const {
    return Values_amount;
}

template<class Value>
bool HashTable<Value>::isEmpty() const {
    return size == 0;
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
    Node<Value> *current;
    Node<Value> *next;
    for (int i = 0; i < size; i++) {
        if (array[i] != nullptr) {
            current = array[i]->head;
            while (current != nullptr) {
                next = current->next;
                if (current->value != nullptr) {
                    current->value = nullptr;
                }
                current = next;
            }
            delete array[i];
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
bool HashTable<Value>::insert_Value(int id, Value value) {
    if ((this->load_factor * this->size) < this->Values_amount) {
        Node<Value> *current;
        List<Value> *bigger_array = new List<Value>[2 * size]();
        for (int i = 0; i < this->size; i++) {
            if (array[i] != nullptr) {
                current = array[i]->head;
                while (current != nullptr) {
                    if (bigger_array[current->id % (2 * this->size)] == nullptr) {
                        bigger_array[current->id % (2 * this->size)] = new List<Value>();
                    }
                    bigger_array[current->id % (2 * this->size)]->addToList(new Value(current->value), current->id);
                    current = current->next;
                }
            }
        }
        this->clear();
        array = bigger_array;
        this->resize(1);
    }
    if (this->findAndReturn(id) != nullptr) {
        return false;
    }
    if (array[id % this->size] == nullptr) {
        array[id % this->size] = new List<Value>();
    }
    array[id % this->size]->addToList(value, id);
    this->Values_amount++;
    return true;
}

template<class Value>
bool HashTable<Value>::remove_Value(int id) {
    if ((this->load_factor * this->Values_amount) < this->size) {
        Node<Value> *current;
        List<Value> *smaller_array = new List<Value>[this->size / 2]();
        for (int i = 0; i < this->size; i++) {
            if (array[i] != nullptr) {
                current = array[i]->head;
                while (current != nullptr) {
                    if (smaller_array[current->id % (this->size / 2)] == nullptr) {
                        smaller_array[current->id % (this->size / 2)] = new List<Value>();
                    }
                    smaller_array[current->id % (this->size / 2)]->addToList(new Value(current->value), current->id);
                    current = current->next;
                }
            }
        }
        this->clear();
        array = smaller_array;
        this->resize(2);
    }
    array[id % this->size]->deleteValue(id);
    this->Values_amount--;
    return true;
}


#endif /* HASH_TABLE_H */