#ifndef TFUNCS_H
#define TFUNCS_H

#include "common_types.h"
#include <vector>
#include <string>

class AVLTree : public Serializable {
private:
    TreeNode* root;

    int getHeight(TreeNode* node) const;
    int getBalance(TreeNode* node) const;
    TreeNode* rightRotate(TreeNode* y);
    TreeNode* leftRotate(TreeNode* x);
    TreeNode* insertNode(TreeNode* node, int value);
    TreeNode* deleteNode(TreeNode* node, int value);
    TreeNode* minValueNode(TreeNode* node) const;
    bool searchNode(TreeNode* node, int value) const;
    void inOrderTraversal(TreeNode* node) const;
    void preOrderTraversal(TreeNode* node) const;
    void postOrderTraversal(TreeNode* node) const;
    int countNodes(TreeNode* node) const;
    int findMin(TreeNode* node) const;
    int findMax(TreeNode* node) const;
    void freeTree(TreeNode* node);
    void inOrderCollect(TreeNode* node, std::vector<int>& result) const;
    void preOrderCollect(TreeNode* node, std::vector<int>& result) const;

public:
    AVLTree();
    ~AVLTree();

    void insert(int value);
    bool search(int value) const;
    void remove(int value);
    bool empty() const;
    int size() const;
    int height() const;
    void printInOrder() const;
    void printPreOrder() const;
    void printPostOrder() const;
    int Min();
    int Max();
    
    std::vector<std::string> serialize() const override;
    void deserialize(const std::vector<std::string>& data) override;
    
    void serializeBinary(std::ostream& os) const override;
    void deserializeBinary(std::istream& is) override;

    TreeNode* getRoot() const { return root; }
};

#endif