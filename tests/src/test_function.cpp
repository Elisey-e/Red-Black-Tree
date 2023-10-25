#include "tree.hpp"
#include <vector>
#include <set>


int main(){

    std::cout << "ok\n";

    Trees::SearchTree<int, int> test_tree;

    test_tree.insert(1);
    test_tree.insert(2);
    test_tree.insert(3);
    test_tree.insert(4);
    test_tree.insert(5);
    test_tree.insert(6);

    return 0;
}

