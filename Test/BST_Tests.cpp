#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include "../BST.h"

using Dict = BST;
using KeyType = Dict::KeyType;
using ItemType = Dict::ItemType;

void isPresent(Dict & dict, KeyType k, ItemType i)
{
    ItemType* p_i = dict.lookup(k);
    BOOST_CHECK_MESSAGE(p_i, std::to_string(k) + " is missing");
    if (p_i)
    {
        BOOST_CHECK_MESSAGE(*p_i == i,
                            std::to_string(k) + " should be " + i + ", but found " + *p_i);
    }
}

void isAbsent(Dict & dict, KeyType k)
{
    BOOST_CHECK_MESSAGE(dict.lookup(k) == nullptr,
                        std::to_string(k) + " should be absent, but is present.");
}

void insertTestData(Dict & dict)
{
    dict.insert(22,"Jane");
    dict.insert(22,"Mary");
    dict.insert(0,"Harold");
    dict.insert(9,"Edward");
    dict.insert(37,"Victoria");
    dict.insert(4,"Matilda");
    dict.insert(26,"Oliver");
    dict.insert(42,"Elizabeth");
    dict.insert(19,"Henry");
    dict.insert(4,"Stephen");
    dict.insert(24,"James");
    dict.insert(-1,"Edward");
    dict.insert(31,"Anne");
    dict.insert(23,"Elizabeth");
    dict.insert(1,"William");
    dict.insert(26,"Charles");
}

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( Constructor_Tests )

    BOOST_AUTO_TEST_CASE( ConstructEmpty )
    {
        new Dict();
        // Use of 'new' is to avoid triggering the destructor in this test.
    }

    BOOST_AUTO_TEST_CASE( DestroyEmpty )
    {
        Dict dict;
    }

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( Lookup_Insert_Tests )

    BOOST_AUTO_TEST_CASE( EmptyLookup )
    {
        Dict dict;
        isAbsent(dict,1);
    }

    BOOST_AUTO_TEST_CASE( SingleInsert )
    {
        Dict dict;
        dict.insert(22,"Mary");
    }

    BOOST_AUTO_TEST_CASE( SingleInsertLookup )
    {
        Dict dict;
        dict.insert(22,"Mary");
        isPresent(dict,22,"Mary");
    }

    BOOST_AUTO_TEST_CASE( SingleOverwriteLookup )
    {
        Dict dict;
        dict.insert(22,"Jane");
        dict.insert(22,"Mary");
        isPresent(dict,22,"Mary");
    }

    BOOST_AUTO_TEST_CASE( MultipleInsert )
    {
        Dict dict;
        insertTestData(dict);
    }

    BOOST_AUTO_TEST_CASE( MultipleInsertLookupPresent )
    {
        Dict dict;
        insertTestData(dict);

        isPresent(dict,22,"Mary");
        isPresent(dict,4,"Stephen");
        isPresent(dict,9,"Edward");
        isPresent(dict,1,"William");
        isPresent(dict,0,"Harold");
        isPresent(dict,24,"James");
        isPresent(dict,26,"Charles");
        isPresent(dict,19,"Henry");
        isPresent(dict,31,"Anne");
        isPresent(dict,23,"Elizabeth");
        isPresent(dict,37,"Victoria");
        isPresent(dict,42,"Elizabeth");
        isPresent(dict,-1,"Edward");
    }

    BOOST_AUTO_TEST_CASE( MultipleInsertLookupAbsent )
    {
        Dict dict;
        insertTestData(dict);

        isAbsent(dict,2);
        isAbsent(dict,3);
        isAbsent(dict,-4);
        isAbsent(dict,56);
        isAbsent(dict,30);
    }

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( Remove_Tests )

    BOOST_AUTO_TEST_CASE( EmptyRemove )
    {
        Dict dict;
        dict.remove(43);
        isAbsent(dict,43);
    }

    BOOST_AUTO_TEST_CASE( RemoveChildlessRoot )
    {
        Dict dict;
        dict.insert(7,"John");
        dict.remove(7);
        isAbsent(dict,7);
    }

    BOOST_AUTO_TEST_CASE( RemoveLeftChildOfRoot )
    {
        Dict dict;
        dict.insert(31,"Anne");
        dict.insert(7,"John");
        dict.remove(7);

        isAbsent(dict,7);
        isPresent(dict,31,"Anne");
    }

    BOOST_AUTO_TEST_CASE( RemoveRightChildOfRoot )
    {
        Dict dict;
        dict.insert(7,"John");
        dict.insert(31,"Anne");
        dict.remove(31);

        isAbsent(dict,31);
        isPresent(dict,7,"John");
    }

    BOOST_AUTO_TEST_CASE( InsertMany_RemoveChildlessNodes )
    {
        Dict dict;
        insertTestData(dict);

        dict.remove(-1);
        isAbsent(dict,-1);

        dict.remove(1);
        isAbsent(dict,1);

        dict.remove(19);
        isAbsent(dict,19);

        dict.remove(23);
        isAbsent(dict,23);

        dict.remove(31);
        isAbsent(dict,31);

        dict.remove(42);
        isAbsent(dict,42);

        dict.remove(4);
        isAbsent(dict,4);

        isPresent(dict,22,"Mary");
        isPresent(dict,9,"Edward");
        isPresent(dict,0,"Harold");
        isPresent(dict,24,"James");
        isPresent(dict,26,"Charles");
        isPresent(dict,37,"Victoria");
    }

    BOOST_AUTO_TEST_CASE( OverwriteThenRemove )
    {
        Dict dict;
        dict.insert(22,"Jane");
        dict.insert(22,"Mary");
        dict.insert(4,"Matilda");
        dict.insert(26,"Oliver");
        dict.insert(4,"Stephen");
        dict.insert(26,"Charles");

        dict.remove(4);
        isAbsent(dict,4);

        dict.remove(26);
        isAbsent(dict,26);

        dict.remove(22);
        isAbsent(dict,22);
    }

    BOOST_AUTO_TEST_CASE( RemoveRootWithLeftChild )
    {
        Dict dict;
        dict.insert(31,"Anne");
        dict.insert(7,"John");
        dict.remove(31);

        isAbsent(dict,31);
        isPresent(dict,7,"John");
    }

    BOOST_AUTO_TEST_CASE( RemoveRootWithRightChild )
    {
        Dict dict;
        dict.insert(7,"John");
        dict.insert(31,"Anne");
        dict.remove(31);

        isAbsent(dict,31);
        isPresent(dict,7,"John");
    }

    BOOST_AUTO_TEST_CASE( InsertMany_RemoveNodesWithOneChild )
    {
        Dict dict;
        insertTestData(dict);

        dict.remove(4);
        isAbsent(dict,4);

        dict.remove(1);
        isAbsent(dict,1);

        dict.remove(9);
        isAbsent(dict,9);

        isPresent(dict,22,"Mary");
        isPresent(dict,0,"Harold");
        isPresent(dict,24,"James");
        isPresent(dict,26,"Charles");
        isPresent(dict,19,"Henry");
        isPresent(dict,31,"Anne");
        isPresent(dict,23,"Elizabeth");
        isPresent(dict,37,"Victoria");
        isPresent(dict,42,"Elizabeth");
        isPresent(dict,-1,"Edward");
    }

    BOOST_AUTO_TEST_CASE( RemoveRootWithChildren )
    {
        Dict dict;
        dict.insert(31,"Anne");
        dict.insert(7,"John");
        dict.insert(42,"Elizabeth");
        dict.remove(31);

        isAbsent(dict,31);
        isPresent(dict,7,"John");
        isPresent(dict,42,"Elizabeth");
    }

    BOOST_AUTO_TEST_CASE( InsertMany_RemoveNodesWithChildren )
    {
        Dict dict;
        insertTestData(dict);

        dict.remove(0);
        isAbsent(dict,0);

        dict.remove(37);
        isAbsent(dict,37);

        dict.remove(22);
        isAbsent(dict,22);

        isPresent(dict,4,"Stephen");
        isPresent(dict,9,"Edward");
        isPresent(dict,1,"William");
        isPresent(dict,24,"James");
        isPresent(dict,26,"Charles");
        isPresent(dict,19,"Henry");
        isPresent(dict,31,"Anne");
        isPresent(dict,23,"Elizabeth");
        isPresent(dict,42,"Elizabeth");
        isPresent(dict,-1,"Edward");
    }

    BOOST_AUTO_TEST_CASE( InsertMany_RemoveAbsent )
    {
        Dict dict;

        insertTestData(dict);

        dict.remove(6);
        isAbsent(dict,6);

        isPresent(dict,22,"Mary");
        isPresent(dict,4,"Stephen");
        isPresent(dict,9,"Edward");
        isPresent(dict,1,"William");
        isPresent(dict,0,"Harold");
        isPresent(dict,24,"James");
        isPresent(dict,26,"Charles");
        isPresent(dict,19,"Henry");
        isPresent(dict,31,"Anne");
        isPresent(dict,23,"Elizabeth");
        isPresent(dict,37,"Victoria");
        isPresent(dict,42,"Elizabeth");
        isPresent(dict,-1,"Edward");
    }

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( RemoveIf_Tests )

    BOOST_AUTO_TEST_CASE( RemoveNone )
    {
        Dict dict;
        insertTestData(dict);

        dict.removeIf([](KeyType k) {return false;});

        isPresent(dict,22,"Mary");
        isPresent(dict,4,"Stephen");
        isPresent(dict,9,"Edward");
        isPresent(dict,1,"William");
        isPresent(dict,0,"Harold");
        isPresent(dict,24,"James");
        isPresent(dict,26,"Charles");
        isPresent(dict,19,"Henry");
        isPresent(dict,31,"Anne");
        isPresent(dict,23,"Elizabeth");
        isPresent(dict,37,"Victoria");
        isPresent(dict,42,"Elizabeth");
        isPresent(dict,-1,"Edward");
    }

    BOOST_AUTO_TEST_CASE( RemoveAll )
    {
        Dict dict;
        insertTestData(dict);

        dict.removeIf([](KeyType k) {return true;});

        isAbsent(dict,22);
        isAbsent(dict,4);
        isAbsent(dict,9);
        isAbsent(dict,1);
        isAbsent(dict,0);
        isAbsent(dict,24);
        isAbsent(dict,26);
        isAbsent(dict,19);
        isAbsent(dict,31);
        isAbsent(dict,23);
        isAbsent(dict,37);
        isAbsent(dict,42);
        isAbsent(dict,-1);
    }

    BOOST_AUTO_TEST_CASE( RemoveOddKeys )
    {
        Dict dict;
        insertTestData(dict);

        dict.removeIf([](KeyType k) {return k%2 != 0;});

        isPresent(dict,22,"Mary");
        isPresent(dict,4,"Stephen");
        isPresent(dict,0,"Harold");
        isPresent(dict,24,"James");
        isPresent(dict,26,"Charles");
        isPresent(dict,42,"Elizabeth");

        isAbsent(dict,9);
        isAbsent(dict,1);
        isAbsent(dict,19);
        isAbsent(dict,31);
        isAbsent(dict,23);
        isAbsent(dict,37);
        isAbsent(dict,-1);
    }

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( Copy_Constructor_Tests )

    BOOST_AUTO_TEST_CASE( CopyConstructorFullyCopies )
    {
        Dict dict1;
        insertTestData(dict1);

        Dict dict2(dict1);

        isPresent(dict2,22,"Mary");
        isPresent(dict2,4,"Stephen");
        isPresent(dict2,9,"Edward");
        isPresent(dict2,1,"William");
        isPresent(dict2,0,"Harold");
        isPresent(dict2,24,"James");
        isPresent(dict2,26,"Charles");
        isPresent(dict2,19,"Henry");
        isPresent(dict2,31,"Anne");
        isPresent(dict2,23,"Elizabeth");
        isPresent(dict2,37,"Victoria");
        isPresent(dict2,42,"Elizabeth");
        isPresent(dict2,-1,"Edward");
    }

    BOOST_AUTO_TEST_CASE( CopyConstructorDoesNotDeleteSource )
    {
        Dict dict1;
        insertTestData(dict1);

        Dict dict2(dict1);

        isPresent(dict1,22,"Mary");
        isPresent(dict1,4,"Stephen");
        isPresent(dict1,9,"Edward");
        isPresent(dict1,1,"William");
        isPresent(dict1,0,"Harold");
        isPresent(dict1,24,"James");
        isPresent(dict1,26,"Charles");
        isPresent(dict1,19,"Henry");
        isPresent(dict1,31,"Anne");
        isPresent(dict1,23,"Elizabeth");
        isPresent(dict1,37,"Victoria");
        isPresent(dict1,42,"Elizabeth");
        isPresent(dict1,-1,"Edward");
    }

    BOOST_AUTO_TEST_CASE( CopyConstructorIsDeep )
    {
        Dict dict1;
        insertTestData(dict1);

        Dict dict2(dict1);

        dict1.insert(2,"William");
        isPresent(dict1,2,"William");
        isAbsent(dict2,2);

        dict2.insert(3,"Henry");
        isPresent(dict2,3,"Henry");
        isAbsent(dict1,3);

        dict1.remove(24);
        isAbsent(dict1,24);
        isPresent(dict2,24,"James");

        dict2.remove(26);
        isAbsent(dict2,26);
        isPresent(dict1,26,"Charles");
    }

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( Copy_Assignment_Tests )

    BOOST_AUTO_TEST_CASE( CopyAssignmentFullyCopies )
    {
        Dict dict1;
        insertTestData(dict1);

        Dict dict2;
        dict2 = dict1;

        isPresent(dict2,22,"Mary");
        isPresent(dict2,4,"Stephen");
        isPresent(dict2,9,"Edward");
        isPresent(dict2,1,"William");
        isPresent(dict2,0,"Harold");
        isPresent(dict2,24,"James");
        isPresent(dict2,26,"Charles");
        isPresent(dict2,19,"Henry");
        isPresent(dict2,31,"Anne");
        isPresent(dict2,23,"Elizabeth");
        isPresent(dict2,37,"Victoria");
        isPresent(dict2,42,"Elizabeth");
        isPresent(dict2,-1,"Edward");
    }

    BOOST_AUTO_TEST_CASE( CopyAssignmentOverwrites )
    {
        Dict dict1;
        insertTestData(dict1);

        Dict dict2;
        dict2.insert(22,"Jane");
        dict2.insert(2,"William");

        dict1 = dict2;

        isAbsent(dict1,4);
        isAbsent(dict1,9);
        isAbsent(dict1,1);
        isAbsent(dict1,0);
        isAbsent(dict1,24);
        isAbsent(dict1,26);
        isAbsent(dict1,19);
        isAbsent(dict1,31);
        isAbsent(dict1,23);
        isAbsent(dict1,37);
        isAbsent(dict1,42);
        isAbsent(dict1,-1);

        isPresent(dict1,2,"William");
        isPresent(dict1,22,"Jane");
    }

    BOOST_AUTO_TEST_CASE( CopyAssignmentDoesNotReverseCopy )
    {
        Dict dict1;
        insertTestData(dict1);

        Dict dict2;

        dict2.insert(22,"Jane");
        dict2.insert(2,"William");

        dict2 = dict1;

        isAbsent(dict1,2);
    }

    BOOST_AUTO_TEST_CASE( CopyAssignmentIsDeep )
    {
        Dict dict1;
        insertTestData(dict1);

        Dict dict2;
        dict2 = dict1;

        dict1.insert(2,"William");
        isPresent(dict1,2,"William");
        isAbsent(dict2,2);

        dict2.insert(3,"Henry");
        isPresent(dict2,3,"Henry");
        isAbsent(dict1,3);

        dict1.remove(24);
        isAbsent(dict1,24);
        isPresent(dict2,24,"James");

        dict2.remove(26);
        isAbsent(dict2,26);
        isPresent(dict1,26,"Charles");
    }

    BOOST_AUTO_TEST_CASE( CopySelfAssignment )
    {
        Dict dict;
        insertTestData(dict);

        dict = dict;
        isPresent(dict,24,"James");
        isPresent(dict,26,"Charles");
        isAbsent(dict,2);
    }

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( Move_Constructor_Tests )

    BOOST_AUTO_TEST_CASE( MoveConstructorFullyMoves )
    {
        Dict dict1;
        insertTestData(dict1);

        Dict dict2(std::move(dict1));

        isPresent(dict2,22,"Mary");
        isPresent(dict2,4,"Stephen");
        isPresent(dict2,9,"Edward");
        isPresent(dict2,1,"William");
        isPresent(dict2,0,"Harold");
        isPresent(dict2,24,"James");
        isPresent(dict2,26,"Charles");
        isPresent(dict2,19,"Henry");
        isPresent(dict2,31,"Anne");
        isPresent(dict2,23,"Elizabeth");
        isPresent(dict2,37,"Victoria");
        isPresent(dict2,42,"Elizabeth");
        isPresent(dict2,-1,"Edward");
    }

    BOOST_AUTO_TEST_CASE( MoveConstructorSteals )
    {
        Dict* dictPtr;
        {
            Dict dict1;
            insertTestData(dict1);

            dictPtr = new Dict(std::move(dict1));

            isAbsent(dict1,22);
            isAbsent(dict1,4);
            isAbsent(dict1,9);
            isAbsent(dict1,1);
            isAbsent(dict1,0);
            isAbsent(dict1,24);
            isAbsent(dict1,26);
            isAbsent(dict1,19);
            isAbsent(dict1,31);
            isAbsent(dict1,23);
            isAbsent(dict1,37);
            isAbsent(dict1,42);
            isAbsent(dict1,-1);

            // dict1 gets deleted here
        }

        isPresent(*dictPtr,22,"Mary");
        isPresent(*dictPtr,4,"Stephen");
        isPresent(*dictPtr,9,"Edward");
        isPresent(*dictPtr,1,"William");
        isPresent(*dictPtr,0,"Harold");
        isPresent(*dictPtr,24,"James");
        isPresent(*dictPtr,26,"Charles");
        isPresent(*dictPtr,19,"Henry");
        isPresent(*dictPtr,31,"Anne");
        isPresent(*dictPtr,23,"Elizabeth");
        isPresent(*dictPtr,37,"Victoria");
        isPresent(*dictPtr,42,"Elizabeth");
        isPresent(*dictPtr,-1,"Edward");
    }

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( Move_Assignment_Tests )

    BOOST_AUTO_TEST_CASE( MoveAssignmentFullyMoves )
    {
        Dict dict1;
        insertTestData(dict1);

        Dict dict2;
        dict2 = std::move(dict1);

        isPresent(dict2,22,"Mary");
        isPresent(dict2,4,"Stephen");
        isPresent(dict2,9,"Edward");
        isPresent(dict2,1,"William");
        isPresent(dict2,0,"Harold");
        isPresent(dict2,24,"James");
        isPresent(dict2,26,"Charles");
        isPresent(dict2,19,"Henry");
        isPresent(dict2,31,"Anne");
        isPresent(dict2,23,"Elizabeth");
        isPresent(dict2,37,"Victoria");
        isPresent(dict2,42,"Elizabeth");
        isPresent(dict2,-1,"Edward");
    }

    BOOST_AUTO_TEST_CASE( MoveAssignmentOverwrites )
    {
        Dict dict1;
        insertTestData(dict1);

        Dict dict2;
        dict2.insert(22,"Jane");
        dict2.insert(2,"William");

        dict1 = std::move(dict2);

        isAbsent(dict1,4);
        isAbsent(dict1,9);
        isAbsent(dict1,1);
        isAbsent(dict1,0);
        isAbsent(dict1,24);
        isAbsent(dict1,26);
        isAbsent(dict1,19);
        isAbsent(dict1,31);
        isAbsent(dict1,23);
        isAbsent(dict1,37);
        isAbsent(dict1,42);
        isAbsent(dict1,-1);

        isPresent(dict1,2,"William");
    }

    BOOST_AUTO_TEST_CASE( MoveAssignmentIsNotShallowCopy )
    {
        Dict dict1;
        insertTestData(dict1);

        Dict dict2;
        dict2 = std::move(dict1);

        dict1.remove(19);
        dict1.remove(23);
        isPresent(dict2,19,"Henry");
        isPresent(dict2,23,"Elizabeth");
    }

    BOOST_AUTO_TEST_CASE( MoveSelfAssignment )
    {
        Dict dict;
        insertTestData(dict);

        dict = std::move(dict);

        isPresent(dict,24,"James");
        isPresent(dict,26,"Charles");
    }

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
