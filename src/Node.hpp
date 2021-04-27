#ifndef ALGOX_NODE_HPP
#define ALGOX_NODE_HPP

#include <iostream>
#include <utility>
#include <vector>
using namespace std;

class Node {
private:
    vector<int> state;
    int depth = 0;
    int cost = 0;
    int getZeroPosition()
    {
        for (int i = 0; i < state.size(); i++)
        {
            if (state[i] == 0)
            {
                return i;
            }
        }
        return -1;
    }
public:
    Node()
    {
        state = vector<int>
        {
                1, 2, 3,
                4, 0, 6,
                7, 8, 5
        };
    }

    explicit Node(vector<int> s)
    {
        state = std::move(s);
    }

    [[nodiscard]] inline int getDepth() const { return depth; }

    inline void setDepth(int val) { depth = val; }

    [[nodiscard]] inline int getCost() const { return cost; }

    inline void setCost(int val) { cost = val; }

    vector<int> getState()
    {
        return state;
    }

    void printState(int cols = 3)
    {
        for(int i = 0; i < state.size(); i++)
        {
            cout << state[i] << " ";
            if ((i + 1) % cols == 0) cout << endl;
        }

        cout << "\n Node depth: " << depth << endl;
    }

    void moveUp()
    {
        int i = getZeroPosition();
        state[i] = state[i + 3];
        state[i + 3] = 0;
    }

    bool canMoveUp()
    {
        int i = getZeroPosition();
        return i < 6;
    }


    void moveRight()
    {
        int i = getZeroPosition();
        state[i] = state[i - 1];
        state[i - 1] = 0;
    }

    bool canMoveRight()
    {
        int i = getZeroPosition();
        return (i + 1) % 3 != 1;
    }

    void moveDown() {
        int i = getZeroPosition();
        state[i] = state[i - 3];
        state[i - 3] = 0;
    }

    bool canMoveDown()
    {
        int i = getZeroPosition();
        return i >= 3;
    }

    void moveLeft()
    {
        int i = getZeroPosition();
        state[i] = state[i + 1];
        state[i + 1] = 0;
    }

    bool canMoveLeft()
    {
        int i = getZeroPosition();
        return (i + 1) % 3 != 0;
    }

    bool operator ==(Node& node) const
    {
        for(int i = 0; i < state.size(); i++)
        {
            if (state[i] != node.getState()[i])
                return false;
        }
        return true;
    }

    bool operator !=(Node& node) const
    {
        for(int i = 0; i < state.size(); i++)
        {
            if (state[i] != node.getState()[i])
                return true;
        }
        return false;
    }

    int heuristic()
    {
        vector<int> goal = vector<int>
        {
                1, 2, 3,
                4, 0, 6,
                7, 8, 5
        };

        int result = 0;

        for(int i = 0; i < goal.size(); i++)
        {
            if (goal[i] == state[i])
                result++;
        }

        return result;
    }
};

#endif //ALGOX_NODE_HPP
