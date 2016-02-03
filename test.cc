#include "bst_imp.h"
#include "bst_imp.h"
#include <iostream>
#include <cassert>
#include <sstream>
#include <vector>
#include <forward_list>
using namespace std;

template <typename T>
void assertEQ(const BST<T>& bst, const string &s) {
    stringstream ss;
    ss << bst;
    assert(ss.str() == s);
}

#define assertThrow(OP) { \
    try { \
    OP; \
    assert(false); \
    } catch(std::logic_error&) { } \
}


void test2();

void assertEmpty(const BST<int> &bst) {
    assertEQ(bst, "");
    assert(bst.size() == 0);
    assertThrow(bst.min());
    assertThrow(bst.max());
    assertThrow(bst.value());
    assertThrow(bst.left());
    assertThrow(bst.right());
    assert(bst.height() == 0);
}

void assertOne(const BST<int> &bst) {

        assertEQ(bst, "3");
        assert(bst.size() == 1);
        assert(bst.min() == 3);
        assert(bst.max() == 3);
        assert(bst.height() == 1);

}

void test3();
int main() {
    {
        BST<int> bst({});
        assertEmpty(bst);
        BST<int> bst2 = bst;
        assertEmpty(bst2);
        std::vector<int> v;
        BST<int> bst3(v.begin(), v.end());
        assertEmpty(bst3);
        assertOne(bst + 3);
        assertOne(3 + bst);
    }


    {
        BST<int> bst({3});
        assertOne(bst);
    }
    {
        BST<int> bst({42, 44, 45});
        assert(max_diff(bst) == 2);
    }
    {
        BST<int> bst({3, 4});
        // 3    |
        //  \   |
        //   4  |
        assertEQ(bst, "3 4");
        assert(bst.size() == 2);
        assert(bst.min() == 3);
        assert(bst.max() == 4);
        assert(bst.height() == 2);
    }

    {
        BST<int> bst({3, 4, 1});
        //   3    |
        //  / \   |
        // 1   4  |
        assertEQ(bst, "1 3 4");
        assert(bst.size() == 3);
        assert(bst.min() == 1);
        assert(bst.max() == 4);
        assert(bst.height() == 2);
    }

    {
        BST<int> bst({3, 4, 1, 2});
        //    3    |
        //   / \   |
        //  1   4  |
        //   \     |
        //    2    |
        assertEQ(bst, "1 2 3 4");
        assert(bst.size() == 4);
        assert(bst.min() == 1);
        assert(bst.max() == 4);
        assert(bst.height() == 3);
    }
    {
        BST<std::string> bst ({"abc", "a", "abc", "gde", "ab"});
        assertEQ(bst, "a ab abc abc gde");
        assert(bst.size() == 5);
        assert(bst.min() == "a");
        assert(bst.max() == "gde");
        assert(bst.height() == 4);
        assertEQ(bst.left(), "a ab abc");
        assertEQ(bst.right(), "gde");
        assertEQ(bst.find("ab"), "ab");
        assert(!bst.empty());
        assert(bst.value() == "abc");
        assert(spine(bst).height() == bst.size());
        assert((bst + string("XD")).size() == 6);
        assert((string("XD") + bst).size() == 6);
        vector<string> v;
        BST<string> (v.begin(), v.end());


    }
    {
        std::initializer_list<int> l = {1, 2, 3};
        BST<int> bst(l.begin(), l.end());
        assert(bst.size() == 3);
        assert(bst.min() == 1);
        assertEQ(bst, "1 2 3");
    }


    {
        std::forward_list<int> l = {42};
        BST<int> bst(l.begin(), l.end());
        assert(bst.size() == 1);
        assert(!bst.empty());
        assert(bst.value() == 42);
        assertEQ(bst, "42");
    }

    {
        BST<int> bst({3,4,1,2,7});
        //    3      |
        //   / \     |
        //  1   4    |
        //   \   \   |
        //    2   7  |
        assertEQ(bst, "1 2 3 4 7");
        assert(bst.size() == 5);
        assert(bst.min() == 1);
        assert(bst.max() == 7);
        assert(bst.height() == 3);
        assert(bst.find(1).min() == 1);
        assert(bst.find(1).max() == 2);
        assert(max_diff(bst) == 3);
    }

    BST<int> bst({3,4,1,2,7,3});
    //    3          |
    //   / \         |
    //  1   4        |
    //   \   \       |
    //    2   7      |
    //     \         |
    //      3        |



    assertEQ(bst, "1 2 3 3 4 7");

    assert(bst.size() == 6);
    assert(bst.min() == 1);
    assert(bst.max() == 7);
    assert(bst.height() == 4);
    assert(bst.find(4).height() == 2);

    assert(spine(bst).height() == 6);
    auto spina = spine(bst);
    assert(spina.find(7).height() == 6);
    assert(spina.find(4).height() == 5);
    assert(spina.find(3).height() == 4);
    assert(spina.find(3).min() == 1);
    assert(spina.find(3).max() == 3);
    assert(spina.find(2).height() == 2);
    assert(spina.find(1).height() == 1);
    assertThrow(spina.find(42).height());
    assertEQ(bst.find(4), "4 7");
    assertThrow(bst.find(11));
    assert(max_diff(bst) == 3);


    {
        auto newBST = bst + 42;
        assertEQ(newBST, "1 2 3 3 4 7 42");

        assertEQ(newBST.find(4), "4 7 42");
        assertEQ(newBST.find(7), "7 42");
        assertEQ(newBST.find(42), "42");

        assert(newBST.find(4).height() == 3);
        assert(max_diff(newBST) == 35);
        assert(newBST.size() == 7);
        assert(newBST.min() == 1);
        assert(newBST.max() == 42);
    }
    {
        auto newBST = 0 + bst + 42;
        assertEQ(newBST, "0 1 2 3 3 4 7 42");

        assertEQ(newBST.find(4), "4 7 42");
        assertEQ(newBST.find(7), "7 42");
        assertEQ(newBST.find(42), "42");
        assertEQ(newBST.find(1), "0 1 2 3");
        assertEQ(newBST.find(0), "0");
        assertThrow(newBST.find(-1));
        assertEQ(newBST.find(2), "2 3");

        assertEQ(newBST.find(7), "7 42");
        assertEQ(newBST.find(42), "42");

        assert(newBST.find(4).height() == 3);
        assert(max_diff(newBST) == 35);
        assert(newBST.size() == 8);
        assert(newBST.min() == 0);
        assert(newBST.max() == 42);

    }


    test2();
    test3();
    cout << "Done" << endl;
    return 0;
}

#include <ctime>
#include <cstdlib>
void test2() {
    std::cout << "testy Michała Banaszkiewicza" << std::endl;
        {
            BST<int> bst({3});
            // 3
        }

        {
            BST<int> bst({3, 4});
            // 3    |
            //  \   |
            //   4  |
        }

        {
            BST<int> bst({3, 4, 1});
            //   3    |
            //  / \   |
            // 1   4  |
        }

        {
            BST<int> bst({3, 4, 1, 2});
            //    3    |
            //   / \   |
            //  1   4  |
            //   \     |
            //    2    |
        }
        {
            BST<int> bst({3,4,1,2,7});
            //    3      |
            //   / \     |
            //  1   4    |
            //   \   \   |
            //    2   7  |
        }

        {
            BST<int> bst({3,4,1,2,7,3});
            //    3          |
            //   / \         |
            //  1   4        |
            //   \   \       |
            //    2   7      |
            //     \         |
            //      3        |

            std::cout << bst << std::endl; // prints 1 2 3 3 4 7
            std::cout << bst.size() << std::endl; //prints 6
            std::cout << bst.min() << std::endl; // prints 1
            std::cout << bst.max() << std::endl; // prints 7
            std::cout << bst.height() << std::endl; // prints 4
            std::cout << spine(bst).height() << std::endl; // prints 6
            std::cout << bst.find(4) << std::endl; // prints 4 7
            int exceptions = 0;
            try {
                std::cout << bst.find(11) << std::endl; //throws
            }
            catch (std::logic_error)
            {
                exceptions++;
            }
            assert(exceptions);

            std::cout << max_diff(bst) << std::endl; //prints 3
        }

        {
            BST<int> bst({});
            assert(bst.empty());

            int exceptions = 0;

            try
            {
                bst.left();
            }
            catch(std::logic_error)
            {
                ++exceptions;
            }

            try
            {
                bst.right();
            }
            catch(std::logic_error)
            {
                ++exceptions;
            }

            try
            {
                bst.value();
            }
            catch(std::logic_error)
            {
                ++exceptions;
            }

            try
            {
                bst.min();
            }
            catch(std::logic_error)
            {
                ++exceptions;
            }

            try
            {
                bst.max();
            }
            catch(std::logic_error)
            {
                ++exceptions;
            }

            try
            {
                max_diff(bst);
            }
            catch(std::logic_error)
            {
                ++exceptions;
            }

            try
            {
                bst.find(0);
            }
            catch(std::logic_error)
            {
                ++exceptions;
            }

            assert(exceptions == 7);
            assert(!bst.size());
            assert(!bst.height());
        }

        {
            BST<int> bst({100, 52, 142, 166, 109, 105, 134, 150, 170});
            assert(!bst.empty());
            assert(bst.size() == 9);
            assert(bst.min() == 52);
            assert(bst.max() == 170);

            assert(bst.height() == 4);
            assert(spine(bst).height() == 9);
            assert(bst.find(52).height() == 1);
            assert(bst.find(109).height() == 2);
            assert(bst.find(142).height() == 3);
            assert(max_diff(bst) == 48);

            BST<int> bst2 = bst + 1000;

            assert(bst2.size() - 1 == bst.size());
            assert(bst2.max() == 1000);

            BST<int> bst3 = 1 + bst2;
            assert(bst3.size() - 1 == bst2.size());
            assert(bst3.min() == 1);

        }

        {
            BST<int> bst({1});
            assert(!bst.empty());
            assert(bst.size() == 1);
            assert(bst.min() == 1);
            assert(bst.max() == 1);

            assert(bst.height() == 1);
            assert(spine(bst).height() == 1);
            assert(bst.find(1).height() == 1);

            int exceptions = 0;

            try
            {
                max_diff(bst);
            }
            catch(...)
            {
                ++exceptions;
            }

            assert(exceptions);

            BST<int> bst2 = bst + 1;
            BST<int> bst3 = bst2 + 1;

            assert(!bst.empty());
            assert(bst.size() == 1);
            assert(bst.min() == 1);
            assert(bst.max() == 1);

            assert(bst.height() == 1);
            assert(spine(bst).height() == 1);
            assert(bst.find(1).height() == 1);


            assert(bst3.height() == 3);
            assert(spine(bst3).height() == 3);
            // assert(bst3.find(1).height() == 3); // depends on implementation

            assert(!max_diff(bst3));
        }

        {
            BST<int> bst({7, 0, 1, 1, 1, 1, 1, 5, 6});


            auto f = [] (int a, int b) {
                return a + b;
            };

            assert(bst.fold(0, f) == 23);

        }

        {
            BST<int> bst = BST<int>();

            auto f = [] (int a, int b) {
                return a + b;
            };

            assert(bst.fold(10, f) == 10);

        }

        {
            BST<int> bst({});

            BST<int> bst2 = bst + 1;

            assert(!bst2.empty());
            assert(bst.empty());
            assert(bst2.size() == 1);
            assert(bst2.height() == 1);
            assert(bst2.min() == 1);
            assert(bst2.max() == 1);
        }

        {
            BST<int> bst({});

            BST<int> bst2 = -1 + bst;

            assert(!bst2.empty());
            assert(bst2.size() == 1);
            assert(bst2.height() == 1);
            assert(bst2.min() == -1);
            assert(bst2.max() == -1);
        }

        {
            std::srand (unsigned(std::time(0)));
            std::vector<int> vect;

            for (int i = 1; i <= 100; ++i)
                vect.push_back(i);

            std::random_shuffle (vect.begin(), vect.end());

            BST<int> bst(vect.begin(), vect.end());

            assert(spine(bst).height() == 100);
            assert(bst.size() == 100);
            assert(bst.min() == 1);
            assert(bst.max() == 100);
            std::cout << bst << std::endl; //prints 1..100

        }

        {
            BST<int> bst({25, 5, 9, 1});
            assert(max_diff(bst) == 16);

            BST<int> bst2 = bst + 500;
            BST<int> bst3 = bst2 + 700;
            BST<int> bst4 = bst3 + 495;
            assert(max_diff(bst4) == 470);

        }

        {
            BST<int> bst({10, 30, 11, 31});
            assert(max_diff(bst) == 19);
        }

        {
            BST<int> bst({10, 30, 11, 31});
            assert(max_diff(bst) == 19);
        }

        {
            BST<int> bst({3, -7, 10, -20, 1});
            assert(max_diff(bst) == 13);
        }

        {

            std::vector<BST<int>> bst_vect;

            bst_vect.push_back(BST<int>({}));

            for (int i = 1; i <= 100; ++i)
                bst_vect.push_back(i + bst_vect[i - 1]);

            for (int i = 1; i <= 100; ++i)
            {
                assert(bst_vect[i].size() == (size_t) i);
                assert(bst_vect[i].height() == (size_t) i);
                assert(bst_vect[i].max() == i);
                assert(bst_vect[i].min() == 1);
            }

        }

        {
            std::vector<int> vect;
            BST<int> bst(vect.begin(), vect.end());
            assert(bst.empty());
        }

        {
            BST<int> bst({5});
            BST<int> bst2 = bst.find(5);
            BST<int> bst3 = bst + 1;
            BST<int> bst4 = 19 + bst2;

            assert(bst3.value() == 5);
            assert(bst3.min() == 1);
            assert(bst3.max() == 5);

            assert(bst4.value() == 5);
            assert(bst4.min() == 5);
            assert(bst4.max() == 19);

        }

        {
            BST<int> bst({});

            BST<int> bst2 = spine(bst);

            assert(!bst2.size());
            assert(bst2.empty());
        }

        {
            BST<int> bst({5, 6, 12, 43, 0, 45, 0, 3, 5});

            assert(bst.find(3).size() == 2);
            assert(bst.find(0).height() == 3);
        }

        {
            BST<int> bst({5, 6, 12, 43, 0, 45, 0, 3, 5});

            int exceptions = 0;

            try
            {
                bst.find(4);
            }
            catch(std::logic_error)
            {
                ++exceptions;
            }

            try
            {
                bst.find(7);
            }
            catch(std::logic_error)
            {
                ++exceptions;
            }

            assert(exceptions == 2);
        }

        {
            BST<int> bst({1});

            int exceptions = 0;

            try
            {
                bst.find(4);
            }
            catch(std::logic_error)
            {
                ++exceptions;
            }

            assert(exceptions);
        }

        {
            BST<int> bst({-1});

            int exceptions = 0;

            try
            {
                bst.find(1);
            }
            catch(std::logic_error)
            {
                ++exceptions;
            }

            assert(exceptions);
        }



\


}

#include "bst_imp.h"
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

void test3() {
    std::cout << "// Testy od Marcina Możejko" << std::endl;
    std::cout << "TESTING OF BST.\n" << std::endl;
    BST<int> bst; // Empty one
    std::cout << "1. TESTING EMPTY TREE." << std::endl << std::endl;
    std::cout << "1. bst.size() == 0";
    assert(bst.size() == 0);
    std::cout << " OK.\n";
    std::cout << "1. bst.height == 0";
    assert(bst.height() == 0);
    std::cout << " OK.\n";
    std::cout << "1. spine(bst).size() == 0";
    assert(spine(bst).size() == 0);
    std::cout << " OK.\n";
    std::cout << "1. spine(bst).height() == 0";
    assert(spine(bst).size() == 0);
    std::cout << " OK.\n";
    std::cout << "1. bst.empty() == true";
    assert(bst.empty());
    std::cout << " OK.\n";

    auto sum = [](int arg1, int arg2) {
        return arg1 + arg2;
    };

    std::cout << "1. bst.fold(0, sum) == 0";
    assert(bst.fold(0, sum) == 0);
    std::cout << " OK.\n";

    try {
        std::cout << "1. bst.find(0).size() will throw";
        assert(bst.find(0).size() == 0);
        assert(0);
    } catch (...) {
        std::cout << " OK.\n";
    }

    try {
        std::cout << "1. bst.min() will throw.";
        bst.min();
        assert(0);
    } catch (...) {
        std::cout << " OK\n";
    }

    try {
        std::cout << "1. bst.max() will throw.";
        bst.min();
        assert(0);
    } catch (...) {
        std::cout << " OK\n";
    }

    try {
        std::cout << "1. bst.left() will throw.";
        bst.left();
        assert(0);
    } catch (...) {
        std::cout << " OK\n";
    }

    try {
        std::cout << "1. bst.right() will throw.";
        bst.right();
        assert(0);
    } catch (...) {
        std::cout << " OK\n";
    }

    try {
        std::cout << "1. bst.value() will throw.";
        bst.value();
        assert(0);
    } catch (...) {
        std::cout << " OK\n";
    }

    std::cout << std::endl << "2. TESTING ONE ELEMENT TREE. CONSTRUCTED BY ADDING + 0" << std::endl << std::endl;

    BST<int> bst2 = bst + 0;

    std::cout << "2. bst2.size() == 1";
    assert(bst2.size() == 1);
    std::cout << " OK.\n";
    std::cout << "2. bst2.height == 1";
    assert(bst2.height() == 1);
    std::cout << " OK.\n";
    std::cout << "2. spine(bst2).size() == 1";
    assert(spine(bst2).size() == 1);
    std::cout << " OK.\n";
    std::cout << "2. spine(bst2).height() == 1";
    assert(spine(bst2).height() == 1);
    std::cout << " OK.\n";
    std::cout << "2. spine(bst2).value() == 0";
    assert(spine(bst2).value() == 0);
    std::cout << " OK.\n";
    std::cout << "2. bst2.empty() == false";
    assert(!bst2.empty());
    std::cout << " OK.\n";
    std::cout << "2. bst2.find(0).size() == 1";
    assert(bst2.find(0).size() == 1);
    std::cout << " OK.\n";
    std::cout << "2. bst2.find(0).height() == 1";
    assert(bst2.find(0).height() == 1);
    std::cout << " OK.\n";
    std::cout << "2. bst2.find(0).value() == 0";
    assert(bst2.find(0).value() == 0);
    std::cout << " OK.\n";
    std::cout << "2. bst2.min() == 0";
    assert(bst2.min() == 0);
    std::cout << " OK.\n";
    std::cout << "2. bst2.max() == 0";
    assert(bst2.max() == 0);
    std::cout << " OK.\n";
    std::cout << "2. bst2.left().size() == 0";
    assert(bst2.left().size() == 0);
    std::cout << " OK.\n";
    std::cout << "2. bst2.left().height() == 0";
    assert(bst2.left().height() == 0);
    std::cout << " OK.\n";
    std::cout << "2. bst2.right().size() == 0";
    assert(bst2.right().size() == 0);
    std::cout << " OK.\n";
    std::cout << "2. bst2.right().height() == 0";
    assert(bst2.right().height() == 0);
    std::cout << " OK.\n";
    std::cout << "2. bst2.right().empty() == true";
    assert(bst2.right().empty());
    std::cout << " OK.\n";
    std::cout << "2. bst2.left().empty() == true";
    assert(bst2.left().empty());
    std::cout << " OK.\n";

    std::cout << "2. bst2.fold(1, sum) == 1";
    assert(bst2.fold(1, sum) == 1);
    std::cout << " OK.\n";

    try {
        std::cout << "2. bst2.min() will not throw.";
        bst2.min();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {

        BST<int> bst2 = bst + 0;
        std::cout << "2. bst2.max() will not throw.";
        bst2.min();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "2. bst2.left() will not throw.";
        bst2.left();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "2. bst2.right() will not throw.";
        bst2.right();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "2. bst2.value() will not throw.";
        bst2.value();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    std::cout << std::endl << "3. TESTING ONE ELEMENT TREE. CONSTRUCTED BY {0}" << std::endl << std::endl;

    BST<int> bst3({0});

    std::cout << "3. bst3.size() == 1";
    assert(bst3.size() == 1);
    std::cout << " OK.\n";
    std::cout << "3. bst3.height == 1";
    assert(bst3.height() == 1);
    std::cout << " OK.\n";
    std::cout << "3. spine(bst3).size() == 1";
    assert(spine(bst3).size() == 1);
    std::cout << " OK.\n";
    std::cout << "3. spine(bst3).height() == 1";
    assert(spine(bst3).height() == 1);
    std::cout << " OK.\n";
    std::cout << "3. spine(bst3).value() == 0";
    assert(spine(bst3).value() == 0);
    std::cout << " OK.\n";
    std::cout << "3. bst3.empty() == false";
    assert(!bst3.empty());
    std::cout << " OK.\n";
    std::cout << "3. bst3.find(0).size() == 1";
    assert(bst3.find(0).size() == 1);
    std::cout << " OK.\n";
    std::cout << "3. bst3.find(0).height() == 1";
    assert(bst3.find(0).height() == 1);
    std::cout << " OK.\n";
    std::cout << "3. bst3.find(0).value() == 0";
    assert(bst3.find(0).value() == 0);
    std::cout << " OK.\n";
    std::cout << "3. bst3.min() == 0";
    assert(bst3.min() == 0);
    std::cout << " OK.\n";
    std::cout << "3. bst3.max() == 0";
    assert(bst3.max() == 0);
    std::cout << " OK.\n";
    std::cout << "3. bst3.left().size() == 0";
    assert(bst3.left().size() == 0);
    std::cout << " OK.\n";
    std::cout << "3. bst3.left().height() == 0";
    assert(bst3.left().height() == 0);
    std::cout << " OK.\n";
    std::cout << "3. bst3.right().size() == 0";
    assert(bst3.right().size() == 0);
    std::cout << " OK.\n";
    std::cout << "3. bst3.right().height() == 0";
    assert(bst3.right().height() == 0);
    std::cout << " OK.\n";
    std::cout << "3. bst3.right().empty() == true";
    assert(bst3.right().empty());
    std::cout << " OK.\n";
    std::cout << "3. bst3.left().empty() == true";
    assert(bst3.left().empty());
    std::cout << " OK.\n";

    std::cout << "3. bst3.fold(1, sum) == 1";
    assert(bst3.fold(1, sum) == 1);
    std::cout << " OK.\n";

    try {
        std::cout << "3. bst3.min() will not throw.";
        bst3.min();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {

        BST<int> bst3 = bst + 0;
        std::cout << "3. bst3.max() will not throw.";
        bst3.min();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "3. bst3.left() will not throw.";
        bst3.left();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "3. bst3.right() will not throw.";
        bst3.right();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "3. bst3.value() will not throw.";
        bst3.value();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    std::cout << std::endl << "4. TESTING ONE ELEMENT TREE. CONSTRUCTED BY ITER" << std::endl << std::endl;

    std::vector<int> vec = {0};
    BST<int> bst4(vec.begin(), vec.end());

    std::cout << "4. bst4.size() == 1";
    assert(bst4.size() == 1);
    std::cout << " OK.\n";
    std::cout << "4. bst4.height == 1";
    assert(bst4.height() == 1);
    std::cout << " OK.\n";
    std::cout << "4. spine(bst4).size() == 1";
    assert(spine(bst4).size() == 1);
    std::cout << " OK.\n";
    std::cout << "4. spine(bst4).height() == 1";
    assert(spine(bst4).height() == 1);
    std::cout << " OK.\n";
    std::cout << "4. spine(bst4).value() == 0";
    assert(spine(bst4).value() == 0);
    std::cout << " OK.\n";
    std::cout << "4. bst4.empty() == false";
    assert(!bst4.empty());
    std::cout << " OK.\n";
    std::cout << "4. bst4.find(0).size() == 1";
    assert(bst4.find(0).size() == 1);
    std::cout << " OK.\n";
    std::cout << "4. bst4.find(0).height() == 1";
    assert(bst4.find(0).height() == 1);
    std::cout << " OK.\n";
    std::cout << "4. bst4.find(0).value() == 0";
    assert(bst4.find(0).value() == 0);
    std::cout << " OK.\n";
    std::cout << "4. bst4.min() == 0";
    assert(bst4.min() == 0);
    std::cout << " OK.\n";
    std::cout << "4. bst4.max() == 0";
    assert(bst4.max() == 0);
    std::cout << " OK.\n";
    std::cout << "4. bst4.left().size() == 0";
    assert(bst4.left().size() == 0);
    std::cout << " OK.\n";
    std::cout << "4. bst4.left().height() == 0";
    assert(bst4.left().height() == 0);
    std::cout << " OK.\n";
    std::cout << "4. bst4.right().size() == 0";
    assert(bst4.right().size() == 0);
    std::cout << " OK.\n";
    std::cout << "4. bst4.right().height() == 0";
    assert(bst4.right().height() == 0);
    std::cout << " OK.\n";
    std::cout << "4. bst4.right().empty() == true";
    assert(bst4.right().empty());
    std::cout << " OK.\n";
    std::cout << "4. bst4.left().empty() == true";
    assert(bst4.left().empty());
    std::cout << " OK.\n";

    std::cout << "4. bst4.fold(1, sum) == 1";
    assert(bst4.fold(1, sum) == 1);
    std::cout << " OK.\n";

    try {
        std::cout << "4. bst4.min() will not throw.";
        bst4.min();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {

        BST<int> bst4 = bst + 0;
        std::cout << "4. bst4.max() will not throw.";
        bst4.min();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "4. bst4.left() will not throw.";
        bst4.left();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "4. bst4.right() will not throw.";
        bst4.right();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "4. bst4.value() will not throw.";
        bst4.value();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    std::cout << std::endl << "5. TESTING TWO ELEMENTS TREE. CONSTRUCTED BY + 0 + 1" << std::endl << std::endl;

    BST<int> bst5(BST<int>() + 0 + 1);

    std::cout << "5. bst5.size() == 2";
    assert(bst5.size() == 2);
    std::cout << " OK.\n";
    std::cout << "5. bst5.height == 2";
    assert(bst5.height() == 2);
    std::cout << " OK.\n";
    std::cout << "5. spine(bst5).size() == 2";
    assert(spine(bst5).size() == 2);
    std::cout << " OK.\n";
    std::cout << "5. spine(bst5).height() == 2";
    assert(spine(bst5).height() == 2);
    std::cout << " OK.\n";
    std::cout << "5. spine(bst5).value() == 1";
    assert(spine(bst5).value() == 1);
    std::cout << " OK.\n";
    std::cout << "5. bst5.empty() == false";
    assert(!bst5.empty());
    std::cout << " OK.\n";
    std::cout << "5. bst5.find(0).size() == 2";
    assert(bst5.find(0).size() == 2);
    std::cout << " OK.\n";
    std::cout << "5. bst5.find(0).height() == 2";
    assert(bst5.find(0).height() == 2);
    std::cout << " OK.\n";
    std::cout << "5. bst5.find(0).value() == 0";
    assert(bst5.find(0).value() == 0);
    std::cout << " OK.\n";
    std::cout << "5. bst5.min() == 0";
    assert(bst5.min() == 0);
    std::cout << " OK.\n";
    std::cout << "5. bst5.max() == 1";
    assert(bst5.max() == 1);
    std::cout << " OK.\n";
    std::cout << "5. bst5.left().size() == 0";
    assert(bst5.left().size() == 0);
    std::cout << " OK.\n";
    std::cout << "5. bst5.left().height() == 0";
    assert(bst5.left().height() == 0);
    std::cout << " OK.\n";
    std::cout << "5. bst5.right().size() == 1";
    assert(bst5.right().size() == 1);
    std::cout << " OK.\n";
    std::cout << "5. bst5.right().height() == 1";
    assert(bst5.right().height() == 1);
    std::cout << " OK.\n";
    std::cout << "5. bst5.right().empty() == false";
    assert(!bst5.right().empty());
    std::cout << " OK.\n";
    std::cout << "5. bst5.left().empty() == true";
    assert(bst5.left().empty());
    std::cout << " OK.\n";

    std::cout << "5. bst5.fold(1, sum) == 2";
    assert(bst5.fold(1, sum) == 2);
    std::cout << " OK.\n";

    try {
        std::cout << "5. bst5.min() will not throw.";
        bst5.min();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {

        BST<int> bst5 = bst + 0;
        std::cout << "5. bst5.max() will not throw.";
        bst5.min();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "5. bst5.left() will not throw.";
        bst5.left();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "5. bst5.right() will not throw.";
        bst5.right();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "5. bst5.value() will not throw.";
        bst5.value();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    std::cout << std::endl << "6. TESTING TWO ELEMENTS TREE. CONSTRUCTED BY {0, 1}" << std::endl << std::endl;

    BST<int> bst6({0, 1});

    std::cout << "6. bst6.size() == 2";
    assert(bst6.size() == 2);
    std::cout << " OK.\n";
    std::cout << "6. bst6.height == 2";
    assert(bst6.height() == 2);
    std::cout << " OK.\n";
    std::cout << "6. spine(bst6).size() == 2";
    assert(spine(bst6).size() == 2);
    std::cout << " OK.\n";
    std::cout << "6. spine(bst6).height() == 2";
    assert(spine(bst6).height() == 2);
    std::cout << " OK.\n";
    std::cout << "6. spine(bst6).value() == 1";
    assert(spine(bst6).value() == 1);
    std::cout << " OK.\n";
    std::cout << "6. bst6.empty() == false";
    assert(!bst6.empty());
    std::cout << " OK.\n";
    std::cout << "6. bst6.find(0).size() == 2";
    assert(bst6.find(0).size() == 2);
    std::cout << " OK.\n";
    std::cout << "6. bst6.find(0).height() == 2";
    assert(bst6.find(0).height() == 2);
    std::cout << " OK.\n";
    std::cout << "6. bst6.find(0).value() == 0";
    assert(bst6.find(0).value() == 0);
    std::cout << " OK.\n";
    std::cout << "6. bst6.min() == 0";
    assert(bst6.min() == 0);
    std::cout << " OK.\n";
    std::cout << "6. bst6.max() == 1";
    assert(bst6.max() == 1);
    std::cout << " OK.\n";
    std::cout << "6. bst6.left().size() == 0";
    assert(bst6.left().size() == 0);
    std::cout << " OK.\n";
    std::cout << "6. bst6.left().height() == 0";
    assert(bst6.left().height() == 0);
    std::cout << " OK.\n";
    std::cout << "6. bst6.right().size() == 1";
    assert(bst6.right().size() == 1);
    std::cout << " OK.\n";
    std::cout << "6. bst6.right().height() == 1";
    assert(bst6.right().height() == 1);
    std::cout << " OK.\n";
    std::cout << "6. bst6.right().empty() == false";
    assert(!bst6.right().empty());
    std::cout << " OK.\n";
    std::cout << "6. bst6.left().empty() == true";
    assert(bst6.left().empty());
    std::cout << " OK.\n";

    std::cout << "6. bst6.fold(1, sum) == 2";
    assert(bst6.fold(1, sum) == 2);
    std::cout << " OK.\n";

    try {
        std::cout << "6. bst6.min() will not throw.";
        bst6.min();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {

        BST<int> bst6 = bst + 0;
        std::cout << "6. bst6.max() will not throw.";
        bst6.min();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "6. bst6.left() will not throw.";
        bst6.left();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "6. bst6.right() will not throw.";
        bst6.right();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "6. bst6.value() will not throw.";
        bst6.value();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    std::cout << std::endl << "7. TESTING TWO ELEMENTS TREE. CONSTRUCTED BY ITER" << std::endl << std::endl;

    std::vector<int> vec2 = {0, 1};
    BST<int> bst7(vec2.begin(), vec2.end());

    std::cout << "7. bst7.size() == 2";
    assert(bst7.size() == 2);
    std::cout << " OK.\n";
    std::cout << "7. bst7.height == 2";
    assert(bst7.height() == 2);
    std::cout << " OK.\n";
    std::cout << "7. spine(bst7).size() == 2";
    assert(spine(bst7).size() == 2);
    std::cout << " OK.\n";
    std::cout << "7. spine(bst7).height() == 2";
    assert(spine(bst7).height() == 2);
    std::cout << " OK.\n";
    std::cout << "7. spine(bst7).value() == 1";
    assert(spine(bst7).value() == 1);
    std::cout << " OK.\n";
    std::cout << "7. bst7.empty() == false";
    assert(!bst7.empty());
    std::cout << " OK.\n";
    std::cout << "7. bst7.find(0).size() == 2";
    assert(bst7.find(0).size() == 2);
    std::cout << " OK.\n";
    std::cout << "7. bst7.find(0).height() == 2";
    assert(bst7.find(0).height() == 2);
    std::cout << " OK.\n";
    std::cout << "7. bst7.find(0).value() == 0";
    assert(bst7.find(0).value() == 0);
    std::cout << " OK.\n";
    std::cout << "7. bst7.min() == 0";
    assert(bst7.min() == 0);
    std::cout << " OK.\n";
    std::cout << "7. bst7.max() == 1";
    assert(bst7.max() == 1);
    std::cout << " OK.\n";
    std::cout << "7. bst7.left().size() == 0";
    assert(bst7.left().size() == 0);
    std::cout << " OK.\n";
    std::cout << "7. bst7.left().height() == 0";
    assert(bst7.left().height() == 0);
    std::cout << " OK.\n";
    std::cout << "7. bst7.right().size() == 1";
    assert(bst7.right().size() == 1);
    std::cout << " OK.\n";
    std::cout << "7. bst7.right().height() == 1";
    assert(bst7.right().height() == 1);
    std::cout << " OK.\n";
    std::cout << "7. bst7.right().empty() == false";
    assert(!bst7.right().empty());
    std::cout << " OK.\n";
    std::cout << "7. bst7.left().empty() == true";
    assert(bst7.left().empty());
    std::cout << " OK.\n";

    std::cout << "7. bst7.fold(1, sum) == 2";
    assert(bst7.fold(1, sum) == 2);
    std::cout << " OK.\n";

    try {
        std::cout << "7. bst7.min() will not throw.";
        bst7.min();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {

        BST<int> bst7 = bst + 0;
        std::cout << "7. bst7.max() will not throw.";
        bst7.min();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "7. bst7.left() will not throw.";
        bst7.left();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "7. bst7.right() will not throw.";
        bst7.right();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "7. bst7.value() will not throw.";
        bst7.value();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    std::cout << std::endl << "8. TESTING THREE ELEMENTS TREE. CONSTRUCTED BY + 0 + 1 + -1" << std::endl << std::endl;

    BST<int> bst8(BST<int>() + 0 + 1 + -1);

    std::cout << "8. bst8.size() == 3";
    assert(bst8.size() == 3);
    std::cout << " OK.\n";
    std::cout << "8. bst8.height == 2";
    assert(bst8.height() == 2);
    std::cout << " OK.\n";
    std::cout << "8. spine(bst8).size() == 3";
    assert(spine(bst8).size() == 3);
    std::cout << " OK.\n";
    std::cout << "8. spine(bst8).height() == 3";
    assert(spine(bst8).height() == 3);
    std::cout << " OK.\n";
    std::cout << "8. spine(bst8).value() == 1";
    assert(spine(bst8).value() == 1);
    std::cout << " OK.\n";
    std::cout << "8. bst8.empty() == false";
    assert(!bst8.empty());
    std::cout << " OK.\n";
    std::cout << "8. bst8.find(0).size() == 3";
    assert(bst8.find(0).size() == 3);
    std::cout << " OK.\n";
    std::cout << "8. bst8.find(0).height() == 2";
    assert(bst8.find(0).height() == 2);
    std::cout << " OK.\n";
    std::cout << "8. bst8.find(0).value() == 0";
    assert(bst8.find(0).value() == 0);
    std::cout << " OK.\n";
    std::cout << "8. bst8.min() == -1";
    assert(bst8.min() == -1);
    std::cout << " OK.\n";
    std::cout << "8. bst8.max() == 1";
    assert(bst8.max() == 1);
    std::cout << " OK.\n";
    std::cout << "8. bst8.left().size() == 1";
    assert(bst8.left().size() == 1);
    std::cout << " OK.\n";
    std::cout << "8. bst8.left().height() == 1";
    assert(bst8.left().height() == 1);
    std::cout << " OK.\n";
    std::cout << "8. bst8.right().size() == 1";
    assert(bst8.right().size() == 1);
    std::cout << " OK.\n";
    std::cout << "8. bst8.right().height() == 1";
    assert(bst8.right().height() == 1);
    std::cout << " OK.\n";
    std::cout << "8. bst8.right().empty() == false";
    assert(!bst8.right().empty());
    std::cout << " OK.\n";
    std::cout << "8. bst8.left().empty() == empty";
    assert(!bst8.left().empty());
    std::cout << " OK.\n";

    std::cout << "8. bst8.fold(1, sum) == 1";
    assert(bst8.fold(1, sum) == 1);
    std::cout << " OK.\n";

    try {
        std::cout << "8. bst8.min() will not throw.";
        bst8.min();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {

        BST<int> bst8 = bst + 0;
        std::cout << "8. bst8.max() will not throw.";
        bst8.min();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "8. bst8.left() will not throw.";
        bst8.left();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "8. bst8.right() will not throw.";
        bst8.right();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    try {
        std::cout << "8. bst8.value() will not throw.";
        bst8.value();
        std::cout << " OK\n";
    } catch (...) {
        assert(0);
    }

    std::cout << std::endl  << "9. TESTING MAX_DIFF." << std::endl << std::endl;

    std::cout << "9. max_diff(BST<int>({1, 1, 1, 1, 1});";
    assert(max_diff(BST<int>({1, 1, 1, 1, 1})) == 0);
    std::cout << " OK" << std::endl;
    std::cout << "9. max_diff(BST<int>({1, 2});";
    assert(max_diff(BST<int>({1, 2})) == 1);
    std::cout << " OK" << std::endl;
    std::cout << "9. max_diff(BST<int>({1, 2, 3, 4, 5, 6});";
    assert(max_diff(BST<int>({1, 2, 3, 4, 5, 6})) == 1);
    std::cout << " OK" << std::endl;
    std::cout << "9. max_diff(BST<int>({0, 2, -2, 1, -1, 3, -3});";
    assert(max_diff(BST<int>({0, 2, -2, 1, -1, 3, -3})) == 1);
    std::cout << " OK" << std::endl;

    try {
        std::cout << "9. max_diff(BST<int>() will throw";
        max_diff(BST<int>());
        assert(0);
    } catch (...) {
        std::cout << " OK.\n";
    }

    try {
        std::cout << "9. max_diff(BST<int>({1}) will throw";
        max_diff(BST<int>({1}));
        assert(0);
    } catch (...) {
        std::cout << " OK.\n";
    }

    std::cout << std::endl << "10. TESTING TREES WITH 1000 NODES." << std::endl << std::endl;

    std::vector<int> vec4;

    int sign = 1;
    for (int i = 0; i < 1000; ++i) {
        sign *= -1;
        vec4.push_back(i * sign);
    }

    time_t start, end;

    time(&start);

    BST<int>(vec4.begin(), vec4.end());

    time(&end);

    std::cout << "10. Building of tree with 1000 nodes took " << end - start << " seconds.\n";

    std::cout << std::endl << "11. TESTING TREES WITH 10000 NODES." << std::endl << std::endl;

    vec4 = std::vector<int>();

    for (int i = 0; i < 10000; ++i) {
        sign *= -1;
        vec4.push_back(i * sign);
    }

    time(&start);

    BST<int>(vec4.begin(), vec4.end());

    time(&end);

    std::cout << "11. Building of tree with 10000 nodes took " << end - start << " seconds.\n";
#define TEST_COMPLEXITY
#ifdef TEST_COMPLEXITY

    std::cout << std::endl << "COMPLEXITY TEST" << std::endl << std::endl;

  srand(time(NULL));

  for (int size = 10; size <= 30; ++size) {

    std::vector<int> temp;

    std::cout << "Testing vector creation." << endl;
    for (int i = 0; i < size * 10000; ++i) {
      temp.push_back(rand());
    }
    std::cout << " Done. " << endl;

    time(&start);

    BST<int> bst_complex(temp.begin(), temp.end());

    time(&end);

    std::cout << "Building of tree with " << size * 10000 << " nodes and " << bst_complex.height() << " height took " << end - start << " seconds.\n";
  }

#endif


}
