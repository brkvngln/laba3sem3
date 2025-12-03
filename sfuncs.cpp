#include "sfuncs.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>

Stack::Stack() : top(nullptr) {}
Stack::~Stack() { clear(); }

void Stack::push(const std::string& value) {
    SNode* newNode = new SNode(value);
    newNode->next = top;
    top = newNode;
}

std::string Stack::pop() {
    if (!top) throw std::runtime_error("Стек пуст");
    SNode* temp = top;
    std::string value = temp->data;
    top = top->next;
    delete temp;
    return value;
}

std::string Stack::getTop() const {
    if (!top) throw std::runtime_error("Стек пуст");
    return top->data;
}

bool Stack::empty() const { return top == nullptr; }

int Stack::size() const {
    int count = 0;
    SNode* current = top;
    while (current) { count++; current = current->next; }
    return count;
}

void Stack::print() const {
    SNode* current = top;
    std::cout << "Стек: ";
    while (current) {
        std::cout << current->data;
        if (current->next) std::cout << " -> ";
        current = current->next;
    }
    std::cout << " -> NULL" << std::endl;
}

void Stack::clear() {
    while (!empty()) pop();
}

std::vector<std::string> Stack::serialize() const {
    std::vector<std::string> result;
    SNode* current = top;
    while (current) {
        result.push_back(current->data);
        current = current->next;
    }
    return result;
}

void Stack::deserialize(const std::vector<std::string>& data) {
    clear();
    for (auto it = data.rbegin(); it != data.rend(); ++it) {
        push(*it);
    }
}

void Stack::serializeBinary(std::ostream& os) const {
    int stackSize = size();
    os.write(reinterpret_cast<const char*>(&stackSize), sizeof(stackSize));
    
    std::vector<std::string> elements;
    SNode* current = top;
    while (current) {
        elements.push_back(current->data);
        current = current->next;
    }
    
    for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
        int len = it->length();
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        os.write(it->c_str(), len);
    }
}

void Stack::deserializeBinary(std::istream& is) {
    clear();
    int size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    std::vector<std::string> elements;
    for (int i = 0; i < size; i++) {
        int len;
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        
        char* buffer = new char[len + 1];
        is.read(buffer, len);
        buffer[len] = '\0';
        
        elements.push_back(std::string(buffer));
        delete[] buffer;
    }
    
    for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
        push(*it);
    }
}