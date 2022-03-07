#include "priority_queue.hpp"
#include <iostream>

using namespace std;

sjtu::priority_queue<int> q;

int main() {
    for (int i = 0; i < 10; ++i)
        q.push(i);
    for (int i = 0; i < 10; ++i) {
        int v = q.top();
        q.pop();
        cout << v << endl;
    }
}
