/*
 * Replace all the red errors with your own Tree code.
 */

#include <iostream>
#include "RankTree.h"
#include <vector>
#include <ostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <memory>
#include <assert.h>


void printTree(RankNode<int,int> * root) {
    std::cout.flush();
    if(root== nullptr)
        return;

    printTree(root->left_son);
    std::cout<<root->key;
    // BalanceFactor func calculates the BF of a given node, implementation in RankTree.h
    std::cout<<" BF: "<<BalanceFactor(root)<<" Height: "<<root->height-1<<std::endl;
    printTree(root->right_son);
}
void print2DUtil(RankNode<int,int> *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right_son child first
    print2DUtil(root->right_son, space);

    // Print current node after space
    // count
    std::cout<<std::endl;
    for (int i = 10; i < space; i++)
        std::cout<<" ";
    std::cout<<root->value<<"\n";

    // Process left_son child
    print2DUtil(root->left_son, space);
}

// Wrapper over print2DUtil()
void print2D(RankNode<int,int> *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

}
int main1(){
    RankTree<int,int> tree;
    std::vector<int> vector;
    //determines the size of the tree
    for (int i=1; i < 11; i++) vector.push_back(i);

    //randomizes the vector, and k is the number of trees to randomize
    for (int k = 1; k < 11; ++k) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); it++){
            tree.insert(*it,*it);
            assert(is_tree_valid(tree.root));
            //print2D(tree.root);
        }
        //shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
            tree.remove(*it);
            assert(is_tree_valid(tree.root));
            //print2D(tree.root);

        }
        //std::cout<<std::endl;
        tree.deleteTree(tree.root);
        tree.root= nullptr;
        //std::cout<<std::endl;
        //std::cout << '\n';
    }

    return 0;
}

/*
 * is_tree_valid - checks if the tree is valid, meaning that the tree is balanced and the rank is correct
 * @param root - the root of the tree
 * @return true if the tree is valid, false otherwise
 * should use to make sure your tree is valid after every insertion and deletion
 * if your Node class doesn't use a parent pointer, remove lines 126-140
 *
 * template<class Key, class Value>
bool is_tree_valid(RankNode<Key, Value> *root) {
    if (!root) {
        return true;
    }
    if (root->height != 1 + std::max(getHeight(root->left_son), getHeight(root->right_son))) {
        return false;
    }
    if (!root->left_son && !root->right_son && root->height != 0) {
        return false;
    }
    if (root->left_son && root->left_son->key >= root->key) {
        return false;
    }
    if (root->right_son && root->right_son->key <= root->key) {
        return false;
    }
    if (root->weight != 1 + getWeight(root->left_son) + getWeight(root->right_son)) {
        return false;
    }
    if (std::abs(BalanceFactor(root)) > 1) {
        return false;
    }
    if (root->parent) {
        if (root->parent->left_son != root && root->parent->right_son != root) {
            return false;
        }
    }
    if (root->left_son) {
        if (root->left_son->parent != root) {
            return false;
        }
    }
    if (root->right_son) {
        if (root->right_son->parent != root) {
            return false;
        }
    }
    return is_tree_valid(root->left_son) && is_tree_valid(root->right_son);
}

template<class Key, class Value>
int getHeight(RankNode<Key, Value> *root) {
    if (!root) {
        return -1;
    }
    return root->height;
}


template<class Key, class Value>
int BalanceFactor(RankNode<Key, Value> *node) {
    if (node == nullptr) {
        return 0;
    }
    int Rheight = -1;
    int Lheight = -1;
    if (node->right_son != nullptr) {
        Rheight = node->right_son->height;
    }
    if (node->left_son != nullptr) {
        Lheight = node->left_son->height;
    }
    return Lheight - Rheight;
}

template<class Key, class Value>
int getWeight(RankNode<Key, Value> *root) {
    if (!root) {
        return 0;
    }
    return root->weight;
}

 */