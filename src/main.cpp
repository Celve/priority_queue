#include "priority_queue.hpp"
#include <iostream>

using namespace std;

sjtu::priority_queue<int> q, p;

int main() {
    for (int i = 0; i < 10; ++i)
        q.push(i);
    for (int i = 10; i < 20; ++i)
        p.push(i);
    p.merge(q);
}
