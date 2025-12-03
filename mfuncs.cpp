#include "mfuncs.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>

DynamicArray::DynamicArray(int initialCapacity) {
    if (initialCapacity <= 0) initialCapacity = 10;
    data = new std::string[initialCapacity];
    size = 0;
    capacity = initialCapacity;
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

void DynamicArray::ensureCapacity(int requiredSize) {
    if (requiredSize >= capacity) {
        int newCapacity = capacity * 2;
        if (newCapacity < requiredSize) newCapacity = requiredSize + 10;

        std::string* newData = new std::string[newCapacity];
        for (int i = 0; i < size; i++) newData[i] = data[i];

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
}

void DynamicArray::pushBack(const std::string& value) {
    ensureCapacity(size + 1);
    data[size++] = value;
}

void DynamicArray::insert(int index, const std::string& value) {
    if (index < 0 || index > size) throw std::out_of_range("Индекс вне диапазона");

    ensureCapacity(size + 1);
    for (int i = size; i > index; i--) data[i] = data[i - 1];
    data[index] = value;
    size++;
}

void DynamicArray::remove(int index) {
    if (index < 0 || index >= size) throw std::out_of_range("Индекс вне диапазона");

    for (int i = index; i < size - 1; i++) data[i] = data[i + 1];
    size--;
}

void DynamicArray::set(int index, const std::string& value) {
    if (index < 0 || index >= size) throw std::out_of_range("Индекс вне диапазона");
    data[index] = value;
}

std::string DynamicArray::get(int index) const {
    if (index < 0 || index >= size) throw std::out_of_range("Индекс вне диапазона");
    return data[index];
}

int DynamicArray::getSize() const { return size; }
int DynamicArray::getCapacity() const { return capacity; }

int DynamicArray::find(const std::string& value) const {
    for (int i = 0; i < size; i++) if (data[i] == value) return i;
    return -1;
}

void DynamicArray::clear() { 
    size = 0; 
}

void DynamicArray::print() const {
    std::cout << "Массив [" << size << "/" << capacity << "]: ";
    for (int i = 0; i < size; i++) {
        std::cout << "\"" << data[i] << "\"";
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}

std::vector<std::string> DynamicArray::serialize() const {
    std::vector<std::string> result;
    for (int i = 0; i < size; i++) {
        result.push_back(data[i]);
    }
    return result;
}

void DynamicArray::deserialize(const std::vector<std::string>& data_vec) {
    clear();
    for (const auto& item : data_vec) {
        pushBack(item);
    }
}

void DynamicArray::serializeBinary(std::ostream& os) const {
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (int i = 0; i < size; i++) {
        int len = data[i].length();
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        os.write(data[i].c_str(), len);
    }
}

void DynamicArray::deserializeBinary(std::istream& is) {
    clear();
    int newSize;
    is.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));
    
    for (int i = 0; i < newSize; i++) {
        int len;
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        
        char* buffer = new char[len + 1];
        is.read(buffer, len);
        buffer[len] = '\0';
        
        pushBack(std::string(buffer));
        delete[] buffer;
    }
}