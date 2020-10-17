#ifndef BST_BST_H
#define BST_BST_H


#include <string>

class ItemType;

class BST
{
public:
    using KeyType = int;
    using ItemType = std::string;

    struct Node;

    BST() = default;
    ItemType* lookup(KeyType);
    void insert(KeyType, ItemType);
    void remove(KeyType);

private:
    Node* root = leaf();

    static Node* leaf();
    static bool isLeaf(Node*);

    void insertRec(KeyType, ItemType, Node*&);
    ItemType* lookupRec(KeyType, Node*);
};


#endif //BST_BST_H
