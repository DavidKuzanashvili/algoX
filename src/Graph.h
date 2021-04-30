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
    // დახურული კვანძები
    deque<Node> closed;
    //გახსნილი კვანძები
    deque<Node> open;
    /*
     * თუ solveWithAStar false_ია მაშინ ალგორითმი
     * ამონახნს პოულობს სრული გადარჩევით, სხვა შემთხვევაში
     * იყენებს ძებნისთვის ფასისი ფუნქციას, რომელიც წარმოადგენს
     * ევრისტიკული და გზის სიგრძის ფუნქციების ჯაბს
     * */
    bool solveWithAStar = false;

    /*
     * კვანძების რაოდენობა, რომელიც გაიხსნა
     * ალგორითმის მსვლელობის დროს
     * */
    int nodesSearched = 0;

    // მიზნის მდგომარეობა ნაგულისხმევი მნიშვნელობით
    vector<int> goalState = vector<int>
        {
            1, 2, 3,
            4, 5, 6,
            7, 8, 0
        };

    // ამოწმებს მიიღწა თუ არა მიზნის მდგომარეობა
    bool goalReached(vector<int> state)
    {
        for(int i = 0; i < goalState.size(); i++)
        {
            if (state[i] != goalState[i]) return false;
        }

        return true;
    }

    // შემფასებელი ფუნქციის გამოყენებით კვანძს სვავს შესაბამის ინდექსზე
    void insert(Node node)
    {
        if (open.empty() || node.cost() <= open.front().cost())
        {
            open.insert(open.begin(), node);
            return;
        }

        if (node.cost() >= open.back().cost())
        {
            open.insert(open.end(), node);
            return;
        }


        size_t result = 0;
        for(int i = 1; i < open.size(); i++)
        {
            if (node.cost() >= open[i - 1].cost() && node.cost() <= open[i].cost())
            {
                result = i - 1;
            }
        }

        if (open[result].cost() <= node.cost())
        {
            result++;
        }

        auto it = open.begin() + result;
        open.insert(it, node);
    }

    // ამოწმებს კვანძი ხომ არ იმყოფება ღია ან დახურულ დეკში
    bool nodeAlreadyOpened(Node n)
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

    /*
     * ამოწმებს ხომ განხილულია თუ არა კვანძი,
     * და თუ განხილული არა არის ამატებს ღია კვანძებში
     * (თუ solveWithAStar დასეტილია როგორც true, მაშინ
     * ღია კვანძი ისმება შემფასებელი ფუნქციის გამოყენებით შესაბამის
     * ადგილზე - ალაგაბს კვანძებს პრიორიტეტის მიხედვით, სხვა
     * შემთხვევაში მოუწესრიგებლად ამატებს დეკში)
     * */
    void addOpenedNode(const Node& tmp)
    {
        if(!nodeAlreadyOpened(tmp))
        {
            if (solveWithAStar) {
                insert(tmp);
                return;
            }
            open.push_back(tmp);
        }
    }

    // აგენერირებს შვილობილ მდგომარეობებს და ამატებს ღია კვანძებში
    void generateChildStates(Node n)
    {
        if (n.canMoveUp()) {
            Node tmp = n;
            tmp.setDepth(n.getDepth() + 1);
            tmp.moveUp();
            addOpenedNode(tmp);
        }

        if (n.canMoveRight()) {
            Node tmp = n;
            tmp.setDepth(n.getDepth() + 1);
            tmp.moveRight();
            addOpenedNode(tmp);
        }

        if (n.canMoveDown()) {
            Node tmp = n;
            tmp.setDepth(n.getDepth() + 1);
            tmp.moveDown();
            addOpenedNode(tmp);
        }

        if (n.canMoveLeft()) {
            Node tmp = n;
            tmp.setDepth(n.getDepth() + 1);
            tmp.moveLeft();
            addOpenedNode(tmp);
        }
    }

    /*
     * ძებნის მეთოდი ეძებს მიზნის მდგომარეობას რეკურსიულად
     * თან ბეჭდავს განვლილ გზას
     * */
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
    // ინიციალიზებას უკეთებს საწყის კვანძს და უშვებს რეკურსილ ძებნას
    void solve(vector<int> startingState, bool useAStar = false)
    {
        this->solveWithAStar = useAStar;
        // Init starting point
        Node node(std::move(startingState));
        node.setDepth(0);
        node.setGoal(goalState);

        open.push_back(node);

        find();
    }

    // მისნის მდგომარეობას ანიჭებს შესაბამის მნიშვნელობას
    void setGoalState(vector<int> gs)
    {
        goalState = std::move(gs);
    }
};

#endif //ALGOX_GRAPH_H
