//
// Created by annag on 21/12/2022.
//

#ifndef EX2_UNIONFIND_H
#define EX2_UNIONFIND_H

#include "RankTree.h"
#include "HashTable.h"
#include "wet2util.h"

template<class Group,class Item>
class UFNode {
public:
    int id;
    int size;
    permutation_t rSpirit;
    permutation_t spirit;
    Item item;
    Group group;
    UFNode *parent;

    UFNode(int id, Item item) : id(id),size(1),rSpirit(0),item(item),group(nullptr),parent(nullptr) {}
};


template<class Group,class Item>
class UnionFind {
public:
    Group* Find(int id);
    StatusType Union(Group group1, Group group2);
    UnionFind() = default;
    ~UnionFind() = default;
private:
    HashTable<Item> *items;
    RankTree<int,Group> *groups;
};

template<class Group, class Item>
Group *UnionFind<Group, Item>::Find(int id) {
    Item item = items->findAndReturn(id);
    if(item == nullptr){
        return nullptr;
    }
    UFNode<Group,Item> *node = item->node;
    while(node->parent != nullptr){
        node = node->parent;
    }
    return node->group;
}


//group1 buys group2 -> group1 will be "on top" of group2 (because the players have been in the group longer)
template<class Group, class Item>
StatusType UnionFind<Group, Item>::Union(Group group1, Group group2) {
    UFNode<Group, Item> *node1 = group1->node;
    UFNode<Group, Item> *node2 = group2->node;
    if(node2->size >= node1->size){
        node1->parent = node2;
        node2->size += node1->size;
        node1->group = node2->group;
    }
    else{
        node2->parent = node1;
        node1->size += node2->size;
        node2->group = node1->group;
    }





    return StatusType::ALLOCATION_ERROR;
}



#endif //EX2_UNIONFIND_H
