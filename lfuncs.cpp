#include "lfuncs.h"
#include <iostream>
#include <vector>
#include <cstring>

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}
DoublyLinkedList::~DoublyLinkedList() { clear(); }

void DoublyLinkedList::pushFront(const std::string& key) {
    LNode* newNode = new LNode(key);
    if (!head) head = tail = newNode;
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void DoublyLinkedList::pushBack(const std::string& key) {
    LNode* newNode = new LNode(key);
    if (!head) head = tail = newNode;
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void DoublyLinkedList::addAfter(LNode* node, const std::string& key) {
    if (!node) return;
    LNode* newNode = new LNode(key);
    newNode->next = node->next;
    newNode->prev = node;
    if (node->next) node->next->prev = newNode;
    node->next = newNode;
    if (node == tail) tail = newNode;
}

void DoublyLinkedList::addBefore(LNode* node, const std::string& key) {
    if (!node) return;
    LNode* newNode = new LNode(key);
    newNode->prev = node->prev;
    newNode->next = node;
    if (node->prev) node->prev->next = newNode;
    node->prev = newNode;
    if (node == head) head = newNode;
}

void DoublyLinkedList::popFront() {
    if (!head) return;
    LNode* temp = head;
    head = head->next;
    if (head) head->prev = nullptr;
    else tail = nullptr;
    delete temp;
}

void DoublyLinkedList::popBack() {
    if (!tail) return;
    LNode* temp = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    else head = nullptr;
    delete temp;
}

void DoublyLinkedList::delAfter(LNode* node) {
    if (!node || !node->next) return;
    LNode* delNode = node->next;
    node->next = delNode->next;
    if (delNode->next) delNode->next->prev = node;
    if (delNode == tail) tail = node;
    delete delNode;
}

void DoublyLinkedList::delBefore(LNode* node) {
    if (!node || !node->prev) return;
    LNode* delNode = node->prev;
    node->prev = delNode->prev;
    if (delNode->prev) delNode->prev->next = node;
    if (delNode == head) head = node;
    delete delNode;
}

void DoublyLinkedList::delByKey(const std::string& key) {
    LNode* current = head;
    while (current) {
        if (current->key == key) {
            if (current == head) popFront();
            else if (current == tail) popBack();
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
            }
            return;
        }
        current = current->next;
    }
}

LNode* DoublyLinkedList::find(const std::string& key) const {
    LNode* current = head;
    while (current) {
        if (current->key == key) return current;
        current = current->next;
    }
    return nullptr;
}

std::string DoublyLinkedList::getAt(int index) const {
    LNode* current = head;
    for (int i = 0; i < index && current; i++) current = current->next;
    return current ? current->key : "";
}

void DoublyLinkedList::print() const {
    LNode* current = head;
    std::cout << "Двусвязный список: ";
    while (current) {
        std::cout << current->key;
        if (current->next) std::cout << " <-> ";
        current = current->next;
    }
    std::cout << " -> NULL" << std::endl;
}

void DoublyLinkedList::printReverse() const {
    LNode* current = tail;
    std::cout << "Двусвязный список (обратный): ";
    while (current) {
        std::cout << current->key;
        if (current->prev) std::cout << " <-> ";
        current = current->prev;
    }
    std::cout << " -> NULL" << std::endl;
}

int DoublyLinkedList::getSize() const {
    int count = 0;
    LNode* current = head;
    while (current) { count++; current = current->next; }
    return count;
}

void DoublyLinkedList::clear() {
    while (head) popFront();
}

std::vector<std::string> DoublyLinkedList::serialize() const {
    std::vector<std::string> result;
    LNode* current = head;
    while (current) {
        result.push_back(current->key);
        current = current->next;
    }
    return result;
}

void DoublyLinkedList::deserialize(const std::vector<std::string>& data) {
    clear();
    for (const auto& item : data) {
        pushBack(item);
    }
}

void DoublyLinkedList::serializeBinary(std::ostream& os) const {
    int size = getSize();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    
    LNode* current = head;
    while (current) {
        int len = current->key.length();
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        os.write(current->key.c_str(), len);
        current = current->next;
    }
}

void DoublyLinkedList::deserializeBinary(std::istream& is) {
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