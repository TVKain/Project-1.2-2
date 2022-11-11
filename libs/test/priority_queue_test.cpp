#include "priority_queue.hpp"

int main() {
    ds::priority_queue<int> a;

    ds::priority_queue<int> b(a);

    ds::priority_queue<int> c = a;


    return 0;
}