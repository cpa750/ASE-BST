#include <iostream>
#include "BST.h"

int main()
{
    BST* bst = new BST();
    bst->insert(0, "hello, ");
    bst->insert(1, "world");

    std::cout << *bst->lookup(0) << *bst->lookup(1) << std::endl;

    return 0;
}
