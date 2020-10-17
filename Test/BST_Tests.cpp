#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include "../BST.h"

BOOST_AUTO_TEST_SUITE(TestBST)

    BOOST_AUTO_TEST_CASE(SingleInsertAndLookup)
    {
        BST* bst = new BST();
        bst->insert(0, "hello");
        BOOST_CHECK_EQUAL("hello", *bst->lookup(0));
    }

    BOOST_AUTO_TEST_CASE(MultipleInsertAndLookup)
    {
        BST* bst = new BST();
        bst->insert(0, "hello, ");
        bst->insert(1, "world");
        BOOST_CHECK_EQUAL("hello, ", *bst->lookup(0));
        BOOST_CHECK_EQUAL("world", *bst->lookup(1));
    }

    BOOST_AUTO_TEST_CASE(LookupWithEmptyTree)
    {
        BST* bst = new BST();
        BOOST_CHECK_EQUAL(nullptr, bst->lookup(1));
    }

    BOOST_AUTO_TEST_CASE(LookupNonexistentKey)
    {
        BST* bst = new BST();
        bst->insert(1, "hello");
        BOOST_CHECK_EQUAL(nullptr, bst->lookup(0));
    }

BOOST_AUTO_TEST_SUITE_END()