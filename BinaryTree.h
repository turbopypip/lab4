#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <cstddef>
#include <iostream>
#include <functional> // Для std::function
#include <stack>
#include <queue>

template<typename T>
struct TreeNode {
    T value;
    TreeNode* left;
    TreeNode* right;

    explicit TreeNode(const T& val) : value(val), left(nullptr), right(nullptr) {}


    ~TreeNode() {
        delete left;
        delete right;
    }

    TreeNode(const TreeNode& other) : value(other.value), left(nullptr), right(nullptr) {
        if (other.left) {
            left = new TreeNode(*other.left);
        }
        if (other.right) {
            right = new TreeNode(*other.right);
        }
    }

    TreeNode& operator=(const TreeNode& other) {
        if (this == &other) {
            return *this;
        }

        delete left;
        delete right;

        value = other.value;
        left = other.left ? new TreeNode(*other.left) : nullptr;
        right = other.right ? new TreeNode(*other.right) : nullptr;

        return *this;
    }

    void insertRecursive(TreeNode<T>* node, const T& value) {
        if (value < node->value) {
            if (node->left == nullptr) {
                node->left = new TreeNode<T>(value);
            } else {
                insertRecursive(node->left, value);
            }
        } else {
            if (node->right == nullptr) {
                node->right = new TreeNode<T>(value);
            } else {
                insertRecursive(node->right, value);
            }
        }
    }

    void klpTraversal(TreeNode<T>* node, std::function<void(const T&)> func) const {
        if (node != nullptr) {
            func(node->value);
            klpTraversal(node->left, func);
            klpTraversal(node->right, func);
        }
    }

    void klrTraversal(TreeNode<T>* node, std::function<void(const T&)> func) const {
        if (node != nullptr) {
            func(node->value);
            klrTraversal(node->right, func);
            klrTraversal(node->left, func);
        }
    }

    void lkpTraversal(TreeNode<T>* node, std::function<void(const T&)> func) const {
        if (node != nullptr) {
            lkpTraversal(node->left, func);
            func(node->value);
            lkpTraversal(node->right, func);
        }
    }

    void lpkTraversal(TreeNode<T>* node, std::function<void(const T&)> func) const {
        if (node != nullptr) {
            lpkTraversal(node->left, func);
            lpkTraversal(node->right, func);
            func(node->value);
        }
    }

    void plkTraversal(TreeNode<T>* node, std::function<void(const T&)> func) const {
        if (node != nullptr) {
            func(node->value);
            plkTraversal(node->left, func);
            plkTraversal(node->right, func);
        }
    }

    void pklTraversal(TreeNode<T>* node, std::function<void(const T&)> func) const {
        if (node != nullptr) {
            pklTraversal(node->right, func);
            pklTraversal(node->left, func);
            func(node->value);
        }
    }

    TreeNode<T>* whereRecursive(TreeNode<T>* node, std::function<bool(T)> pred) {
        if (node == nullptr) {
            return nullptr;
        }

        TreeNode<T>* leftFiltered = whereRecursive(node->left, pred);
        TreeNode<T>* rightFiltered = whereRecursive(node->right, pred);

        if (pred(node->value)) {
            auto* newNode = new TreeNode<T>(node->value);
            newNode->left = leftFiltered;
            newNode->right = rightFiltered;
            return newNode;
        } else {
            if (leftFiltered != nullptr) {
                if (rightFiltered != nullptr) {
                    TreeNode<T>* temp = leftFiltered;
                    while (temp->right != nullptr) {
                        temp = temp->right;
                    }
                    temp->right = rightFiltered;
                    return leftFiltered;
                }
                return leftFiltered;
            }
            return rightFiltered;
        }
    }

    bool containsSubtree(const TreeNode<T>* tree, const TreeNode<T>* subtree) const {
        if (tree == nullptr && subtree == nullptr)
            return true;
        if (tree == nullptr || subtree == nullptr)
            return false;
        return isEquals(tree, subtree) ||
               containsSubtree(tree->left, subtree) ||
               containsSubtree(tree->right, subtree);
    }

    bool isEquals(const TreeNode<T>* tree, const TreeNode<T>* subtree) const {
        if (tree == nullptr && subtree == nullptr)
            return true;
        if (tree == nullptr || subtree == nullptr)
            return false;
        return tree->value == subtree->value &&
               isEquals(tree->left, subtree->left) &&
               isEquals(tree->right, subtree->right);
    }

};

enum TraversalOrder {
    KLP = 1,
    LKP = 2,
    PLK = 3,
    KLR = 4,
    LPK = 5,
    PKL = 6
};

template<typename T>
class BinaryTree {
private:
    TreeNode<T>* root;

public:
    BinaryTree() : root(nullptr) {}

    BinaryTree(T* values, size_t count) : root(nullptr) {
        for (size_t i = 0; i < count; ++i) {
            insert(values[i]);
        }
    }

    explicit BinaryTree(TreeNode<T>* root) : root(root){}

    BinaryTree(const BinaryTree& other) : root(nullptr) {
        if (other.root != nullptr) {
            root = new TreeNode<T>(*other.root);
        }
    }

    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            clear();
            if (other.root != nullptr) {
                root = new TreeNode<T>(*other.root);
            }
        }
        return *this;
    }

    ~BinaryTree() {
        delete root;
    }

    [[nodiscard]] bool isEmpty() const {
        return root == nullptr;
    }

    void clear() {
        delete root;
        root = nullptr;
    }

    void insert(const T& value) {
        if (root == nullptr) {
            root = new TreeNode<T>(value);
        } else {
            root->insertRecursive(root, value);
        }
    }

    TreeNode<T>* bfsSearch(const T& target) const {
        if (root == nullptr) {
            return nullptr;
        }

        std::queue<TreeNode<T>*> nodeQueue;
        nodeQueue.push(root);

        while (!nodeQueue.empty()) {
            TreeNode<T>* current = nodeQueue.front();
            nodeQueue.pop();

            if (current->value == target) {
                return current;
            }

            if (current->left != nullptr) {
                nodeQueue.push(current->left);
            }
            if (current->right != nullptr) {
                nodeQueue.push(current->right);
            }
        }

        return nullptr;
    }

    void deleteNode(TreeNode<T>*& root, const T& value) {
        if (root == nullptr) {
            return;
        }

        if (value < root->value) {
            deleteNode(root->left, value);
        }
        else if (value > root->value) {
            deleteNode(root->right, value);
        }
        else {
            if (root->left == nullptr) {
                TreeNode<T>* temp = root->right;
                root->right = nullptr;
                delete root;
                root = temp;
            } else if (root->right == nullptr) {
                TreeNode<T>* temp = root->left;
                root->left = nullptr;
                delete root;
                root = temp;
            }
            else {
                TreeNode<T>* temp = minValueNode(root->right);
                root->value = temp->value;
                deleteNode(root->right, temp->value);
            }
        }
    }

    TreeNode<T>* minValueNode(TreeNode<T>* node) {
        TreeNode<T>* current = node;

        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void deleteValue(const T& value) {
        deleteNode(root, value);
    }


    // Traversals
    void klpTraversal(std::function<void(const T&)> func) const {
        root->klpTraversal(root, func);
    }

    void klrTraversal(std::function<void(const T&)> func) const {
        root->klrTraversal(root, func);
    }

    void lkpTraversal(std::function<void(const T&)> func) const {
        root->lkpTraversal(root, func);
    }

    void lpkTraversal(std::function<void(const T&)> func) const {
        root->lpkTraversal(root, func);
    }

    void plkTraversal(std::function<void(const T&)> func) const {
        root->plkTraversal(root, func);
    }

    void pklTraversal(std::function<void(const T&)> func) const {
        root->pklTraversal(root, func);
    }

    template<typename R>
    BinaryTree<R> map(std::function<R(T)> func) const {
        BinaryTree<R> result;
        if (root != nullptr) {
            result.root = new TreeNode<R>(func(root->value));
            std::stack<TreeNode<T>*> nodeStack;
            std::stack<TreeNode<R>*> resultStack;

            nodeStack.push(root);
            resultStack.push(result.root);

            while (!nodeStack.empty()) {
                TreeNode<T>* currentNode = nodeStack.top();
                TreeNode<R>* currentResultNode = resultStack.top();
                nodeStack.pop();
                resultStack.pop();

                if (currentNode->right != nullptr) {
                    nodeStack.push(currentNode->right);
                    currentResultNode->right = new TreeNode<R>(func(currentNode->right->value));
                    resultStack.push(currentResultNode->right);
                }

                if (currentNode->left != nullptr) {
                    nodeStack.push(currentNode->left);
                    currentResultNode->left = new TreeNode<R>(func(currentNode->left->value));
                    resultStack.push(currentResultNode->left);
                }
            }
        }
        return result;
    }


    BinaryTree<T> where(std::function<bool(T)> pred) {
        BinaryTree<T> result;
        TreeNode<T>* copy = root;
        result.root = root->whereRecursive(copy, pred);
        return result;
    }

    void mergeRecursive(TreeNode<T>* tree1, const TreeNode<T>* tree2) {
        if (tree2 == nullptr) {
            return;
        }
        tree1->insertRecursive(tree1, tree2->value);
        mergeRecursive(tree1, tree2->left);
        mergeRecursive(tree1, tree2->right);
    }

    BinaryTree<T>& merge(const BinaryTree<T>& tree2) {
        mergeRecursive(root, tree2.root);
        return *this;
    }

    BinaryTree<T> getSubtree(const T& value) const {
        TreeNode<T>* node = bfsSearch(value);
        if (node != nullptr) {
            return BinaryTree<T>(new TreeNode<T>(*node));
        } else {
            return BinaryTree<T>();
        }
    }

    bool containsSubtree(const BinaryTree<T>& subtree) const {
        return root->containsSubtree(root, subtree.root);
    }


    std::string saveToString(const BinaryTree<T>& tree, const int traversalOrder) {
        std::string result;
        switch (traversalOrder) {
            case KLP:
                tree.klpTraversal([&result](const T& value) { result += std::to_string(value); });
                break;
            case LKP:
                tree.lkpTraversal([&result](const T& value) { result += std::to_string(value); });
                break;
            case PLK:
                tree.plkTraversal([&result](const T& value) { result += std::to_string(value); });
                break;
            case KLR:
                tree.klrTraversal([&result](const T& value) { result += std::to_string(value); });
                break;
            case LPK:
                tree.lpkTraversal([&result](const T& value) { result += std::to_string(value); });
                break;
            case PKL:
                tree.pklTraversal([&result](const T& value) { result += std::to_string(value); });
                break;
            default:
                break;
        }
        return result;
    }


};

#endif // BINARYTREE_H