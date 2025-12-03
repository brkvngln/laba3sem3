#include "qfuncs.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>

Queue::Queue() : front(nullptr), rear(nullptr) {}
Queue::~Queue() { clear(); }

void Queue::push(const std::string& value) {
    QNode* newNode = new QNode(value);
    if (!rear) front = rear = newNode;
    else {
        rear->next = newNode;
        rear = newNode;
    }
}

std::string Queue::pop() {
    if (!front) throw std::runtime_error("Очередь пуста");
    QNode* temp = front;
    std::string value = temp->data;
    front = front->next;
    if (!front) rear = nullptr;
    delete temp;
    return value;
}

std::string Queue::getFront() const {
    if (!front) throw std::runtime_error("Очередь пуста");
    return front->data;
}

std::string Queue::getRear() const {
    if (!rear) throw std::runtime_error("Очередь пуста");
    return rear->data;
}

bool Queue::empty() const { return front == nullptr; }

int Queue::size() const {
    int count = 0;
    QNode* current = front;
    while (current) { count++; current = current->next; }
    return count;
}

void Queue::print() const {
    QNode* current = front;
    std::cout << "Очередь: ";
    while (current) {
        std::cout << current->data;
        if (current->next) std::cout << " -> ";
        current = current->next;
    }
    std::cout << " -> NULL" << std::endl;
}

void Queue::clear() {
    while (!empty()) pop();
}

std::vector<std::string> Queue::serialize() const {
    std::vector<std::string> result;
    QNode* current = front;
    while (current) {
        result.push_back(current->data);
        current = current->next;
    }
    return result;
}

void Queue::deserialize(const std::vector<std::string>& data) {
    clear();
    for (const auto& item : data) {
        push(item);
    }
}

void Queue::serializeBinary(std::ostream& os) const {
    int queueSize = size();
    os.write(reinterpret_cast<const char*>(&queueSize), sizeof(queueSize));
    
    QNode* current = front;
    while (current) {
        int len = current->data.length();
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        os.write(current->data.c_str(), len);
        current = current->next;
    }
}

void Queue::deserializeBinary(std::istream& is) {
    clear();
    int size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    for (int i = 0; i < size; i++) {
        int len;
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        
        char* buffer = new char[len + 1];
        is.read(buffer, len);
        buffer[len] = '\0';
        
        push(std::string(buffer));
        delete[] buffer;
    }
}