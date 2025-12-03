#ifndef LFUNCS_H
#define LFUNCS_H

#include "common_types.h"
#include <vector>
#include <string>

class DoublyLinkedList : public Serializable {
private:
    LNode* head;
    LNode* tail;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void pushFront(const std::string& key);
    void pushBack(const std::string& key);
    void addAfter(LNode* node, const std::string& key);
    void addBefore(LNode* node, const std::string& key);
    void popFront();
    void popBack();
    void delAfter(LNode* node);
    void delBefore(LNode* node);
    void delByKey(const std::string& key);

    LNode* find(const std::string& key) const;
    std::string getAt(int index) const;
    void print() const;
    void printReverse() const;
    int getSize() const;
    void clear();
    
    LNode* getHead() const { return head; }
    LNode* getTail() const { return tail; }

    std::vector<std::string> serialize() const override;
    void deserialize(const std::vector<std::string>& data) override;
    
    void serializeBinary(std::ostream& os) const override;
    void deserializeBinary(std::istream& is) override;
};

#endif