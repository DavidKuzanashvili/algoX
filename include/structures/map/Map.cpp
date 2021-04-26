//
// Created by David on 4/10/2021.
//

#include "Map.h"

template<typename TKey, typename TValue>
Map<TKey, TValue>::Map(vector<Node<TKey, TValue>> nodes)
    : nodes(nodes)
{
    setTopNode();
    buildTree();
}

template<typename TKey, typename TValue>
void Map<TKey, TValue>::setTopNode() {
    top = nodes[0];
    nodes.erase(nodes.begin());
}

template<typename TKey, typename TValue>
void Map<TKey, TValue>::moveLeft(Node<TKey, TValue>* currentNode, Node<TKey, TValue>* node) {
    if (currentNode->getLeft() == NULL) {
        currentNode->setLeft(node);
        return;
    }

    setInPosition(currentNode->getLeft(), node);
}

template<typename TKey, typename TValue>
void Map<TKey, TValue>::moveRight(Node<TKey, TValue>* currentNode, Node<TKey, TValue>* node) {
    if (currentNode->getRight() == NULL) {
        currentNode->setRight(node);
        return;
    }

    setInPosition(currentNode->getRight(), node);
}

template<typename TKey, typename TValue>
void Map<TKey, TValue>::setInPosition(Node<TKey, TValue> *currentNode, Node<TKey, TValue> *node) {
    if (currentNode->getKey() < node->getKey()) {
        moveRight(currentNode, node);
        return;
    }

    moveLeft(currentNode, node);
}

template<typename TKey, typename TValue>
void Map<TKey, TValue>::buildTree() {
    for(int i = 0; i < nodes.size(); ++i) {
        setInPosition(&top, &nodes[i]);
    }
}

template<typename TKey, typename TValue>
void Map<TKey, TValue>::insert(Node<TKey, TValue> node)
{
    nodes.push_back(node);
    setInPosition(&top, &nodes[nodes.size() - 1]);
}

template<typename TKey, typename TValue>
Node<TKey, TValue> Map<TKey, TValue>::find(TKey key)
{
    Node<TKey, TValue>* currentNode = &top;
    while (currentNode->getKey() != key)
    {
        currentNode = currentNode->getKey() < key ? currentNode->getRight() : currentNode->getLeft();
        if (currentNode == NULL)
        throw std::invalid_argument("Not found");
    }

    return *currentNode;
}

template<typename TKey, typename TValue>
TValue Map<TKey, TValue>::operator[](TKey key) {
    auto node = find(key);
    return node.getValue();
}