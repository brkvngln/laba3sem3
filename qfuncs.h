#ifndef QFUNCS_H
#define QFUNCS_H

#include "common_types.h"
#include <vector>
#include <string>

class Queue : public Serializable {
private:
    QNode* front;
    QNode* rear;

public:
    Queue();
    ~Queue();

    void push(const std::string& value);
    std::string pop();
    std::string getFront() const;
    std::string getRear() const;
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