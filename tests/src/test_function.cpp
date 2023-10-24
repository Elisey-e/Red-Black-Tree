#include "tree.hpp"
#include <vector>
#include <set>


int main(){

    std::cout << "ok\n";

    Trees::SearchTree<int, int> test_tree;

    int y = 5;
    int * x = new int;
    *x = 5;
    cout << *x << &y << endl << endl;

    test_tree.insert(1);
    test_tree.insert(2);
    test_tree.insert(3);
    test_tree.insert(4);
    test_tree.insert(5);
    test_tree.insert(6);

    return 0;
}

