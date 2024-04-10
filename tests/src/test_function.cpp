#include "tree.hpp"
#include <vector>
#include <set>


int main(){

    Trees::SearchTree<int, int> test_tree;

    // for (int i = 1; i < 100; i++){
    //     test_tree.insert(i);
    // }

    test_tree.insert(1);
    test_tree.insert(2);
    test_tree.insert(3);
    test_tree.insert(4);
    test_tree.insert(5);
    test_tree.insert(6);
    test_tree.insert(7);
    test_tree.insert(8);
    test_tree.insert(9);
    test_tree.insert(10);
    // test_tree.pop_node(4);

    test_tree.dump_tree();
    cout << endl;

    cout << "\nNon parallel summ calculating:\n" << test_tree.non_parallel_summ() << "\n\nParallel summ calculating:";
    cout << "\n";
    cout << test_tree.parallel_summ() << "\n";

    return 0;
}

