#include "BST.h"

struct BST::Node
{
    Node(KeyType key, ItemType item)
    {
        this->key = key;
        this->item = item;
        this->leftChild = leaf();
        this->rightChild = leaf();
    }

    Node(KeyType key, ItemType item, Node* leftChild, Node* rightChild)
    {
        this->key = key;
        this->item = item;
        this->leftChild = leftChild;
        this->rightChild = rightChild;
    }

    KeyType key;
    ItemType item;
    Node* leftChild;
    Node* rightChild;
};

BST::Node* BST::leaf()
{
    return nullptr;
}

bool BST::isLeaf(Node* node)
{
    return node == nullptr;
}

BST::ItemType* BST::lookup(KeyType key)
{
    return this->lookupRec(key, this->root);
}

BST::ItemType* BST::lookupRec(KeyType key, BST::Node* node)
{
    if (isLeaf(node)) return nullptr;

    if (key == node->key) return &node->item;
    else if (key > node->key) return lookupRec(key, node->rightChild);
    else return this->lookupRec(key, node->leftChild);
}

void BST::insert(KeyType key, ItemType item)
{
    this->insertRec(key, item, this->root);
}

void BST::insertRec(KeyType key, ItemType item, Node*& node)
{
    if (isLeaf(node) || key == node->key) node = new Node(key, item);
    else if (key > node->key) this->insertRec(key, item, node->rightChild);
    else this->insertRec(key, item, node->leftChild);
}
