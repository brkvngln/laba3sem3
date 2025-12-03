#include "tfuncs.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

AVLTree::AVLTree() : root(nullptr) {}
AVLTree::~AVLTree() { freeTree(root); }

int AVLTree::Min() {
    return findMin(root);
}

int AVLTree::Max() {
    return findMax(root);
}

int AVLTree::getHeight(TreeNode* node) const {
    return node ? node->height : 0;
}

int AVLTree::getBalance(TreeNode* node) const {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

TreeNode* AVLTree::rightRotate(TreeNode* y) {
    if (!y || !y->left) return y;

    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

TreeNode* AVLTree::leftRotate(TreeNode* x) {
    if (!x || !x->right) return x;

    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

TreeNode* AVLTree::insertNode(TreeNode* node, int value) {
    if (!node) return new TreeNode(value);

    if (value < node->data)
        node->left = insertNode(node->left, value);
    else if (value > node->data)
        node->right = insertNode(node->right, value);
    else
        return node;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && value < node->left->data)
        return rightRotate(node);

    if (balance < -1 && value > node->right->data)
        return leftRotate(node);

    if (balance > 1 && value > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && value < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

TreeNode* AVLTree::deleteNode(TreeNode* node, int value) {
    if (!node) return node;

    if (value < node->data)
        node->left = deleteNode(node->left, value);
    else if (value > node->data)
        node->right = deleteNode(node->right, value);
    else {
        if (!node->left || !node->right) {
            TreeNode* temp = node->left ? node->left : node->right;

            if (!temp) {
                temp = node;
                node = nullptr;
            }
            else {
                *node = *temp;
            }
            delete temp;
        }
        else {
            TreeNode* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
    }

    if (!node) return node;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

TreeNode* AVLTree::minValueNode(TreeNode* node) const {
    if (!node) return nullptr;

    TreeNode* current = node;
    while (current->left)
        current = current->left;
    return current;
}

bool AVLTree::searchNode(TreeNode* node, int value) const {
    if (!node) return false;
    if (value == node->data) return true;
    if (value < node->data)
        return searchNode(node->left, value);
    else
        return searchNode(node->right, value);
}

void AVLTree::inOrderTraversal(TreeNode* node) const {
    if (node) {
        inOrderTraversal(node->left);
        std::cout << node->data << " ";
        inOrderTraversal(node->right);
    }
}

void AVLTree::preOrderTraversal(TreeNode* node) const {
    if (node) {
        std::cout << node->data << " ";
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }
}

void AVLTree::postOrderTraversal(TreeNode* node) const {
    if (node) {
        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        std::cout << node->data << " ";
    }
}

int AVLTree::countNodes(TreeNode* node) const {
    return node ? 1 + countNodes(node->left) + countNodes(node->right) : 0;
}

int AVLTree::findMin(TreeNode* node) const {
    if (!node) return -1;
    while (node->left) node = node->left;
    return node->data;
}

int AVLTree::findMax(TreeNode* node) const {
    if (!node) return -1;
    while (node->right) node = node->right;
    return node->data;
}

void AVLTree::freeTree(TreeNode* node) {
    if (node) {
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }
}

void AVLTree::inOrderCollect(TreeNode* node, std::vector<int>& result) const {
    if (node) {
        inOrderCollect(node->left, result);
        result.push_back(node->data);
        inOrderCollect(node->right, result);
    }
}

void AVLTree::preOrderCollect(TreeNode* node, std::vector<int>& result) const {
    if (node) {
        result.push_back(node->data);
        preOrderCollect(node->left, result);
        preOrderCollect(node->right, result);
    }
}

void AVLTree::insert(int value) {
    root = insertNode(root, value);
}

bool AVLTree::search(int value) const {
    return searchNode(root, value);
}

void AVLTree::remove(int value) {
    root = deleteNode(root, value);
}

bool AVLTree::empty() const {
    return root == nullptr;
}

int AVLTree::size() const {
    return countNodes(root);
}

int AVLTree::height() const {
    return getHeight(root);
}

void AVLTree::printInOrder() const {
    if (root) {
        inOrderTraversal(root);
        std::cout << std::endl;
    }
    else {
        std::cout << "Дерево пусто" << std::endl;
    }
}

void AVLTree::printPreOrder() const {
    if (root) {
        preOrderTraversal(root);
        std::cout << std::endl;
    }
    else {
        std::cout << "Дерево пусто" << std::endl;
    }
}

void AVLTree::printPostOrder() const {
    if (root) {
        postOrderTraversal(root);
        std::cout << std::endl;
    }
    else {
        std::cout << "Дерево пусто" << std::endl;
    }
}

std::vector<std::string> AVLTree::serialize() const {
    std::vector<std::string> result;
    std::vector<int> data;
    inOrderCollect(root, data);
    for (int value : data) {
        result.push_back(std::to_string(value));
    }
    return result;
}

void AVLTree::deserialize(const std::vector<std::string>& data) {
    freeTree(root);
    root = nullptr;
    for (const auto& item : data) {
        try {
            int value = std::stoi(item);
            insert(value);
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка десериализации: " << e.what() << std::endl;
        }
    }
}

void AVLTree::serializeBinary(std::ostream& os) const {
    int treeSize = size();
    os.write(reinterpret_cast<const char*>(&treeSize), sizeof(treeSize));
    
    std::vector<int> data;
    preOrderCollect(root, data);
    
    for (int value : data) {
        os.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
}

void AVLTree::deserializeBinary(std::istream& is) {
    freeTree(root);
    root = nullptr;
    
    int size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    for (int i = 0; i < size; i++) {
        int value;
        is.read(reinterpret_cast<char*>(&value), sizeof(value));
        insert(value);
    }
}