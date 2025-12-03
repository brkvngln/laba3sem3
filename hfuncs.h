#ifndef HFUNCS_H
#define HFUNCS_H

#include "common_types.h"
#include <iostream>
#include <string>
#include <vector>

class HashTable : public Serializable {
private:
    struct HashItem {
        std::string key;
        std::string value;
        bool isDeleted;
        bool isEmpty;

        HashItem() : key(""), value(""), isDeleted(false), isEmpty(true) {}
    };

    std::vector<HashItem> items;
    int capacity;
    int size;

    int hashFunction(const std::string& key) const;
    void rehash();

public:
    HashTable(int capacity = 10);
    ~HashTable();

    bool insert(const std::string& key, const std::string& value);
    bool find(const std::string& key, std::string& value) const;
    bool remove(const std::string& key);
    void clear();

    int getSize() const { return size; }
    int getCapacity() const { return capacity; }
    bool empty() const { return size == 0; }

    void getAllItems(std::vector<std::pair<std::string, std::string>>& result) const;
    
    void print() const;

    std::vector<std::string> serialize() const override;
    void deserialize(const std::vector<std::string>& data) override;
    
    void serializeBinary(std::ostream& os) const override;
    void deserializeBinary(std::istream& is) override;
};

#endif