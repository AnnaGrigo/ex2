//
// Created by annag on 21/12/2022.
//

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
int main(){
    RankTree<int,int> tree;
    std::vector<int> vector;

    for (int i=1; i<10000; i++) vector.push_back(i);


    for (int k = 0; k <= 1000; ++k) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); it++){
            assert(is_tree_valid(tree.root));
            tree.insert(*it,*it);

        }
        //shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
            //print2D(tree.root);
            tree.remove(*it);

        }
        //std::cout<<std::endl;
        tree.deleteTree(tree.root);
        tree.root= nullptr;
        //std::cout<<std::endl;
        //std::cout << '\n';
    }

    return 0;
}