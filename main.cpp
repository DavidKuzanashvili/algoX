#include <iostream>
#include <vector>
#include "include/includes.h"
using namespace std;

int main() {
    Node<int, vector<int>> node1(1, vector<int>(5));
    Node<int, vector<int>> node2(2, vector<int>(5));
    vector<Node<int, vector<int>>> vec = {
        node1,
        node2
    };
    Map<int, vector<int>> map = Map<int, vector<int>>(vec);

    map.insert(node1);
    map.insert(node2);

    auto numbers = map[1];
    for (auto number : numbers) {
        std::cout << number << std::endl;
    }

    return 0;
}
