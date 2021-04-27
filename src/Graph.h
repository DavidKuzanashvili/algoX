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

    int getInsertionIndex(Node& node)
    {
        if (node.getCost() <= open.front().getCost())
            return 0;

        if (node.getCost() >= open.back().getCost())
            return open.size();

        int result = -1;
        for(int i = 1; i < open.size(); i++)
        {
            if (node.getCost() >= open[i - 1].getCost() && node.getCost() <= open[i].getCost())
            {
                result = i;
            }
        }

        if (open[result].getCost() <= node.getCost())
        {
            result++;
        }

        return result;
    }

    void insert(Node& node)
    {
        int index = getInsertionIndex(node);
        open.resize(open.size() + 1);

        if (open.size() <= 1)
        {
            open.push_back(node);
            return;
        }

        int i = open.size() - 2;

        while(i >= index)
        {
            open[i + 1] = open[i];
            i--;
        }

        open[index] = node;
    }

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
        {
            insert(tmp);
            // open.push_back(tmp);
        }
    }

    void generateChildStates(Node n)
    {
        if (n.canMoveUp()) {
            Node tmp = n;
            tmp.setDepth(n.getDepth() + 1);
            tmp.moveUp();
            tmp.setCost(tmp.getDepth() + tmp.heuristic());
            addOpenedNode(tmp);
        }

        if (n.canMoveRight()) {
            Node tmp = n;
            tmp.setDepth(n.getDepth() + 1);
            tmp.moveRight();
            tmp.setCost(tmp.getDepth() + tmp.heuristic());
            addOpenedNode(tmp);
        }

        if (n.canMoveDown()) {
            Node tmp = n;
            tmp.setDepth(n.getDepth() + 1);
            tmp.moveDown();
            tmp.setCost(tmp.getDepth() + tmp.heuristic());
            addOpenedNode(tmp);
        }

        if (n.canMoveLeft()) {
            Node tmp = n;
            tmp.setDepth(n.getDepth() + 1);
            tmp.moveLeft();
            tmp.setCost(tmp.getDepth() + tmp.heuristic());
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
        node.setDepth(0);
        node.setCost(node.getDepth() + node.heuristic());
        open.push_back(node);

        find();
    }
};

#endif //ALGOX_GRAPH_H
