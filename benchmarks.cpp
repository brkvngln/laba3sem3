#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include "mfuncs.h"
#include "ffuncs.h"
#include "lfuncs.h"
#include "qfuncs.h"
#include "sfuncs.h"
#include "tfuncs.h"
#include "hfuncs.h" 

using namespace std;
using namespace std::chrono;

class Benchmark {
private:
    string name;
    steady_clock::time_point start_time;
    
public:
    Benchmark(const string& benchmark_name) : name(benchmark_name) {
        start_time = steady_clock::now();
    }
    
    ~Benchmark() {
        auto end_time = steady_clock::now();
        auto duration = duration_cast<milliseconds>(end_time - start_time);
        cout << "BENCHMARK " << name << ": " << duration.count() << " ms" << endl;
    }
};

void benchmarkDynamicArray() {
    Benchmark bench("DynamicArray_PushBack_10000");
    DynamicArray arr;
    for (int i = 0; i < 10000; i++) {
        arr.pushBack("element_" + to_string(i));
    }
}

void benchmarkForwardList() {
    Benchmark bench("ForwardList_PushFront_5000");
    ForwardList list;
    for (int i = 0; i < 5000; i++) {
        list.pushFront("element_" + to_string(i));
    }
}

void benchmarkDoublyLinkedList() {
    Benchmark bench("DoublyLinkedList_PushBack_5000");
    DoublyLinkedList list;
    for (int i = 0; i < 5000; i++) {
        list.pushBack("element_" + to_string(i));
    }
}

void benchmarkQueue() {
    Benchmark bench("Queue_Push_10000");
    Queue queue;
    for (int i = 0; i < 10000; i++) {
        queue.push("element_" + to_string(i));
    }
}

void benchmarkStack() {
    Benchmark bench("Stack_Push_10000");
    Stack stack;
    for (int i = 0; i < 10000; i++) {
        stack.push("element_" + to_string(i));
    }
}

void benchmarkAVLTree() {
    Benchmark bench("AVLTree_Insert_5000");
    AVLTree tree;
    for (int i = 0; i < 5000; i++) {
        tree.insert(i);
    }
}

void benchmarkHashTable() {
    Benchmark bench("HashTable_InsertFind_5000");
    HashTable table(1000);
    
    for (int i = 0; i < 5000; i++) {
        table.insert("key_" + to_string(i), "value_" + to_string(i));
    }
    
    string value;
    for (int i = 0; i < 5000; i++) {
        table.find("key_" + to_string(i), value);
    }
}

void benchmarkMixedOperations() {
    Benchmark bench("MixedOperations_AllStructures");
    
    DynamicArray arr;
    for (int i = 0; i < 1000; i++) {
        arr.pushBack("array_" + to_string(i));
    }
    for (int i = 0; i < 500; i++) {
        if (arr.getSize() > 0) {
            arr.remove(0);
        }
    }
    
    ForwardList flist;
    for (int i = 0; i < 1000; i++) {
        flist.pushFront("list_" + to_string(i));
    }
    
    Queue queue;
    for (int i = 0; i < 1000; i++) {
        queue.push("queue_" + to_string(i));
    }
    for (int i = 0; i < 500; i++) {
        if (!queue.empty()) {
            queue.pop();
        }
    }
    
    Stack stack;
    for (int i = 0; i < 1000; i++) {
        stack.push("stack_" + to_string(i));
    }
    for (int i = 0; i < 500; i++) {
        if (!stack.empty()) {
            stack.pop();
        }
    }
    
    AVLTree tree;
    for (int i = 0; i < 1000; i++) {
        tree.insert(i);
    }
    for (int i = 0; i < 500; i++) {
        tree.remove(i);
    }

    HashTable hashTable(500);
    for (int i = 0; i < 1000; i++) {
        hashTable.insert("hash_" + to_string(i), "value_" + to_string(i));
    }
    for (int i = 0; i < 500; i++) {
        hashTable.remove("hash_" + to_string(i));
    }
}

int main() {
    cout << "=== PERFORMANCE TESTING DATA STRUCTURES ===" << endl;
    cout << "Running performance tests..." << endl << endl;
    
    benchmarkDynamicArray();
    benchmarkForwardList();
    benchmarkDoublyLinkedList();
    benchmarkQueue();
    benchmarkStack();
    benchmarkAVLTree();
    benchmarkHashTable();
    benchmarkMixedOperations();
    
    cout << endl << "=== PERFORMANCE TESTING COMPLETED ===" << endl;
    
    return 0;
}