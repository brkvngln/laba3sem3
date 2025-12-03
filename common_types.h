#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <string>
#include <vector>
#include <iostream>

struct FNode {
    std::string key;
    FNode* next;

    FNode() : key(""), next(nullptr) {}
    FNode(const std::string& k) : key(k), next(nullptr) {}
};

struct LNode {
    std::string key;
    LNode* next;
    LNode* prev;

    LNode() : key(""), next(nullptr), prev(nullptr) {}
    LNode(const std::string& k) : key(k), next(nullptr), prev(nullptr) {}
};

struct QNode {
    std::string data;
    QNode* next;

    QNode() : data(""), next(nullptr) {}
    QNode(const std::string& d) : data(d), next(nullptr) {}
};

struct SNode {
    std::string data;
    SNode* next;

    SNode() : data(""), next(nullptr) {}
    SNode(const std::string& d) : data(d), next(nullptr) {}
};

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

struct HashItem {
    std::string key;
    std::string value;
    bool isDeleted;
    bool isEmpty;

    HashItem() : key(""), value(""), isDeleted(false), isEmpty(true) {}
};

class Serializable {
public:
    virtual ~Serializable() {}
    
    virtual std::vector<std::string> serialize() const = 0;
    virtual void deserialize(const std::vector<std::string>& data) = 0;
    
    virtual void serializeBinary(std::ostream& os) const = 0;
    virtual void deserializeBinary(std::istream& is) = 0;
};

extern std::string M_FILE;
extern std::string F_FILE;
extern std::string L_FILE;
extern std::string Q_FILE;
extern std::string S_FILE;
extern std::string T_FILE;
extern std::string H_FILE;

#endif