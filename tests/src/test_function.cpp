#include "tree.hpp"
#include <vector>
#include <set>


int main(){

    Trees::SearchTree<int, int> test_tree;

    test_tree.insert(1);
    
    test_tree.insert(2);
    
    test_tree.insert(3);
    
    test_tree.insert(4);
    test_tree.insert(5);
    test_tree.insert(6);

    test_tree.dump_tree();
    cout << endl;

    return 0;
}

