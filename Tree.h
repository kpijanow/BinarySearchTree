#ifndef TREE_H
#define TREE_H

template <class t_Data>
class Tree {
public:
    virtual ~Tree() {};

    virtual void traversal() const = 0;
    virtual void insert(const t_Data& AData) = 0;
    virtual void remove(const t_Data& AData) = 0;

    virtual t_Data& getMaxValue() const = 0;
    virtual t_Data& getMinValue() const = 0;
};

#endif // TREE_H
