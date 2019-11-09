#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <memory>
#include "CustomExceptions.h"
#include "Tree.h"

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <class t_Data>
class BinarySearchTree : public Tree<t_Data>
{
public:
    BinarySearchTree() {}
    ~BinarySearchTree() override {}

    struct Node {
        t_Data m_Data;
        std::unique_ptr<Node> m_Left;
        std::unique_ptr<Node> m_Right;

        Node(const t_Data& data) : m_Data(data) {

        }
    };

    std::unique_ptr<Node> root;

    void traversal() const override {
        if (!root)
            return;

        inOrderTraversal(root.get());
    }
    void insert(const t_Data& AData) override {
        if (root)
            insertNode(AData, root.get());
        else
            root = make_unique<Node>(AData);
    }

    void insertNode(const t_Data& AData, Node* ANode) {
        if (AData < ANode->m_Data) {
            if (ANode->m_Left)
                insertNode(AData, ANode->m_Left.get());
            else
                ANode->m_Left = make_unique<Node>(AData);
        }
        else {
            if (ANode->m_Right)
                insertNode(AData, ANode->m_Right.get());
            else
                ANode->m_Right = make_unique<Node>(AData);
        }
    }

    void inOrderTraversal(Node* ANode) const {
        if (ANode->m_Left)
            inOrderTraversal(ANode->m_Left.get());

        std::cout << ANode->m_Data << std::endl;

        if (ANode->m_Right)
            inOrderTraversal(ANode->m_Right.get());
    }

    void remove(const t_Data& AData) override {
        if (!root)
            return;

        remove(AData, root);
    }

    std::unique_ptr<Node> detchRightMost(std::unique_ptr<Node>& ANode) {
        if (ANode->m_Right)
            return detchRightMost(ANode->m_Right);

        return std::move(ANode);
    }

    std::unique_ptr<Node>& getLeftMost(std::unique_ptr<Node>& ANode) {
        if (ANode->m_Left)
            return getLeftMost(ANode->m_Left);

        return ANode;
    }

    void remove(const t_Data &AData, std::unique_ptr<Node>& ANode) {
        if (AData < ANode->m_Data) {
            if (ANode->m_Left)
                remove(AData, ANode->m_Left);
        }
        else if (AData > ANode->m_Data) {
            if (ANode->m_Right)
                remove(AData, ANode->m_Right);
        }
        else {
            if (!ANode->m_Left && !ANode->m_Right) {
                ANode.reset();
                return;
            }

            if (!ANode->m_Left) {
                std::unique_ptr<Node> tmp = std::move(ANode->m_Right);
                ANode.reset();
                ANode = std::move(tmp);
                return;
            }

            if (!ANode->m_Right) {
                std::unique_ptr<Node> tmp = std::move(ANode->m_Left);
                ANode.reset();
                ANode = std::move(tmp);
                return;
            }

            std::unique_ptr<Node> tmp = detchRightMost(ANode->m_Left);
            tmp->m_Right = std::move(ANode->m_Right);
            std::unique_ptr<Node>& tmpLeftMost = getLeftMost(tmp);
            tmpLeftMost->m_Left = std::move(ANode->m_Left);

            ANode.reset();
            ANode = std::move(tmp);
        }
    }

    t_Data& getMaxValue() const override {
        if (!root)
            throw EmptyTreeException();

        return getMin(root.get());
    }

    t_Data& getMinValue() const override {
        if (!root)
            throw EmptyTreeException();

        return getMax(root.get());
    }

    t_Data& getMin(Node* ANode) const {
        if (ANode->m_Left)
            return getMin(ANode->m_Left.get());

        return ANode->m_Data;
    }

    t_Data& getMax(Node* ANode) const {
        if (ANode->m_Right)
            return getMax(ANode->m_Right.get());

        return ANode->m_Data;
    }
};

#endif // BINARYSEARCHTREE_H
