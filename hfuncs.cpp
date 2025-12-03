#include "hfuncs.h"
#include <vector>
#include <sstream>
#include <utility>
#include <iostream>
#include <cstring>

int HashTable::hashFunction(const std::string& key) const {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % capacity;
    }
    return hash;
}

void HashTable::rehash() {
    int newCapacity = capacity * 2;
    std::vector<HashItem> newItems(newCapacity);

    std::vector<std::pair<std::string, std::string>> oldItems;
    getAllItems(oldItems);
    
    clear();
    
    capacity = newCapacity;
    items = std::vector<HashItem>(newCapacity);
    
    for (const auto& item : oldItems) {
        insert(item.first, item.second);
    }
}

HashTable::HashTable(int cap) : capacity(std::max(1, cap)), size(0) {
    items.resize(capacity);
}

HashTable::~HashTable() {
    clear();
}

bool HashTable::insert(const std::string& key, const std::string& value) {
    if (size >= capacity * 0.7) {
        rehash();
    }

    int index = hashFunction(key);
    int startIndex = index;

    do {
        if (items[index].isEmpty || items[index].isDeleted) {
            items[index].key = key;
            items[index].value = value;
            items[index].isEmpty = false;
            items[index].isDeleted = false;
            size++;
            return true;
        }

        if (!items[index].isDeleted && items[index].key == key) {
            items[index].value = value;
            return true;
        }

        index = (index + 1) % capacity;
    } while (index != startIndex);

    return false;
}

bool HashTable::find(const std::string& key, std::string& value) const {
    int index = hashFunction(key);
    int startIndex = index;

    do {
        if (items[index].isEmpty && !items[index].isDeleted) {
            return false;
        }

        if (!items[index].isEmpty && !items[index].isDeleted &&
            items[index].key == key) {
            value = items[index].value;
            return true;
        }

        index = (index + 1) % capacity;
    } while (index != startIndex);

    return false;
}

bool HashTable::remove(const std::string& key) {
    int index = hashFunction(key);
    int startIndex = index;

    do {
        if (items[index].isEmpty && !items[index].isDeleted) {
            return false;
        }

        if (!items[index].isEmpty && !items[index].isDeleted &&
            items[index].key == key) {
            items[index].isDeleted = true;
            size--;
            return true;
        }

        index = (index + 1) % capacity;
    } while (index != startIndex);

    return false;
}

void HashTable::clear() {
    for (int i = 0; i < capacity; i++) {
        items[i] = HashItem();
    }
    size = 0;
}

void HashTable::getAllItems(std::vector<std::pair<std::string, std::string>>& result) const {
    result.clear();
    for (int i = 0; i < capacity; i++) {
        if (!items[i].isEmpty && !items[i].isDeleted) {
            result.emplace_back(items[i].key, items[i].value);
        }
    }
}

void HashTable::print() const {
    std::cout << "Хеш-таблица [" << size << "/" << capacity << "]: ";
    std::vector<std::pair<std::string, std::string>> allItems;
    getAllItems(allItems);
    
    if (allItems.empty()) {
        std::cout << "пуста" << std::endl;
        return;
    }
    
    for (size_t i = 0; i < allItems.size(); i++) {
        std::cout << "{" << allItems[i].first << ":" << allItems[i].second << "}";
        if (i < allItems.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}

std::vector<std::string> HashTable::serialize() const {
    std::vector<std::string> result;
    std::vector<std::pair<std::string, std::string>> allItems;
    getAllItems(allItems);
    
    for (const auto& item : allItems) {
        result.push_back(item.first + ":" + item.second);
    }
    return result;
}

void HashTable::deserialize(const std::vector<std::string>& data) {
    clear();
    for (const auto& item : data) {
        size_t pos = item.find(':');
        if (pos != std::string::npos) {
            std::string key = item.substr(0, pos);
            std::string value = item.substr(pos + 1);
            insert(key, value);
        }
    }
}

void HashTable::serializeBinary(std::ostream& os) const {
    std::vector<std::pair<std::string, std::string>> allItems;
    getAllItems(allItems);
    
    int itemCount = allItems.size();
    os.write(reinterpret_cast<const char*>(&itemCount), sizeof(itemCount));
    
    for (const auto& item : allItems) {
        int keyLen = item.first.length();
        os.write(reinterpret_cast<const char*>(&keyLen), sizeof(keyLen));
        os.write(item.first.c_str(), keyLen);
        
        int valueLen = item.second.length();
        os.write(reinterpret_cast<const char*>(&valueLen), sizeof(valueLen));
        os.write(item.second.c_str(), valueLen);
    }
}

void HashTable::deserializeBinary(std::istream& is) {
    clear();
    
    int itemCount;
    is.read(reinterpret_cast<char*>(&itemCount), sizeof(itemCount));
    
    for (int i = 0; i < itemCount; i++) {
        int keyLen;
        is.read(reinterpret_cast<char*>(&keyLen), sizeof(keyLen));
        
        char* keyBuffer = new char[keyLen + 1];
        is.read(keyBuffer, keyLen);
        keyBuffer[keyLen] = '\0';
        
        int valueLen;
        is.read(reinterpret_cast<char*>(&valueLen), sizeof(valueLen));
        
        char* valueBuffer = new char[valueLen + 1];
        is.read(valueBuffer, valueLen);
        valueBuffer[valueLen] = '\0';
        
        insert(std::string(keyBuffer), std::string(valueBuffer));
        
        delete[] keyBuffer;
        delete[] valueBuffer;
    }
}