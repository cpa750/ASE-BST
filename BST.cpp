#include <iostream>
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

BST::BST(const BST& original)
{
    this->root = this->deepCopy(original.root);
}

BST::BST(BST&& original) noexcept
{
    if (this != &original) {
        this->deepDelete(this->root);
        this->root = original.root;
        original.root = BST::leaf();
    }
}

BST::~BST()
{
    this->deepDelete(this->root);
}

BST& BST::operator=(BST&& original) noexcept
{
    if (this != &original) {
        this->deepDelete(this->root);
        this->root = original.root;
        original.root = BST::leaf();
    }
}

BST& BST::operator=(const BST& original)
{
    if (this != &original) {
        this->deepDelete(this->root);
        this->root = this->deepCopy(original.root);
    }
}

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
    if (isLeaf(node)) node = new Node(key, item);
    else if (key == node->key) {
        node->key = key;
        node->item = item;
    }
    else if (key > node->key) this->insertRec(key, item, node->rightChild);
    else this->insertRec(key, item, node->leftChild);
}

void BST::displayEntries()
{
    this->displayEntriesRec(this->root);
}

void BST::displayEntriesRec(Node* pNode)
{
    if (this->isLeaf(pNode)) return;

    if (!this->isLeaf(pNode->leftChild))
        this->displayEntriesRec(pNode->leftChild);
    else std::cout << "*" << std::endl;

    std::cout << pNode->key << ": " << pNode->item << std::endl;

    if (!this->isLeaf(pNode->rightChild))
        this->displayEntriesRec(pNode->rightChild);
    else std::cout << "*" << std::endl;
}

void BST::displayTree()
{
    this->displayTreeRec(this->root, 0);
}

void BST::displayTreeRec(Node* pNode, int indentLevel)
{
    if (this->isLeaf(pNode)) return;
    std::cout << std::string(indentLevel, '\t');
    std::cout << pNode->key << ": " << pNode->item << std::endl;

    if (!this->isLeaf(pNode->leftChild))
        this->displayTreeRec(pNode->leftChild, indentLevel + 1);
    else {
        std::cout << std::string(indentLevel + 1, '\t');
        std::cout << "*" << std::endl;
    }

    if (!this->isLeaf(pNode->rightChild))
        this->displayTreeRec(pNode->rightChild, indentLevel + 1);
    else {
        std::cout << std::string(indentLevel + 1, '\t');
        std::cout << "*" << std::endl;
    }

}

void BST::remove(KeyType key)
{
    this->removeRec(this->root, key);
}

BST::Node* BST::removeRec(Node* pNode, KeyType key)
{
    if (BST::isLeaf(pNode)) return pNode;
    if (key < pNode->key) {
        pNode->leftChild = this->removeRec(pNode->leftChild, key);
    } else if (key > pNode->key) {
        pNode->rightChild = this->removeRec(pNode->rightChild, key);
    } else {
        if (this->isLeaf(pNode->leftChild) && this->isLeaf(pNode->rightChild)) {
            delete pNode;
            if (pNode == this->root) this->root = this->leaf();
            pNode = nullptr;
        } else if (this->isLeaf(pNode->leftChild)) {
            BST::Node* tmp = pNode->rightChild;
            if (pNode == this->root) this->root = tmp;
            delete pNode;
            return tmp;
        } else if (this->isLeaf(pNode->rightChild)) {
            BST::Node* tmp = pNode->leftChild;
            if (pNode == this->root) this->root = tmp;
            delete pNode;
            return tmp;
        } else {
            BST::Node* minNode = this->minNode(pNode->rightChild);
            pNode->key = minNode->key;
            pNode->item = minNode->item;
            pNode->rightChild = this->removeRec(pNode->rightChild, key);
        }
    }
    return pNode;
}

void BST::deepDelete(Node* pNode)
{
    if (!this->isLeaf(pNode)) {
        deepDelete(pNode->leftChild);
        deepDelete(pNode->rightChild);

        delete pNode;
    }
}

BST::Node* BST::minNode(BST::Node* pNode)
{
    BST::Node* minNode = pNode;
    while (!BST::isLeaf(minNode->leftChild)) {
        minNode = minNode->leftChild;
    }
    return minNode;
}

void BST::removeIf(const std::function<bool (KeyType)>& predicate)
{
    this->removeIfRec(this->root, predicate);
}

BST::Node* BST::removeIfRec(Node* pNode, const std::function<bool (KeyType)>& predicate)
{
    if (!this->isLeaf(pNode)) {
        this->removeIfRec(pNode->leftChild, predicate);
        this->removeIfRec(pNode->rightChild, predicate);

        if (predicate(pNode->key)) this->remove(pNode->key);
    }
}

BST::Node* BST::deepCopy(Node* pNode)
{
    Node* newNode = this->leaf();
    if (!this->isLeaf(pNode)) {
        newNode = new Node(pNode->key, pNode->item);
        newNode->leftChild = this->deepCopy(pNode->leftChild);
        newNode->rightChild = this->deepCopy(pNode->rightChild);
    }
    return newNode;
}
