//
// Created by David on 4/10/2021.
//

#ifndef ALGOX_NODE_H
#define ALGOX_NODE_H

template<typename TKey, typename TValue>
class Node {
private:
    Node* left;
    Node* right;
    TKey key;
    TValue value;
public:
    Node() {}

    Node(Node *left, Node *right) : left(left), right(right) {}

    Node(TKey key, TValue value) : key(key), value(value) {}

    Node *getLeft() const;

    void setLeft(Node *left);

    Node *getRight() const;

    void setRight(Node *right);

    TKey getKey() const;

    void setKey(TKey key);

    TValue getValue() const;

    void setValue(TValue value);
};

#endif //ALGOX_NODE_H
