#ifndef ALGOX_GRAPH_H
#define ALGOX_GRAPH_H

#include <iostream>
#include <utility>
#include <vector>
#include <deque>
using namespace std;

#include "Node.hpp"

class Graph {
private:
    deque<Node> closed;
    deque<Node> open;

    int nodesSearched = 0;

    static bool goalReached(vector<int> state)
    {
        vector<int> goalState = vector<int>
        {
            1, 2, 3,
            4, 5, 6,
            7, 8, 0
        };

        for(int i = 0; i < goalState.size(); i++)
        {
            if (state[i] != goalState[i]) return false;
        }

        return true;
    }

    bool nodeAlreadyOpened(Node& n)
    {
        for(const Node& node : closed)
        {
            if (node == n) return true;
        }

        for(const Node& node : open)
        {
            if (node == n) return true;
        }

        return false;
    }

    void addOpenedNode(Node tmp)
    {
        if(!nodeAlreadyOpened(tmp))
            open.push_back(tmp);
    }

    void generateChildStates(Node n)
    {
        if (n.canMoveUp()) {
            Node tmp = n;
            tmp.moveUp();
            addOpenedNode(tmp);
        }

        if (n.canMoveRight()) {
            Node tmp = n;
            tmp.moveRight();
            addOpenedNode(tmp);
        }

        if (n.canMoveDown()) {
            Node tmp = n;
            tmp.moveDown();
            addOpenedNode(tmp);
        }

        if (n.canMoveLeft()) {
            Node tmp = n;
            tmp.moveLeft();
            addOpenedNode(tmp);
        }
    }

    void find()
    {
        if (open.empty())
        {
            cout << "Solution not found" << endl;
            return;
        }

        Node currentNode = open.front();

        cout << "<<<<<<<<<<<<<<<<<<" << endl;
        currentNode.printState();
        cout << "<<<<<<<<<<<<<<<<<<" << endl;

        open.pop_front();
        if (goalReached(currentNode.getState()))
        {
            cout << "Searched " << nodesSearched << " node total\n";
            return;
        }
        generateChildStates(currentNode);
        closed.push_back(currentNode);
        nodesSearched++;
        find();
    }
public:
    void solve(vector<int> startingState)
    {
        // Init starting point
        Node node(std::move(startingState));
        open.push_back(node);

        find();
    }
};

#endif //ALGOX_GRAPH_H
