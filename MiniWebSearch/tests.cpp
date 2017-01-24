//  Casey Hittinger
//  tests.cpp
//  MiniWebSearch
//
//  Created by Casey on 10/24/16.
//  Tests for AVLTree

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "AVLTree.h"

TEST_CASE("AVLTree class", "[AVLTree]")
{
    // Creating three different templates for AVLTree and adding a certain amount of elements
    
    AVLTree<int> num1;
    num1.insert(1);
    
    AVLTree<std::string> string1;
    string1.insert("joe");
    string1.insert("billy");
    
    AVLTree<char> letter;
    letter.insert('d');
    letter.insert('e');
    letter.insert('h');
    
    // tests to see if the added elements are accounted for
    SECTION("Get Number of Elements")
    {
        REQUIRE(num1.getNumElements() == 1);
        REQUIRE(string1.getNumElements() == 2);
        REQUIRE(letter.getNumElements() == 3);
    }
    
    // inserts elements and sees if the post order operation is in the correct order
    SECTION("INSERT AND CHECK OUTPUT")
    {
        num1.insert(3);
        num1.insert(4);
        REQUIRE(num1.getNumElements() == 3);
        // check to see if the output is correct
        //num1.postOrder();
        //std::cout << "\n" << std::endl;
        
        string1.insert("casey");
        string1.insert("ashley");
        string1.insert("supercalifragolistic");
        REQUIRE(string1.getNumElements() == 5);
        // test to see if output is the way its suppose to be
        //string1.postOrder();
        
        
        letter.insert('a');
        letter.insert('b');
        REQUIRE(letter.getNumElements() == 5);
        //std::cout << "\n" << std::endl;
        //test to see if postOrder worked
        //letter.postOrder();
    }
    
}
