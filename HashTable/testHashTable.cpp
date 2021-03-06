/* 
   testLinkedList.cpp
   Unit tests for the container HashMap

   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project */
/*****************************************************************************/
/*                                 Blurb                                     */
/*****************************************************************************/
/* To compile the test program, use the Makefile in this directory and run: 
        ./testHashMap
   This tests all the functionality of the class LinkedList, including all the 
   corner cases I could think of. Testing is done using assertion, so all tests
   are passed if the program correctly terminates (they all passed).         
   Due to the fact that I wanted to make the function clear() private, the 
   tests for clear() are commented out so the test would compile. But they all
   passed during testing stage.                                              */
#include <iostream>
#include <sstream>
#include <cassert>
#include "HashTable.h"
#include "../Coord/Coord.h"
#include "../Set/Set.h"

/* Tests inserting elements and using subscript operator. Also checks that
   exceptions are correctly thrown when querying for keys that don't exist */
void testGetterSetter() {
    std::cout << "Testing getter and setter...";
    HashTable<std::string, int> ht;
    ht.insert("key1", 1);
    ht.insert("key2", 2);
    int val1 = ht["key1"];
    int val2 = ht["key2"];
    assert(val1 == 1);
    assert(val2 == 2);
    bool caughtException = false;
    try {
        int val3 = ht["key3"];
        (void) val3;
    } catch (std::logic_error) {
        caughtException = true;
    }
    assert(caughtException);
    std::cout << "test passed.\n";
}
/* Tests that key after removal doesn't exist anymore */
void testRemove() {
    std::cout << "Testing remove...";
    HashTable<std::string, int> ht;
    ht.insert("key", 1);
    ht.remove("key");
    bool caughtException = false;
    try {
        int val = ht["key"];
        (void) val;
    } catch (std::logic_error) {
        caughtException = true;
    }
    assert(caughtException);
    std::cout << "test passed.\n";

}

void testIterator1() {
    std::cout << "Testing iterator...";
    HashTable<std::string, int> ht;
    ht.insert("key1", 1);
    ht.insert("key2", 2);
    ht.insert("key3", 3);
    for (HashTable<std::string, int>::iterator k = ht.begin(); 
         k != ht.end(); ++k) {
        assert(k.value() == ht[k.key()]);
    } 
    
}
void testIterator2() {
    HashTable<Coord, int> ht;
    Coord c1(1, 2);
    Coord c2(2, 3);
    Coord c3(3, 4);
    ht.insert(c1, 10);
    ht.insert(c2, 20);
    ht.insert(c3, 30);
    for (HashTable<Coord, int>::iterator k = ht.begin(); 
         k != ht.end(); ++k) {
        assert(k.value() == ht[k.key()]);
    }
    
}

void testIterator3() {
    
    HashTable<Coord, Set<int>> ht;
    Coord c(1, 2);
    ht.insert(c, Set<int>());
    for (int i = 0; i < 5; i++) {
        ht[c].add(i);
    }
    
    for (HashTable<Coord, Set<int>>::iterator k = ht.begin(); 
         k != ht.end(); ++k) {
        std::stringstream buffer;
        buffer << k.value();
        assert(buffer.str() == "[0, 1, 2, 3, 4]");
        assert(k.key() == c);
    }  
    std::cout << "test passed.\n";
}
/* Tests using a custom defined object as keys */
void testType1() {
    std::cout << "Testing using custom defined object...";
    HashTable<Coord, int> ht;
    Coord c1(1, 2);
    Coord c2(2, 3);
    Coord c3(3, 4);
    ht.insert(c1, 10);
    ht.insert(c2, 20);
    int val1 = ht[c1];
    int val2 = ht[c2];
    assert(val1 == 10);
    assert(val2 == 20);

}
/* Tests using a custom defined object as value */
void testType2() {
    HashTable<int, Coord> ht;
    Coord c1(1, 2);
    Coord c2(2, 3);
    ht.insert(10, c1);
    ht.insert(20, c2);
    Coord val1 = ht[10];
    Coord val2 = ht[20];
    assert(val1 == c1);
    assert(val2 == c2);
    std::cout << "test passed.\n";
}
/* Tests constructor and copy constructor */
void testConstructor1() {
    std::cout << "Testing constructor and copy constructor...";
    HashTable<Coord, int> ht1;
    size_t size = 200;
    HashTable<std::string, int> ht2(size);
}
void testConstructor2() {
    HashTable<std::string, int> ht1;
    ht1.insert("key1", 10);
    ht1.insert("key2", 20);
    HashTable<std::string, int> ht2(ht1);
    assert(ht2["key1"] == ht1["key1"]);
    assert(ht2["key2"] == ht1["key2"]);
    ht1.insert("key1", 30);
    assert(ht2["key1"] == 10);
    std::cout << "test passed.\n";
}

/*
void testClear1() {
    std::cout << "Testing function clear...";
    HashTable<std::string, int> ht;
    ht.insert("key1", 10);
    ht.insert("key2", 20);
    ht.clear();
    bool caughtException1 = false;
    try {
        int val = ht["key1"];
        (void) val;
    } catch (std::logic_error) {
        caughtException1 = true;
    }
    assert(caughtException1);
    bool caughtException2 = false;
    try {
        int val = ht["key2"];
        (void) val;
    } catch (std::logic_error) {
        caughtException2 = true;
    }
    assert(caughtException2);
    HashTable<std::string, int>::iterator it = ht.begin();
    assert(it == ht.end());
   
}
void testClear2() {
    HashTable<Coord, Set<int>> ht;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            Coord c(i, j);
            ht.insert(c, Set<int>());
            for (int k = 0; k < 5; k++) {
                ht[c].add(k);
            }
        }
    }
    ht.clear();
    std::cout << "test passed.\n";
}
*/
/* Tests using assignment operator on primitive types */
void testAssignmentOperator1() {
    std::cout << "Testing assignment operator...";
    HashTable<std::string, int> ht1;
    ht1.insert("key1", 10);
    ht1.insert("key2", 20);
    HashTable<std::string, int> ht2;
    ht2.insert("key1", 30);
    ht2.insert("key2", 40);
    ht2 = ht1;
    assert(ht2["key1"] == 10);
    assert(ht2["key2"] == 20);
    
}
/* Tests using assignment operator on custom defined objects */
void testAssignmentOperator2() {
    HashTable<Coord, Set<int>> ht1;
    HashTable<Coord, Set<int>> ht2;
    Coord c1(1, 2);
    ht1.insert(c1, Set<int>());
    ht2.insert(c1, Set<int>());
    for (int i = 0; i < 10; i++) {
        ht1[c1].add(i);
        ht2[c1].add(i);
    }
    Coord c2(3, 4);
    ht1.insert(c2, Set<int>());
    for (int i = 100; i < 106; i++) {
        ht1[c2].add(i);
    }
    ht2 = ht1;
    std::stringstream buffer;
    buffer << ht2[c2];
    assert(buffer.str() == "[100, 101, 102, 103, 104, 105]");
    std::cout << "...test passed\n";
}
void testResize() {
    std::cout << "Testing resize function...";
    HashTable<int, std::string> ht1(40);
    for (int i = 0; i < 70; i++) {
        ht1.insert(i, "value");
    }
    std::cout << "...test passed\n";
}
int main() {
    std::cout << "============ Running tests for Hash Table ============\n";
    testConstructor1();
    testConstructor2();
    testGetterSetter();
    testRemove();
    testType1();
    testType2();
    testIterator1();
    testIterator2();
    testIterator3();
    //testClear1();
    //testClear2();
    testAssignmentOperator1();
    testAssignmentOperator2();
    testResize();

    std::cout << "============ Tests for HashTable completed! ============\n";
}







