//
// Created by David on 4/10/2021.
//

#include "Node.h"

template<typename TKey, typename TValue>
Node<TKey, TValue> *Node<TKey, TValue>::getLeft() const {
    return left;
}

template<typename TKey, typename TValue>
void Node<TKey, TValue>::setLeft(Node *left) {
    Node::left = left;
}

template<typename TKey, typename TValue>
Node<TKey, TValue> *Node<TKey, TValue>::getRight() const {
    return right;
}

template<typename TKey, typename TValue>
void Node<TKey, TValue>::setRight(Node *right) {
    Node::right = right;
}

template<typename TKey, typename TValue>
TKey Node<TKey, TValue>::getKey() const {
    return key;
}

template<typename TKey, typename TValue>
void Node<TKey, TValue>::setKey(TKey key) {
    Node::key = key;
}

template<typename TKey, typename TValue>
TValue Node<TKey, TValue>::getValue() const {
    return value;
}

template<typename TKey, typename TValue>
void Node<TKey, TValue>::setValue(TValue value) {
    Node::value = value;
}
