//-----------------------------------------------------------------------------
//
// Source code for MIPT ILab
// Slides: https://sourceforge.net/projects/cpp-lects-rus/files/cpp-graduate/
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
//  Example of range-based queries with std::set
//  compile with: g++ -O2 setsol.cc
//
//----------------------------------------------------------------------------

#include <cassert>
#include <iostream>
#include <set>

namespace {
const char KEY = 'k';
const char QUERY = 'q';
} // namespace

using KeyT = int;

struct Node {
KeyT key_;
int balance_factor() const;
private:
Node *parent_, *left_, *right_;
int height_;
};

namespace Trees {
    template <typename KeyT, typename Comp>
    class SearchTree {
            struct Node; // внутренний узел
            using iterator = Node *; // положение внутри дерева
            Node *top_; 
        public: // селекторы
            iterator lower_bound(KeyT key) const;
            iterator upper_bound(KeyT key) const;
            int distance(iterator fst, iterator snd) const;
        public: // модификаторы
            void insert(KeyT key);
    };
}

template <typename C, typename T> int range_query(const C &s, T fst, T snd) {
    using itt = typename C::iterator;
    itt start = s.lower_bound(fst);
    itt fin = s.upper_bound(snd);
    return mydistance(start, fin);
}

int main() {
    std::set<int> s;
    for (;;) {
        char c;
        std::cin >> c;
        if (!std::cin)
            break;
        if (c == KEY) {
            int value;
            std::cin >> value;
            assert(std::cin.good());
            s.insert(value);
        }
        if (c == QUERY) {
            int fst, snd;
            std::cin >> fst >> snd;
            assert(std::cin.good());
            std::cout << range_query(s, fst, snd) << " ";
        }
    }
    std::cout << std::endl;
}