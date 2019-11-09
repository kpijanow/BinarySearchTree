#ifndef CUSTOMEXCEPTIONS_H
#define CUSTOMEXCEPTIONS_H

#include <iostream>
#include <exception>

class EmptyTreeException : std::exception
{
public:
    EmptyTreeException() {}

    const char* what() const noexcept override {
        return "The tree is empty";
    }
};

#endif // CUSTOMEXCEPTIONS_H
