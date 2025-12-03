#include "ffuncs.h"
#include <iostream>
#include <vector>
#include <cstring>

ForwardList::ForwardList() : head(nullptr) {}
ForwardList::~ForwardList() { clear(); }

void ForwardList::pushFront(const std::string& key) {
    FNode* newNode = new FNode(key);
    newNode->next = head;
    head = newNode;
}

void ForwardList::pushBack(const std::string& key) {
    FNode* newNode = new FNode(key);
    if (!head) head = newNode;
    else {
        FNode* current = head;
        while (current->next) current = current->next;
        current->next = newNode;
    }
}

void ForwardList::addAfter(FNode* node, const std::string& key) {
    if (!node) return;
    FNode* newNode = new FNode(key);
    newNode->next = node->next;
    node->next = newNode;
}

void ForwardList::delAfter(FNode* node) {
    if (!node || !node->next) return;
    FNode* delNode = node->next;
    node->next = delNode->next;
    delete delNode;
}

void ForwardList::addBefore(FNode* node, const std::string& key) {
    if (!node) return;
    if (head == node) pushFront(key);
    else {
        FNode* current = head;
        while (current && current->next != node) current = current->next;
        if (current) addAfter(current, key);
    }
}

void ForwardList::delBefore(FNode* node) {
    if (!node || !head || head == node) return;
    if (head->next == node) popFront();
    else {
        FNode* current = head;
        while (current && current->next && current->next->next != node) current = current->next;
        if (current && current->next) delAfter(current);
    }
}

void ForwardList::popFront() {
    if (!head) return;
    FNode* temp = head;
    head = head->next;
    delete temp;
}

void ForwardList::delByKey(const std::string& key) {
    if (!head) return;
    if (head->key == key) popFront();
    else {
        FNode* current = head;
        while (current->next && current->next->key != key) current = current->next;
        if (current->next) delAfter(current);
    }
}

FNode* ForwardList::find(const std::string& key) const {
    FNode* current = head;
    while (current) {
        if (current->key == key) return current;
        current = current->next;
    }
    return nullptr;
}

std::string ForwardList::getAt(int index) const {
    FNode* current = head;
    for (int i = 0; i < index && current; i++) current = current->next;
    return current ? current->key : "";
}

void ForwardList::print() const {
    FNode* current = head;
    std::cout << "Односвязный список: ";
    while (current) {
        std::cout << current->key;
        if (current->next) std::cout << " -> ";
        current = current->next;
    }
    std::cout << " -> NULL" << std::endl;
}

int ForwardList::getSize() const {
    int count = 0;
    FNode* current = head;
    while (current) { count++; current = current->next; }
    return count;
}

void ForwardList::clear() {
    while (head) popFront();
}

std::vector<std::string> ForwardList::serialize() const {
    std::vector<std::string> result;
    FNode* current = head;
    while (current) {
        result.push_back(current->key);
        current = current->next;
    }
    return result;
}

void ForwardList::deserialize(const std::vector<std::string>& data) {
    clear();
    for (const auto& item : data) {
        pushBack(item);
    }
}

void ForwardList::serializeBinary(std::ostream& os) const {
    int size = getSize();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    
    FNode* current = head;
    while (current) {
        int len = current->key.length();
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        os.write(current->key.c_str(), len);
        current = current->next;
    }
}

void ForwardList::deserializeBinary(std::istream& is) {
    clear();
    int size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    for (int i = 0; i < size; i++) {
        int len;
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        
        char* buffer = new char[len + 1];
        is.read(buffer, len);
        buffer[len] = '\0';
        
        pushBack(std::string(buffer));
        delete[] buffer;
    }
}