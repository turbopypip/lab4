#include <iostream>
#include "BinaryTree.h"

BinaryTree<int> tree;

void PrintBaseMenu() {
    std::cout << "\n***Menu***\n"
                 "1. Add element\n"
                 "2. Search element\n"
                 "3. Remove element\n"
                 "4. Display tree\n"
                 "5. Extract subtree\n"
                 "6. Exit\n";
}

void runMenu() {
    int option;
    while (true) {
        PrintBaseMenu();
        std::cout << "Choose a variant: ";
        std::cin >> option;

        switch (option) {
            case 1: {
                int value;
                std::cout << "Enter the value to add: ";
                std::cin >> value;
                tree.insert(value);
                std::cout << "Element added successfully.\n";
                break;
            }
            case 2: {
                int value;
                std::cout << "Enter the value to search: ";
                std::cin >> value;
                TreeNode<int>* found = tree.bfsSearch(value);
                if (found != nullptr) {
                    std::cout << "Element found in the tree.\n";
                } else {
                    std::cout << "Element not found.\n";
                }
                break;
            }
            case 3: {
                int value;
                std::cout << "Enter the value to remove: ";
                std::cin >> value;
                TreeNode<int>* found = tree.bfsSearch(value);
                if (found == nullptr) {
                    std::cout << "There is no such element in the tree.\n";
                    break;
                } else {
                    tree.deleteValue(value);
                    std::cout << "Element removed successfully.\n";
                }
                break;
            }
            case 4: {
                int order;
                std::cout << "Enter the traversal order (1 - KLP, 2 - LKP, 3 - PLK, 4 - KLR, 5 - LPK, 6 - PKL): ";
                std::cin >> order;
                while (order < 1 || order > 6) {
                    std::cout << "Invalid input. Enter the traversal order (1 - KLP, 2 - LKP, 3 - PLK, 4 - KLR, 5 - LPK, 6 - PKL): ";
                    std::cin >> order;
                }
                switch (order) {
                    case KLP:
                        tree.klpTraversal([](const int& value) { std::cout << value << " "; });
                        break;
                    case LKP:
                        tree.lkpTraversal([](const int& value) { std::cout << value << " "; });
                        break;
                    case PLK:
                        tree.plkTraversal([](const int& value) { std::cout << value << " "; });
                        break;
                    case KLR:
                        tree.klrTraversal([](const int& value) { std::cout << value << " "; });
                        break;
                    case LPK:
                        tree.lkpTraversal([](const int& value) { std::cout << value << " "; });
                        break;
                    case PKL:
                        tree.plkTraversal([](const int& value) { std::cout << value << " "; });
                        break;
                    default:
                        std::cout << "Invalid traversal order!\n";
                }
                break;
            }
            case 5: {
                int value;
                std::cout << "Enter the value to extract subtree: ";
                std::cin >> value;
                BinaryTree<int> subtreeRoot = tree.getSubtree(value);
                if (subtreeRoot.isEmpty()) {
                    std::cout << "There is no such element in the tree.\n";
                    break;
                } else {
                    std::cout << "Subtree extracted successfully.\n";
                    tree.lkpTraversal([](const int& value) { std::cout << value << " "; });
                    break;
                }
            }
            case 6: {
                std::cout << "Exiting...\n";
                return;
            }
            default: {
                std::cout << "Invalid option. Please choose another.\n";
                break;
            }
        }
    }
}