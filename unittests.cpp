#include "gtest/gtest.h"
#include "mfuncs.h"
#include "ffuncs.h"
#include "lfuncs.h"
#include "qfuncs.h"
#include "sfuncs.h"
#include "tfuncs.h"
#include "hfuncs.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdio>

TEST(DynamicArrayTest, ConstructorAndDestructor) {
    DynamicArray* arr = new DynamicArray(5);
    ASSERT_NE(arr, nullptr);
    EXPECT_EQ(arr->getSize(), 0);
    EXPECT_GE(arr->getCapacity(), 5);
    delete arr;
}

TEST(DynamicArrayTest, PushBack) {
    DynamicArray arr;
    arr.pushBack("A");
    arr.pushBack("B");
    arr.pushBack("C");
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr.get(0), "A");
    EXPECT_EQ(arr.get(1), "B");
    EXPECT_EQ(arr.get(2), "C");
}

TEST(DynamicArrayTest, Insert) {
    DynamicArray arr;
    arr.pushBack("A");
    arr.pushBack("C");
    arr.insert(1, "B");
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr.get(0), "A");
    EXPECT_EQ(arr.get(1), "B");
    EXPECT_EQ(arr.get(2), "C");
    
    arr.insert(0, "Start");
    EXPECT_EQ(arr.get(0), "Start");
    EXPECT_EQ(arr.getSize(), 4);
    
    arr.insert(4, "End");
    EXPECT_EQ(arr.get(4), "End");
    EXPECT_EQ(arr.getSize(), 5);
}

TEST(DynamicArrayTest, Remove) {
    DynamicArray arr;
    arr.pushBack("A");
    arr.pushBack("B");
    arr.pushBack("C");
    arr.remove(1);
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr.get(0), "A");
    EXPECT_EQ(arr.get(1), "C");
}

TEST(DynamicArrayTest, SetAndGet) {
    DynamicArray arr;
    arr.pushBack("A");
    arr.pushBack("B");
    arr.set(0, "X");
    arr.set(1, "Y");
    EXPECT_EQ(arr.get(0), "X");
    EXPECT_EQ(arr.get(1), "Y");
}

TEST(DynamicArrayTest, Find) {
    DynamicArray arr;
    arr.pushBack("A");
    arr.pushBack("B");
    arr.pushBack("C");
    EXPECT_EQ(arr.find("A"), 0);
    EXPECT_EQ(arr.find("B"), 1);
    EXPECT_EQ(arr.find("C"), 2);
    EXPECT_EQ(arr.find("D"), -1);
}

TEST(DynamicArrayTest, Clear) {
    DynamicArray arr;
    arr.pushBack("A");
    arr.pushBack("B");
    arr.pushBack("C");
    EXPECT_EQ(arr.getSize(), 3);
    arr.clear();
    EXPECT_EQ(arr.getSize(), 0);
}

TEST(DynamicArrayTest, GetCapacity) {
    DynamicArray arr(2);
    EXPECT_GE(arr.getCapacity(), 2);
    arr.pushBack("A");
    arr.pushBack("B");
    arr.pushBack("C"); 
    EXPECT_GT(arr.getCapacity(), 2);
}

TEST(DynamicArrayTest, Serialize) {
    DynamicArray arr;
    arr.pushBack("A");
    arr.pushBack("B");
    arr.pushBack("C");
    std::vector<std::string> data = arr.serialize();
    EXPECT_EQ(data.size(), 3);
    EXPECT_EQ(data[0], "A");
    EXPECT_EQ(data[1], "B");
    EXPECT_EQ(data[2], "C");
}

TEST(DynamicArrayTest, Deserialize) {
    DynamicArray arr;
    std::vector<std::string> data = {"X", "Y", "Z"};
    arr.deserialize(data);
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr.get(0), "X");
    EXPECT_EQ(arr.get(1), "Y");
    EXPECT_EQ(arr.get(2), "Z");
}

TEST(DynamicArrayTest, SerializeBinary) {
    DynamicArray arr;
    arr.pushBack("Hello");
    arr.pushBack("World");
    std::stringstream ss;
    arr.serializeBinary(ss);
    
    DynamicArray arr2;
    arr2.deserializeBinary(ss);
    EXPECT_EQ(arr2.getSize(), 2);
    EXPECT_EQ(arr2.get(0), "Hello");
    EXPECT_EQ(arr2.get(1), "World");
}

TEST(DynamicArrayTest, Print) {
    DynamicArray arr;
    arr.pushBack("A");
    arr.pushBack("B");
    arr.pushBack("C");
    
    // Redirect cout to stringstream to capture output
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    arr.print();
    
    std::cout.rdbuf(old); // Reset cout
    
    std::string output = buffer.str();
    EXPECT_NE(output.find("A"), std::string::npos);
    EXPECT_NE(output.find("B"), std::string::npos);
    EXPECT_NE(output.find("C"), std::string::npos);
}

TEST(DynamicArrayTest, EdgeCases) {
    DynamicArray arr;
    
    EXPECT_EQ(arr.getSize(), 0);
    EXPECT_EQ(arr.find("A"), -1);
    arr.clear(); 
    
    arr.pushBack("Single");
    EXPECT_EQ(arr.getSize(), 1);
    EXPECT_EQ(arr.get(0), "Single");
    arr.remove(0);
    EXPECT_EQ(arr.getSize(), 0);
}

// ==================== ForwardList Tests ====================
TEST(ForwardListTest, PushFront) {
    ForwardList list;
    list.pushFront("C");
    list.pushFront("B");
    list.pushFront("A");
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list.getAt(0), "A");
    EXPECT_EQ(list.getAt(1), "B");
    EXPECT_EQ(list.getAt(2), "C");
}

TEST(ForwardListTest, PushBack) {
    ForwardList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list.getAt(0), "A");
    EXPECT_EQ(list.getAt(1), "B");
    EXPECT_EQ(list.getAt(2), "C");
}

TEST(ForwardListTest, AddAfter) {
    ForwardList list;
    list.pushBack("A");
    list.pushBack("C");
    FNode* nodeA = list.find("A");
    list.addAfter(nodeA, "B");
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list.getAt(0), "A");
    EXPECT_EQ(list.getAt(1), "B");
    EXPECT_EQ(list.getAt(2), "C");
}

TEST(ForwardListTest, DelAfter) {
    ForwardList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    FNode* nodeA = list.find("A");
    list.delAfter(nodeA);
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list.getAt(0), "A");
    EXPECT_EQ(list.getAt(1), "C");
}

TEST(ForwardListTest, AddBefore) {
    ForwardList list;
    list.pushBack("A");
    list.pushBack("C");
    FNode* nodeC = list.find("C");
    list.addBefore(nodeC, "B");
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list.getAt(0), "A");
    EXPECT_EQ(list.getAt(1), "B");
    EXPECT_EQ(list.getAt(2), "C");
}

TEST(ForwardListTest, DelBefore) {
    ForwardList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    FNode* nodeC = list.find("C");
    list.delBefore(nodeC);
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list.getAt(0), "A");
    EXPECT_EQ(list.getAt(1), "C");
}

TEST(ForwardListTest, PopFront) {
    ForwardList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    list.popFront();
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list.getAt(0), "B");
    EXPECT_EQ(list.getAt(1), "C");
}

TEST(ForwardListTest, DelByKey) {
    ForwardList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    list.delByKey("B");
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list.getAt(0), "A");
    EXPECT_EQ(list.getAt(1), "C");
}

TEST(ForwardListTest, Find) {
    ForwardList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    FNode* nodeB = list.find("B");
    ASSERT_NE(nodeB, nullptr);
    EXPECT_EQ(nodeB->key, "B");
    EXPECT_EQ(list.find("X"), nullptr);
}

TEST(ForwardListTest, GetAt) {
    ForwardList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    EXPECT_EQ(list.getAt(0), "A");
    EXPECT_EQ(list.getAt(1), "B");
    EXPECT_EQ(list.getAt(2), "C");
    EXPECT_EQ(list.getAt(3), "");
}

TEST(ForwardListTest, GetSize) {
    ForwardList list;
    EXPECT_EQ(list.getSize(), 0);
    list.pushBack("A");
    EXPECT_EQ(list.getSize(), 1);
    list.pushBack("B");
    EXPECT_EQ(list.getSize(), 2);
}

TEST(ForwardListTest, Clear) {
    ForwardList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    EXPECT_EQ(list.getSize(), 3);
    list.clear();
    EXPECT_EQ(list.getSize(), 0);
}

TEST(ForwardListTest, GetHead) {
    ForwardList list;
    EXPECT_EQ(list.getHead(), nullptr);
    
    list.pushBack("A");
    ASSERT_NE(list.getHead(), nullptr);
    EXPECT_EQ(list.getHead()->key, "A");
    
    list.pushBack("B");
    EXPECT_EQ(list.getHead()->key, "A");
}

TEST(ForwardListTest, Serialize) {
    ForwardList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    std::vector<std::string> data = list.serialize();
    EXPECT_EQ(data.size(), 3);
    EXPECT_EQ(data[0], "A");
    EXPECT_EQ(data[1], "B");
    EXPECT_EQ(data[2], "C");
}

TEST(ForwardListTest, Deserialize) {
    ForwardList list;
    std::vector<std::string> data = {"X", "Y", "Z"};
    list.deserialize(data);
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list.getAt(0), "X");
    EXPECT_EQ(list.getAt(1), "Y");
    EXPECT_EQ(list.getAt(2), "Z");
}

TEST(ForwardListTest, SerializeBinary) {
    ForwardList list;
    list.pushBack("Hello");
    list.pushBack("World");
    std::stringstream ss;
    list.serializeBinary(ss);
    
    ForwardList list2;
    list2.deserializeBinary(ss);
    EXPECT_EQ(list2.getSize(), 2);
    EXPECT_EQ(list2.getAt(0), "Hello");
    EXPECT_EQ(list2.getAt(1), "World");
}

TEST(ForwardListTest, Print) {
    ForwardList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    list.print();
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    EXPECT_NE(output.find("A"), std::string::npos);
    EXPECT_NE(output.find("B"), std::string::npos);
    EXPECT_NE(output.find("C"), std::string::npos);
    EXPECT_NE(output.find("->"), std::string::npos);
}

// ==================== DoublyLinkedList Tests ====================
TEST(DoublyLinkedListTest, PushFront) {
    DoublyLinkedList list;
    list.pushFront("C");
    list.pushFront("B");
    list.pushFront("A");
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list.getAt(0), "A");
    EXPECT_EQ(list.getAt(1), "B");
    EXPECT_EQ(list.getAt(2), "C");
}

TEST(DoublyLinkedListTest, PushBack) {
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list.getAt(0), "A");
    EXPECT_EQ(list.getAt(1), "B");
    EXPECT_EQ(list.getAt(2), "C");
}

TEST(DoublyLinkedListTest, AddAfter) {
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("C");
    LNode* nodeA = list.find("A");
    list.addAfter(nodeA, "B");
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list.getAt(0), "A");
    EXPECT_EQ(list.getAt(1), "B");
    EXPECT_EQ(list.getAt(2), "C");
}

TEST(DoublyLinkedListTest, AddBefore) {
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("C");
    LNode* nodeC = list.find("C");
    list.addBefore(nodeC, "B");
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list.getAt(0), "A");
    EXPECT_EQ(list.getAt(1), "B");
    EXPECT_EQ(list.getAt(2), "C");
}

TEST(DoublyLinkedListTest, PopFront) {
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    list.popFront();
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list.getAt(0), "B");
    EXPECT_EQ(list.getAt(1), "C");
}

TEST(DoublyLinkedListTest, PopBack) {
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    list.popBack();
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list.getAt(0), "A");
    EXPECT_EQ(list.getAt(1), "B");
}

TEST(DoublyLinkedListTest, DelAfter) {
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    LNode* nodeA = list.find("A");
    list.delAfter(nodeA);
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list.getAt(0), "A");
    EXPECT_EQ(list.getAt(1), "C");
}

TEST(DoublyLinkedListTest, DelBefore) {
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    LNode* nodeC = list.find("C");
    list.delBefore(nodeC);
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list.getAt(0), "A");
    EXPECT_EQ(list.getAt(1), "C");
}

TEST(DoublyLinkedListTest, DelByKey) {
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    list.delByKey("B");
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list.getAt(0), "A");
    EXPECT_EQ(list.getAt(1), "C");
}

TEST(DoublyLinkedListTest, Find) {
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    LNode* nodeB = list.find("B");
    ASSERT_NE(nodeB, nullptr);
    EXPECT_EQ(nodeB->key, "B");
    EXPECT_EQ(list.find("X"), nullptr);
}

TEST(DoublyLinkedListTest, GetAt) {
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    EXPECT_EQ(list.getAt(0), "A");
    EXPECT_EQ(list.getAt(1), "B");
    EXPECT_EQ(list.getAt(2), "C");
    EXPECT_EQ(list.getAt(3), "");
}

TEST(DoublyLinkedListTest, GetSize) {
    DoublyLinkedList list;
    EXPECT_EQ(list.getSize(), 0);
    list.pushBack("A");
    EXPECT_EQ(list.getSize(), 1);
    list.pushBack("B");
    EXPECT_EQ(list.getSize(), 2);
}

TEST(DoublyLinkedListTest, Clear) {
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    EXPECT_EQ(list.getSize(), 3);
    list.clear();
    EXPECT_EQ(list.getSize(), 0);
}

TEST(DoublyLinkedListTest, GetHead) {
    DoublyLinkedList list;
    EXPECT_EQ(list.getHead(), nullptr);
    
    list.pushBack("A");
    ASSERT_NE(list.getHead(), nullptr);
    EXPECT_EQ(list.getHead()->key, "A");
    
    list.pushBack("B");
    EXPECT_EQ(list.getHead()->key, "A");
}

TEST(DoublyLinkedListTest, GetTail) {
    DoublyLinkedList list;
    EXPECT_EQ(list.getTail(), nullptr);
    
    list.pushBack("A");
    ASSERT_NE(list.getTail(), nullptr);
    EXPECT_EQ(list.getTail()->key, "A");
    
    list.pushBack("B");
    EXPECT_EQ(list.getTail()->key, "B");
    
    list.pushBack("C");
    EXPECT_EQ(list.getTail()->key, "C");
}

TEST(DoublyLinkedListTest, Serialize) {
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    std::vector<std::string> data = list.serialize();
    EXPECT_EQ(data.size(), 3);
    EXPECT_EQ(data[0], "A");
    EXPECT_EQ(data[1], "B");
    EXPECT_EQ(data[2], "C");
}

TEST(DoublyLinkedListTest, Deserialize) {
    DoublyLinkedList list;
    std::vector<std::string> data = {"X", "Y", "Z"};
    list.deserialize(data);
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list.getAt(0), "X");
    EXPECT_EQ(list.getAt(1), "Y");
    EXPECT_EQ(list.getAt(2), "Z");
}

TEST(DoublyLinkedListTest, SerializeBinary) {
    DoublyLinkedList list;
    list.pushBack("Hello");
    list.pushBack("World");
    std::stringstream ss;
    list.serializeBinary(ss);
    
    DoublyLinkedList list2;
    list2.deserializeBinary(ss);
    EXPECT_EQ(list2.getSize(), 2);
    EXPECT_EQ(list2.getAt(0), "Hello");
    EXPECT_EQ(list2.getAt(1), "World");
}

TEST(DoublyLinkedListTest, Print) {
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    list.print();
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    EXPECT_NE(output.find("A"), std::string::npos);
    EXPECT_NE(output.find("B"), std::string::npos);
    EXPECT_NE(output.find("C"), std::string::npos);
    EXPECT_NE(output.find("<->"), std::string::npos);
}

TEST(DoublyLinkedListTest, PrintReverse) {
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    list.printReverse();
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    EXPECT_NE(output.find("A"), std::string::npos);
    EXPECT_NE(output.find("B"), std::string::npos);
    EXPECT_NE(output.find("C"), std::string::npos);
    EXPECT_NE(output.find("<->"), std::string::npos);
}

// ==================== Queue Tests ====================
TEST(QueueTest, PushPop) {
    Queue q;
    EXPECT_TRUE(q.empty());
    q.push("A");
    EXPECT_FALSE(q.empty());
    q.push("B");
    q.push("C");
    EXPECT_EQ(q.pop(), "A");
    EXPECT_EQ(q.pop(), "B");
    EXPECT_EQ(q.pop(), "C");
    EXPECT_TRUE(q.empty());
}

TEST(QueueTest, FrontRear) {
    Queue q;
    q.push("A");
    EXPECT_EQ(q.getFront(), "A");
    EXPECT_EQ(q.getRear(), "A");
    q.push("B");
    EXPECT_EQ(q.getFront(), "A");
    EXPECT_EQ(q.getRear(), "B");
    q.pop();
    EXPECT_EQ(q.getFront(), "B");
    EXPECT_EQ(q.getRear(), "B");
}

TEST(QueueTest, Size) {
    Queue q;
    EXPECT_EQ(q.size(), 0);
    q.push("A");
    EXPECT_EQ(q.size(), 1);
    q.push("B");
    EXPECT_EQ(q.size(), 2);
    q.pop();
    EXPECT_EQ(q.size(), 1);
}

TEST(QueueTest, Clear) {
    Queue q;
    q.push("A");
    q.push("B");
    q.push("C");
    EXPECT_EQ(q.size(), 3);
    q.clear();
    EXPECT_EQ(q.size(), 0);
    EXPECT_TRUE(q.empty());
}

TEST(QueueTest, Serialize) {
    Queue q;
    q.push("A");
    q.push("B");
    q.push("C");
    std::vector<std::string> data = q.serialize();
    EXPECT_EQ(data.size(), 3);
    EXPECT_EQ(data[0], "A");
    EXPECT_EQ(data[1], "B");
    EXPECT_EQ(data[2], "C");
}

TEST(QueueTest, Deserialize) {
    Queue q;
    std::vector<std::string> data = {"X", "Y", "Z"};
    q.deserialize(data);
    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.pop(), "X");
    EXPECT_EQ(q.pop(), "Y");
    EXPECT_EQ(q.pop(), "Z");
    EXPECT_TRUE(q.empty());
}

TEST(QueueTest, SerializeBinary) {
    Queue q;
    q.push("Hello");
    q.push("World");
    std::stringstream ss;
    q.serializeBinary(ss);
    
    Queue q2;
    q2.deserializeBinary(ss);
    EXPECT_EQ(q2.size(), 2);
    EXPECT_EQ(q2.pop(), "Hello");
    EXPECT_EQ(q2.pop(), "World");
}

TEST(QueueTest, Print) {
    Queue q;
    q.push("A");
    q.push("B");
    q.push("C");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    q.print();
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    EXPECT_NE(output.find("A"), std::string::npos);
    EXPECT_NE(output.find("B"), std::string::npos);
    EXPECT_NE(output.find("C"), std::string::npos);
    EXPECT_NE(output.find("->"), std::string::npos);
}

// ==================== Stack Tests ====================
TEST(StackTest, PushPop) {
    Stack s;
    EXPECT_TRUE(s.empty());
    s.push("A");
    EXPECT_FALSE(s.empty());
    s.push("B");
    s.push("C");
    EXPECT_EQ(s.pop(), "C");
    EXPECT_EQ(s.pop(), "B");
    EXPECT_EQ(s.pop(), "A");
    EXPECT_TRUE(s.empty());
}

TEST(StackTest, GetTop) {
    Stack s;
    s.push("A");
    EXPECT_EQ(s.getTop(), "A");
    s.push("B");
    EXPECT_EQ(s.getTop(), "B");
    s.pop();
    EXPECT_EQ(s.getTop(), "A");
}

TEST(StackTest, Size) {
    Stack s;
    EXPECT_EQ(s.size(), 0);
    s.push("A");
    EXPECT_EQ(s.size(), 1);
    s.push("B");
    EXPECT_EQ(s.size(), 2);
    s.pop();
    EXPECT_EQ(s.size(), 1);
}

TEST(StackTest, Clear) {
    Stack s;
    s.push("A");
    s.push("B");
    s.push("C");
    EXPECT_EQ(s.size(), 3);
    s.clear();
    EXPECT_EQ(s.size(), 0);
    EXPECT_TRUE(s.empty());
}

TEST(StackTest, Serialize) {
    Stack s;
    s.push("A");
    s.push("B");
    s.push("C");
    std::vector<std::string> data = s.serialize();
    EXPECT_EQ(data.size(), 3);
    EXPECT_EQ(data[0], "C");
    EXPECT_EQ(data[1], "B");
    EXPECT_EQ(data[2], "A");
}

TEST(StackTest, Deserialize) {
    Stack s;
    std::vector<std::string> data = {"C", "B", "A"};
    s.deserialize(data);
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.pop(), "C");
    EXPECT_EQ(s.pop(), "B");
    EXPECT_EQ(s.pop(), "A");
    EXPECT_TRUE(s.empty());
}

TEST(StackTest, SerializeBinary) {
    Stack s;
    s.push("Hello");
    s.push("World");
    std::stringstream ss;
    s.serializeBinary(ss);
    
    Stack s2;
    s2.deserializeBinary(ss);
    EXPECT_EQ(s2.size(), 2);
    EXPECT_EQ(s2.pop(), "Hello");
    EXPECT_EQ(s2.pop(), "World");
}

TEST(StackTest, Print) {
    Stack s;
    s.push("A");
    s.push("B");
    s.push("C");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    s.print();
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    EXPECT_NE(output.find("A"), std::string::npos);
    EXPECT_NE(output.find("B"), std::string::npos);
    EXPECT_NE(output.find("C"), std::string::npos);
    EXPECT_NE(output.find("->"), std::string::npos);
}

TEST(AVLTreeTest, Insert) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);
    EXPECT_EQ(tree.size(), 6);
    EXPECT_FALSE(tree.empty());
}

TEST(AVLTreeTest, Search) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    EXPECT_TRUE(tree.search(10));
    EXPECT_TRUE(tree.search(20));
    EXPECT_TRUE(tree.search(30));
    EXPECT_FALSE(tree.search(40));
}

TEST(AVLTreeTest, Remove) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    EXPECT_TRUE(tree.search(20));
    tree.remove(20);
    EXPECT_FALSE(tree.search(20));
    EXPECT_TRUE(tree.search(10));
    EXPECT_TRUE(tree.search(30));
    EXPECT_EQ(tree.size(), 2);
}

TEST(AVLTreeTest, Empty) {
    AVLTree tree;
    EXPECT_TRUE(tree.empty());
    tree.insert(10);
    EXPECT_FALSE(tree.empty());
    tree.remove(10);
    EXPECT_TRUE(tree.empty());
}

TEST(AVLTreeTest, Size) {
    AVLTree tree;
    EXPECT_EQ(tree.size(), 0);
    tree.insert(10);
    EXPECT_EQ(tree.size(), 1);
    tree.insert(20);
    EXPECT_EQ(tree.size(), 2);
    tree.insert(30);
    EXPECT_EQ(tree.size(), 3);
    tree.remove(20);
    EXPECT_EQ(tree.size(), 2);
}

TEST(AVLTreeTest, Height) {
    AVLTree tree;
    EXPECT_EQ(tree.height(), 0);
    tree.insert(10);
    EXPECT_EQ(tree.height(), 1);
    tree.insert(20);
    EXPECT_GE(tree.height(), 1);
    tree.insert(30);
    EXPECT_GE(tree.height(), 1);
}

TEST(AVLTreeTest, MinMax) {
    AVLTree tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    
    int min = tree.Min();
    int max = tree.Max();
    
    EXPECT_EQ(min, 20);
    EXPECT_EQ(max, 80);
    
    tree.remove(20);
    tree.remove(80);
    
    EXPECT_EQ(tree.Min(), 30);
    EXPECT_EQ(tree.Max(), 70);
}

TEST(AVLTreeTest, GetRoot) {
    AVLTree tree;
    EXPECT_EQ(tree.getRoot(), nullptr);
    
    tree.insert(10);
    EXPECT_NE(tree.getRoot(), nullptr);
    EXPECT_EQ(tree.getRoot()->data, 10);
    
    tree.insert(20);
    tree.insert(5);
    EXPECT_NE(tree.getRoot(), nullptr);
    EXPECT_TRUE(tree.getRoot()->data == 10 || tree.getRoot()->data == 20);
}

TEST(AVLTreeTest, PrintInOrder) {
    AVLTree tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    tree.printInOrder();
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    
    EXPECT_NE(output.find("20"), std::string::npos);
    EXPECT_NE(output.find("30"), std::string::npos);
    EXPECT_NE(output.find("40"), std::string::npos);
    EXPECT_NE(output.find("50"), std::string::npos);
    EXPECT_NE(output.find("60"), std::string::npos);
    EXPECT_NE(output.find("70"), std::string::npos);
    EXPECT_NE(output.find("80"), std::string::npos);
}

TEST(AVLTreeTest, PrintPreOrder) {
    AVLTree tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    tree.printPreOrder();
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    
    EXPECT_NE(output.find("50"), std::string::npos);
    EXPECT_NE(output.find("30"), std::string::npos);
    EXPECT_NE(output.find("70"), std::string::npos);
}

TEST(AVLTreeTest, PrintPostOrder) {
    AVLTree tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    tree.printPostOrder();
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    
    EXPECT_NE(output.find("30"), std::string::npos);
    EXPECT_NE(output.find("70"), std::string::npos);
    EXPECT_NE(output.find("50"), std::string::npos);
}

TEST(AVLTreeTest, Serialize) {
    AVLTree tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    
    std::vector<std::string> data = tree.serialize();
    EXPECT_EQ(data.size(), 7);
    std::vector<int> values;
    for (const auto& str : data) {
        values.push_back(std::stoi(str));
    }
    
    EXPECT_NE(std::find(values.begin(), values.end(), 20), values.end());
    EXPECT_NE(std::find(values.begin(), values.end(), 30), values.end());
    EXPECT_NE(std::find(values.begin(), values.end(), 40), values.end());
    EXPECT_NE(std::find(values.begin(), values.end(), 50), values.end());
    EXPECT_NE(std::find(values.begin(), values.end(), 60), values.end());
    EXPECT_NE(std::find(values.begin(), values.end(), 70), values.end());
    EXPECT_NE(std::find(values.begin(), values.end(), 80), values.end());
}

TEST(AVLTreeTest, Deserialize) {
    AVLTree tree;
    std::vector<std::string> data = {"20", "30", "40", "50", "60", "70", "80"};
    tree.deserialize(data);
    EXPECT_EQ(tree.size(), 7);
    EXPECT_TRUE(tree.search(20));
    EXPECT_TRUE(tree.search(50));
    EXPECT_TRUE(tree.search(80));
    EXPECT_FALSE(tree.search(90));
}

TEST(AVLTreeTest, SerializeBinary) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    std::stringstream ss;
    tree.serializeBinary(ss);
    
    AVLTree tree2;
    tree2.deserializeBinary(ss);
    EXPECT_EQ(tree2.size(), 3);
    EXPECT_TRUE(tree2.search(10));
    EXPECT_TRUE(tree2.search(20));
    EXPECT_TRUE(tree2.search(30));
}

TEST(HashTableTest, Constructor) {
    HashTable ht(5);
    EXPECT_EQ(ht.getSize(), 0);
    EXPECT_EQ(ht.getCapacity(), 5);
    EXPECT_TRUE(ht.empty());
}

TEST(HashTableTest, Insert) {
    HashTable ht;
    EXPECT_TRUE(ht.insert("key1", "value1"));
    EXPECT_TRUE(ht.insert("key2", "value2"));
    EXPECT_EQ(ht.getSize(), 2);
    EXPECT_FALSE(ht.empty());
}

TEST(HashTableTest, Find) {
    HashTable ht;
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");
    
    std::string value;
    EXPECT_TRUE(ht.find("key1", value));
    EXPECT_EQ(value, "value1");
    
    EXPECT_TRUE(ht.find("key2", value));
    EXPECT_EQ(value, "value2");
    
    EXPECT_FALSE(ht.find("key3", value));
}

TEST(HashTableTest, Remove) {
    HashTable ht;
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");
    
    EXPECT_TRUE(ht.remove("key1"));
    EXPECT_EQ(ht.getSize(), 1);
    
    std::string value;
    EXPECT_FALSE(ht.find("key1", value));
    EXPECT_TRUE(ht.find("key2", value));
    EXPECT_EQ(value, "value2");
    
    EXPECT_FALSE(ht.remove("key3"));
}

TEST(HashTableTest, Clear) {
    HashTable ht;
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");
    ht.insert("key3", "value3");
    
    EXPECT_EQ(ht.getSize(), 3);
    ht.clear();
    EXPECT_EQ(ht.getSize(), 0);
    EXPECT_TRUE(ht.empty());
}

TEST(HashTableTest, GetAllItems) {
    HashTable ht;
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");
    ht.insert("key3", "value3");
    
    std::vector<std::pair<std::string, std::string>> items;
    ht.getAllItems(items);
    
    EXPECT_EQ(items.size(), 3);
    
    bool found1 = false, found2 = false, found3 = false;
    for (const auto& item : items) {
        if (item.first == "key1" && item.second == "value1") found1 = true;
        if (item.first == "key2" && item.second == "value2") found2 = true;
        if (item.first == "key3" && item.second == "value3") found3 = true;
    }
    
    EXPECT_TRUE(found1);
    EXPECT_TRUE(found2);
    EXPECT_TRUE(found3);
}

TEST(HashTableTest, Rehash) {
    HashTable ht(2); 
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");
    ht.insert("key3", "value3");
    ht.insert("key4", "value4");
    
    EXPECT_GT(ht.getCapacity(), 2);
    EXPECT_EQ(ht.getSize(), 4);
    
    std::string value;
    EXPECT_TRUE(ht.find("key1", value));
    EXPECT_EQ(value, "value1");
    EXPECT_TRUE(ht.find("key2", value));
    EXPECT_EQ(value, "value2");
    EXPECT_TRUE(ht.find("key3", value));
    EXPECT_EQ(value, "value3");
    EXPECT_TRUE(ht.find("key4", value));
    EXPECT_EQ(value, "value4");
}

TEST(HashTableTest, Serialize) {
    HashTable ht;
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");
    ht.insert("key3", "value3");
    
    std::vector<std::string> data = ht.serialize();
    EXPECT_EQ(data.size(), 3);
    
    bool found1 = false, found2 = false, found3 = false;
    for (const auto& item : data) {
        if (item == "key1:value1") found1 = true;
        if (item == "key2:value2") found2 = true;
        if (item == "key3:value3") found3 = true;
    }
    EXPECT_TRUE(found1);
    EXPECT_TRUE(found2);
    EXPECT_TRUE(found3);
}

TEST(HashTableTest, Deserialize) {
    HashTable ht;
    std::vector<std::string> data = {"key1:value1", "key2:value2", "key3:value3"};
    ht.deserialize(data);
    
    EXPECT_EQ(ht.getSize(), 3);
    
    std::string value;
    EXPECT_TRUE(ht.find("key1", value));
    EXPECT_EQ(value, "value1");
    EXPECT_TRUE(ht.find("key2", value));
    EXPECT_EQ(value, "value2");
    EXPECT_TRUE(ht.find("key3", value));
    EXPECT_EQ(value, "value3");
}

TEST(HashTableTest, SerializeBinary) {
    HashTable ht;
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");
    std::stringstream ss;
    ht.serializeBinary(ss);
    
    HashTable ht2;
    ht2.deserializeBinary(ss);
    EXPECT_EQ(ht2.getSize(), 2);
    
    std::string value;
    EXPECT_TRUE(ht2.find("key1", value));
    EXPECT_EQ(value, "value1");
    EXPECT_TRUE(ht2.find("key2", value));
    EXPECT_EQ(value, "value2");
}

TEST(HashTableTest, Print) {
    HashTable ht;
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");
    ht.insert("key3", "value3");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    ht.print();
    
    std::cout.rdbuf(old);
    
    std::string output = buffer.str();
    
    EXPECT_NE(output.find("key1"), std::string::npos);
    EXPECT_NE(output.find("key2"), std::string::npos);
    EXPECT_NE(output.find("key3"), std::string::npos);
    EXPECT_NE(output.find("value1"), std::string::npos);
    EXPECT_NE(output.find("value2"), std::string::npos);
    EXPECT_NE(output.find("value3"), std::string::npos);
}

TEST(EdgeCasesTest, EmptyStructures) {
    DynamicArray arr;
    EXPECT_EQ(arr.getSize(), 0);
    
    ForwardList flist;
    EXPECT_EQ(flist.getSize(), 0);
    
    DoublyLinkedList dlist;
    EXPECT_EQ(dlist.getSize(), 0);
    
    Queue q;
    EXPECT_TRUE(q.empty());
    
    Stack s;
    EXPECT_TRUE(s.empty());
    
    AVLTree tree;
    EXPECT_TRUE(tree.empty());
    
    HashTable ht;
    EXPECT_TRUE(ht.empty());
}

TEST(EdgeCasesTest, SingleElementOperations) {
    DynamicArray arr;
    arr.pushBack("A");
    EXPECT_EQ(arr.getSize(), 1);
    arr.remove(0);
    EXPECT_EQ(arr.getSize(), 0);
    
    ForwardList flist;
    flist.pushBack("A");
    EXPECT_EQ(flist.getSize(), 1);
    flist.popFront();
    EXPECT_EQ(flist.getSize(), 0);
    
    DoublyLinkedList dlist;
    dlist.pushBack("A");
    EXPECT_EQ(dlist.getSize(), 1);
    dlist.popFront();
    EXPECT_EQ(dlist.getSize(), 0);
    
    Queue q;
    q.push("A");
    EXPECT_EQ(q.size(), 1);
    q.pop();
    EXPECT_TRUE(q.empty());
    
    Stack s;
    s.push("A");
    EXPECT_EQ(s.size(), 1);
    s.pop();
    EXPECT_TRUE(s.empty());
    
    AVLTree tree;
    tree.insert(10);
    EXPECT_EQ(tree.size(), 1);
    tree.remove(10);
    EXPECT_TRUE(tree.empty());
    
    HashTable ht;
    ht.insert("key", "value");
    EXPECT_EQ(ht.getSize(), 1);
    ht.remove("key");
    EXPECT_TRUE(ht.empty());
}

TEST(EdgeCasesTest, InvalidOperations) {
    DynamicArray arr;
    EXPECT_THROW(arr.get(0), std::out_of_range);
    EXPECT_THROW(arr.set(0, "value"), std::out_of_range);
    EXPECT_THROW(arr.remove(0), std::out_of_range);
    EXPECT_THROW(arr.insert(1, "value"), std::out_of_range);
    
    Queue q;
    EXPECT_THROW(q.pop(), std::runtime_error);
    EXPECT_THROW(q.getFront(), std::runtime_error);
    EXPECT_THROW(q.getRear(), std::runtime_error);
    
    Stack s;
    EXPECT_THROW(s.pop(), std::runtime_error);
    EXPECT_THROW(s.getTop(), std::runtime_error);
}

TEST(EdgeCasesTest, MemoryLeakCheck) {
    for (int i = 0; i < 10; i++) {
        DynamicArray* arr = new DynamicArray();
        for (int j = 0; j < 100; j++) {
            arr->pushBack("item" + std::to_string(j));
        }
        delete arr;
        
        ForwardList* flist = new ForwardList();
        for (int j = 0; j < 100; j++) {
            flist->pushBack("item" + std::to_string(j));
        }
        delete flist;
        
        DoublyLinkedList* dlist = new DoublyLinkedList();
        for (int j = 0; j < 100; j++) {
            dlist->pushBack("item" + std::to_string(j));
        }
        delete dlist;
        
        Queue* q = new Queue();
        for (int j = 0; j < 100; j++) {
            q->push("item" + std::to_string(j));
        }
        delete q;
        
        Stack* s = new Stack();
        for (int j = 0; j < 100; j++) {
            s->push("item" + std::to_string(j));
        }
        delete s;
        
        AVLTree* tree = new AVLTree();
        for (int j = 0; j < 100; j++) {
            tree->insert(j);
        }
        delete tree;
        
        HashTable* ht = new HashTable();
        for (int j = 0; j < 100; j++) {
            ht->insert("key" + std::to_string(j), "value" + std::to_string(j));
        }
        delete ht;
    }
    
    SUCCEED(); 
}

TEST(IntegrationTest, SerializeDeserializeAll) {
    DynamicArray arr;
    arr.pushBack("A");
    arr.pushBack("B");
    arr.pushBack("C");
    
    std::vector<std::string> arrData = arr.serialize();
    DynamicArray arr2;
    arr2.deserialize(arrData);
    EXPECT_EQ(arr2.getSize(), 3);
    EXPECT_EQ(arr2.get(0), "A");
    EXPECT_EQ(arr2.get(1), "B");
    EXPECT_EQ(arr2.get(2), "C");
    
    ForwardList flist;
    flist.pushBack("X");
    flist.pushBack("Y");
    flist.pushBack("Z");
    
    std::vector<std::string> flistData = flist.serialize();
    ForwardList flist2;
    flist2.deserialize(flistData);
    EXPECT_EQ(flist2.getSize(), 3);
    EXPECT_EQ(flist2.getAt(0), "X");
    EXPECT_EQ(flist2.getAt(1), "Y");
    EXPECT_EQ(flist2.getAt(2), "Z");
    
    DoublyLinkedList dlist;
    dlist.pushBack("1");
    dlist.pushBack("2");
    dlist.pushBack("3");
    
    std::vector<std::string> dlistData = dlist.serialize();
    DoublyLinkedList dlist2;
    dlist2.deserialize(dlistData);
    EXPECT_EQ(dlist2.getSize(), 3);
    EXPECT_EQ(dlist2.getAt(0), "1");
    EXPECT_EQ(dlist2.getAt(1), "2");
    EXPECT_EQ(dlist2.getAt(2), "3");
    
    Queue q;
    q.push("A");
    q.push("B");
    q.push("C");
    
    std::vector<std::string> qData = q.serialize();
    Queue q2;
    q2.deserialize(qData);
    EXPECT_EQ(q2.size(), 3);
    EXPECT_EQ(q2.pop(), "A");
    EXPECT_EQ(q2.pop(), "B");
    EXPECT_EQ(q2.pop(), "C");
    
    Stack s;
    s.push("A");
    s.push("B");
    s.push("C");
    
    std::vector<std::string> sData = s.serialize();
    Stack s2;
    s2.deserialize(sData);
    EXPECT_EQ(s2.size(), 3);
    EXPECT_EQ(s2.pop(), "C");
    EXPECT_EQ(s2.pop(), "B");
    EXPECT_EQ(s2.pop(), "A");
    
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    
    std::vector<std::string> treeData = tree.serialize();
    AVLTree tree2;
    tree2.deserialize(treeData);
    EXPECT_EQ(tree2.size(), 3);
    EXPECT_TRUE(tree2.search(10));
    EXPECT_TRUE(tree2.search(20));
    EXPECT_TRUE(tree2.search(30));
    
    HashTable ht;
    ht.insert("k1", "v1");
    ht.insert("k2", "v2");
    ht.insert("k3", "v3");
    
    std::vector<std::string> htData = ht.serialize();
    HashTable ht2;
    ht2.deserialize(htData);
    EXPECT_EQ(ht2.getSize(), 3);
    std::string value;
    EXPECT_TRUE(ht2.find("k1", value));
    EXPECT_EQ(value, "v1");
    EXPECT_TRUE(ht2.find("k2", value));
    EXPECT_EQ(value, "v2");
    EXPECT_TRUE(ht2.find("k3", value));
    EXPECT_EQ(value, "v3");
}

TEST(IntegrationTest, BinarySerializationAll) {
    std::stringstream ss;
    
    DynamicArray arr;
    arr.pushBack("Hello");
    arr.pushBack("World");
    arr.serializeBinary(ss);
    
    ForwardList flist;
    flist.pushBack("Test");
    flist.pushBack("Data");
    flist.serializeBinary(ss);
    
    DoublyLinkedList dlist;
    dlist.pushBack("One");
    dlist.pushBack("Two");
    dlist.serializeBinary(ss);
    
    Queue q;
    q.push("First");
    q.push("Second");
    q.serializeBinary(ss);
    
    Stack s;
    s.push("Bottom");
    s.push("Top");
    s.serializeBinary(ss);
    
    AVLTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.serializeBinary(ss);
    
    HashTable ht;
    ht.insert("key1", "val1");
    ht.insert("key2", "val2");
    ht.serializeBinary(ss);
    
    DynamicArray arr2;
    arr2.deserializeBinary(ss);
    EXPECT_EQ(arr2.getSize(), 2);
    EXPECT_EQ(arr2.get(0), "Hello");
    EXPECT_EQ(arr2.get(1), "World");
    
    ForwardList flist2;
    flist2.deserializeBinary(ss);
    EXPECT_EQ(flist2.getSize(), 2);
    EXPECT_EQ(flist2.getAt(0), "Test");
    EXPECT_EQ(flist2.getAt(1), "Data");
    
    DoublyLinkedList dlist2;
    dlist2.deserializeBinary(ss);
    EXPECT_EQ(dlist2.getSize(), 2);
    EXPECT_EQ(dlist2.getAt(0), "One");
    EXPECT_EQ(dlist2.getAt(1), "Two");
    
    Queue q2;
    q2.deserializeBinary(ss);
    EXPECT_EQ(q2.size(), 2);
    EXPECT_EQ(q2.pop(), "First");
    EXPECT_EQ(q2.pop(), "Second");
    
    Stack s2;
    s2.deserializeBinary(ss);
    EXPECT_EQ(s2.size(), 2);
    EXPECT_EQ(s2.pop(), "Bottom");
    EXPECT_EQ(s2.pop(), "Top");
    
    AVLTree tree2;
    tree2.deserializeBinary(ss);
    EXPECT_EQ(tree2.size(), 3);
    EXPECT_TRUE(tree2.search(1));
    EXPECT_TRUE(tree2.search(2));
    EXPECT_TRUE(tree2.search(3));
    
    HashTable ht2;
    ht2.deserializeBinary(ss);
    EXPECT_EQ(ht2.getSize(), 2);
    std::string value;
    EXPECT_TRUE(ht2.find("key1", value));
    EXPECT_EQ(value, "val1");
    EXPECT_TRUE(ht2.find("key2", value));
    EXPECT_EQ(value, "val2");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}