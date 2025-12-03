#ifndef MFUNCS_H
#define MFUNCS_H

#include "common_types.h"
#include <vector>
#include <string>

class DynamicArray : public Serializable {
private:
    std::string* data;
    int size;
    int capacity;

    void ensureCapacity(int requiredSize);

public:
    DynamicArray(int initialCapacity = 10);
    ~DynamicArray();

    void pushBack(const std::string& value);
    void insert(int index, const std::string& value);
    void remove(int index);
    void set(int index, const std::string& value);

    std::string get(int index) const;
    int getSize() const;
    int getCapacity() const;
    int find(const std::string& value) const;

    void clear();
    void print() const;
    
    std::vector<std::string> serialize() const override;
    void deserialize(const std::vector<std::string>& data) override;
    
    void serializeBinary(std::ostream& os) const override;
    void deserializeBinary(std::istream& is) override;
};

#endif