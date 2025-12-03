#ifndef FFUNCS_H
#define FFUNCS_H

#include "common_types.h"
#include <vector>
#include <string>

class ForwardList : public Serializable {
private:
    FNode* head;

public:
    ForwardList();
    ~ForwardList();

    void pushFront(const std::string& key);
    void pushBack(const std::string& key);
    void addAfter(FNode* node, const std::string& key);
    void delAfter(FNode* node);
    void addBefore(FNode* node, const std::string& key);
    void delBefore(FNode* node);
    void popFront();
    void delByKey(const std::string& key);

    FNode* find(const std::string& key) const;
    std::string getAt(int index) const;
    void print() const;
    int getSize() const;
    void clear();
    
    FNode* getHead() const { return head; }
    
    std::vector<std::string> serialize() const override;
    void deserialize(const std::vector<std::string>& data) override;
    
    void serializeBinary(std::ostream& os) const override;
    void deserializeBinary(std::istream& is) override;
};

#endif