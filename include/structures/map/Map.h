//
// Created by David on 4/10/2021.
//

#ifndef ALGOX_MAP_H
#define ALGOX_MAP_H

#include<vector>
#include<iostream>
using namespace std;

#include "../nodes/Node.h"

template <typename TKey, typename TValue>
class Map {
private:
    vector<Node<TKey, TValue>> nodes;
    Node<TKey, TValue> top;

    void setTopNode();

    void moveLeft(Node<TKey, TValue>* currentNode, Node<TKey, TValue>* node);
    void moveRight(Node<TKey, TValue>* currentNode, Node<TKey, TValue>* node);

    void setInPosition(Node<TKey, TValue>* currentNode, Node<TKey, TValue>* node);
    void buildTree();
public:
    Map() {}

    Map(vector<Node<TKey, TValue>> nodes);

    void insert(Node<TKey, TValue> node);

    Node<TKey, TValue> find(TKey key);

    TValue operator[](TKey key);
};


#endif //ALGOX_MAP_H
