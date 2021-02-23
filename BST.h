#ifndef BST_BST_H
#define BST_BST_H


#include <string>

class BST
{
public:
    using KeyType = int;
    using ItemType = std::string;

    struct Node;

    BST() = default;
    ~BST();
    ItemType* lookup(KeyType);
    void insert(KeyType, ItemType);
    void remove(KeyType);
    void displayEntries();
    void displayTree();

private:
    Node* root = leaf();

    static Node* leaf();
    static bool isLeaf(Node*);
    void insertRec(KeyType, ItemType, Node*&);
    ItemType* lookupRec(KeyType, Node*);
    void displayEntriesRec(Node*);
    void displayTreeRec(Node*, int);
    Node* removeRec(Node*, KeyType);
    void deepDelete(Node*);
    Node* minNode(Node*);
};


#endif //BST_BST_H
