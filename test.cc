#include "bst_imp.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template<typename T>
void assert_str(BST<T> bst, string s) {
    std::stringstream ss;
    ss << bst;
    assert(ss.str() == s);
}

template<typename T>
void assert_throws(T f) {
    bool thrown = false;
    try {
        f();
    } catch(std::logic_error e) {
        thrown = true;
    }
    assert(thrown);
}

int main() {
    // Example translated into assertions.

    BST<int> bst({3,4,1,2,7,3});
    assert_str(bst, "1 2 3 3 4 7 ");

    {
        assert(bst.size() == 6);
        assert(bst.min() == 1);
        assert(bst.max() == 7);
    }

    assert(bst.height() == 4);
    assert(spine(bst).height() == 6);
    assert_str(bst.find(4), "4 7 ");
    assert(max_diff(bst) == 3);
    assert_throws([&](){bst.find(11);});

    return 0;
}
