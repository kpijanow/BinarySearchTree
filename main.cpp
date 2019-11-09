#include <iostream>
#include <memory>
#include "BinarySearchTree.h"

int main(int argc, char *argv[])
{
    std::shared_ptr<Tree<int>> tree = std::make_shared<BinarySearchTree<int>>();
    tree->insert(0);
    tree->insert(5);
    tree->insert(65);
    tree->insert(2);
    tree->insert(34);
    tree->insert(7);
    tree->insert(21);

    tree->traversal();

    std::cout << "-----------" << std::endl;

    tree->remove(5);

    tree->traversal();

    return 0;
}

