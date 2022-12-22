#include <iostream>
#include "HashTable.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {

    HashTable<int> table(3);
    table.insert_HT(1, 1);
    table.insert_HT(2, 2);
    table.insert_HT(3, 3);
    table.insert_HT(4, 4);
    table.insert_HT(5, 5);
    table.insert_HT(6, 6);
    table.insert_HT(7, 7);
    table.insert_HT(8, 8);
    table.insert_HT(9, 9);
    table.insert_HT(10, 10);
    table.remove_HT(1);
    table.remove_HT(2);
    table.remove_HT(3);
    table.remove_HT(4);
    table.remove_HT(5);
    table.remove_HT(6);
    table.remove_HT(7);
    table.remove_HT(8);
    table.remove_HT(9);
    table.remove_HT(10);




    return 0;
}
