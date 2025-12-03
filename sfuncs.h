#ifndef SFUNCS_H
#define SFUNCS_H

#include "common_types.h"
#include <vector>
#include <string>

class Stack : public Serializable {
private:
    SNode* top;

public:
    Stack();
    ~Stack();

    void push(const std::string& value);
    std::string pop();
    std::string getTop() const;
    bool empty() const;
    int size() const;
    void print() const;
    void clear();
    
    std::vector<std::string> serialize() const override;
    void deserialize(const std::vector<std::string>& data) override;
    
    void serializeBinary(std::ostream& os) const override;
    void deserializeBinary(std::istream& is) override;
};

#endif