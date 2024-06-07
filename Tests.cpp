#include <iostream>
#include <cassert>
#include "BinaryTree.h"

// Test function to print values
void printValue(const int& value) {
    std::cout << value << " ";
}

// Test function for map
int doubleValue(int value) {
    return value * 2;
}

// Test function for where
bool isEven(int value) {
    return value % 2 == 0;
}

void testInsertAndTraversal() {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    std::cout << "Traversal LKP: ";
    tree.lkpTraversal(printValue);

    std::string inorderTraversal = tree.saveToString(tree, LKP);
    assert(inorderTraversal == "2345678");
}

void testBfsSearch() {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    TreeNode<int>* foundNode = tree.bfsSearch(4);
    assert(foundNode != nullptr && foundNode->value == 4);

    foundNode = tree.bfsSearch(10);
    assert(foundNode == nullptr);
    std::cout << std::endl;
}

void testMap() {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    BinaryTree<int> mappedTree = tree.map<int>(doubleValue);
    std::cout << "Mapped tree (values doubled, LKP): ";
    mappedTree.lkpTraversal(printValue);
    std::cout << std::endl;

    // Expected output: 4 6 8 10 12 14 16
    std::string mappedTraversal = mappedTree.saveToString(mappedTree, LKP);
    assert(mappedTraversal == "46810121416");
}

void testWhere() {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    BinaryTree<int> filteredTree = tree.where(isEven);
    std::cout << "Filtered tree (even values, LKP): ";
    filteredTree.lkpTraversal(printValue);
    std::cout << std::endl;

    // Expected output: 2 4 6 8
    std::string filteredTraversal = filteredTree.saveToString(filteredTree, LKP);
    assert(filteredTraversal == "2468");
}

void testMerge() {
    int values1[] = {1, 2, 3};
    int values2[] = {4, 5, 6};
    BinaryTree<int> tree1(values1, 3);
    BinaryTree<int> tree2(values2, 3);

    BinaryTree<int> mergedTree = tree1.merge(tree2);
    std::cout << "Merged tree (LKP): ";
    mergedTree.lkpTraversal(printValue);
    std::cout << std::endl;

    // Expected output: 1 2 3 4 5 6
    std::string mergedTraversal = mergedTree.saveToString(mergedTree, LKP);
    assert(mergedTraversal == "123456");
}

void testGetSubtree() {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    BinaryTree<int> subtree = tree.getSubtree(3);
    std::cout << "Subtree (root 3, LKP): ";
    subtree.lkpTraversal(printValue);
    std::cout << std::endl;

    // Expected output: 2 3 4
    std::string subtreeTraversal = subtree.saveToString(subtree, LKP);
    assert(subtreeTraversal == "234");
}

void testContainsSubtree() {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    BinaryTree<int> subtree = tree.getSubtree(3);
    assert(tree.containsSubtree(subtree));
}

void runTests() {
    testInsertAndTraversal();
    testBfsSearch();
    testMap();
    testWhere();
    testMerge();
    testGetSubtree();
    testContainsSubtree();

    std::cout << "All tests passed!" << std::endl;
}
