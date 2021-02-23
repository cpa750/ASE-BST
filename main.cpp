#include <iostream>
#include "bst.h"

using Dict = BST;

int main()
{
    Dict dict;

    dict.insert(22,"Jane");
    dict.insert(22,"Mary");
    dict.insert(0,"Harold");
    dict.insert(9,"Edward");
    dict.insert(37,"Victoria");
    dict.insert(4,"Matilda");
    dict.insert(26,"Oliver");
    dict.insert(42,"Elizabeth");
    dict.insert(19,"Henry");
    dict.insert(4,"Stephen");
    dict.insert(24,"James");
    dict.insert(-1,"Edward");
    dict.insert(31,"Anne");
    dict.insert(23,"Elizabeth");
    dict.insert(1,"William");
    dict.insert(26,"Charles");

    dict.displayEntries();

    std::cout << std::endl;

    dict.displayTree();
    dict.remove(0);
}