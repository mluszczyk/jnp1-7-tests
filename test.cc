#include "bst_imp.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

template<typename T>
void assert_str(BST<T> bst, string s) {
    std::stringstream ss;
    ss << bst;
    assert(ss.str() == s);
}

void assert_almost_equal(double x, double y) {
    assert(abs(x - y) < 0.001);
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

    // additional tests for special cases
    {
        BST<int> bst({1, 1, 1, 1});
        assert_str(bst.find(1), "1 1 1 1 ");
        assert(bst.min() == 1);
        assert(bst.max() == 1);
        assert(bst.height() == 4);
    }

    {
        BST<int> bst;
        assert(bst.empty());
        assert_throws([&](){bst.left();});
        assert_throws([&](){bst.right();});
        assert_throws([&](){bst.value();});
        assert_throws([&](){bst.min();});
        assert_throws([&](){bst.max();});
    }

    {
        BST<int> empty;
        assert_throws([&](){max_diff(empty);});
        BST<int> one_element({1});
        assert_throws([&](){max_diff(one_element);});
        BST<int> equal_elements({1, 1});
        assert(max_diff(equal_elements) == 0);
    }

    // operator + both ways
    {
        BST<int> bst({1, 5, 6});
        assert_str(bst + 3, "1 3 5 6 ");
        assert_str(3 + bst, "1 3 5 6 ");
    }

    // max diff with a different type than int
    {
        BST<double> bst({0.1, 1.7, 1.9});
        assert_almost_equal(max_diff(bst), 1.6);
    }

    // spine on empty tree
    {
        BST<int> empty;
        auto spined = spine(empty);
        assert(spined.empty());
    }

    // fold on empty tree
    {
        BST<int> empty;
        auto res = empty.fold(5, [](int, int const &) {return 2345;});
        assert(res == 5);
    }

    // and non empty
    {
        BST<int> bst({1, 5, 6, 9, 3, 6});
        vector<int> v, expected({1, 3, 5, 6, 6, 9});
        bst.fold(0, [&](const int, const int& val) { v.push_back(val); return 1; });
        assert(v == expected);
    }

    return 0;
}
