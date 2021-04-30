#ifndef ALGOX_NODE_HPP
#define ALGOX_NODE_HPP

#include <iostream>
#include <utility>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

class Node {
private:
    // მდგომარეობა
    vector<int> state;
    /*
     * სიღრმე, რომელზეც იმყოფება კვანძი,
     * გამოყენებული იქნება როგორც გზის ფუნქცია,
     * ვინაიდან ნებისმიერ კვანზე გადასვლის ფასი
     * უდრის 1_ს
     * */
    int depth = 0;

    // მიზნის მდგომარეობა (იყენებს ევრისტიკული ფუნქცია)
    vector<int> goal = vector<int>
    {
        1, 2, 3,
        4, 5, 6,
        7, 8, 0
    };

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
    Node() = default;

    explicit Node(vector<int> s)
    {
        state = std::move(s);
    }

    [[nodiscard]] inline int getDepth() const { return depth; }

    inline void setDepth(int val) { depth = val; }

    vector<int> getState()
    {
        return state;
    }

    // ბეჭდავს მდგომარეობას
    void printState(int cols = 3)
    {
        for(int i = 0; i < state.size(); i++)
        {
            cout << state[i] << " ";
            if ((i + 1) % cols == 0) cout << endl;
        }

        cout << "\n Node depth: " << depth << endl;
        cout << "\n Node cost: " << cost() << endl;
    }

    /*
     * დამხმარე move ფუნქციები
     * მდგომარეობის რიცხვების შესაბამის
     * ადგილზე მოსათავსებლად
     * */
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

    /*
     * ტოლობის ოპერატორი ორი კვანძის მდგომარეობების შესადარებლად
     * */
    bool operator ==(Node& node) const
    {
        for(int i = 0; i < state.size(); i++)
        {
            if (state[i] != node.getState()[i])
                return false;
        }
        return true;
    }

    /*
     * უტოლობის ოპერატორი ორი კვანძის მდგომარეობების შესადარებლად
     * */
    bool operator !=(Node& node) const
    {
        for(int i = 0; i < state.size(); i++)
        {
            if (state[i] != node.getState()[i])
                return true;
        }
        return false;
    }

    // შემფასებელი ფუნქცია (გზის ფასი + ევრისტიკული ფუნქციის მნიშვნელობა)
    int cost() {
        return depth + heuristic();
    }

    /*
     * ევრისტიკული h ფუნქცია, რომელიც ითვლის მოცემული
     * კვანძისთვის (მდგომარეობისთვის) რადმენი რიცხვი
     * არ არის თავის ადგილზე
     * */
    int heuristic()
    {
        int result = 0;

        for(int i = 0; i < goal.size(); i++)
        {
            if (goal[i] != state[i])
                result++;
        }

        return result;
    }

    void setGoal(vector<int> g)
    {
        goal = std::move(g);
    }
};

#endif //ALGOX_NODE_HPP
