#pragma once 

#include <vector>

template <class Type, class Container = std::vector<Type>>
class Stack{
private:
    Container container;

public:

    Type& top();
    const Type& top()const;

    size_t size()const;
    bool empty()const;

    void push(const Type&);
    void pop();

    void swap(Stack<Type, Container>&);
};

template <class Type, class Container>
Type& Stack<Type, Container>::top()
{
    return container.back();
}

template <class Type, class Container>
const Type& Stack<Type, Container>::top()const
{
    if(container.empty())
        throw std::exception();

    return container[container.size() - 1];
}

template <class Type, class Container>
size_t Stack<Type, Container>::size()const
{
    return container.size();
}

template <class Type, class Container>
bool Stack<Type, Container>::empty()const
{
    return container.empty();
}

template <class Type, class Container>
void Stack<Type, Container>::push(const Type& val)
{
    container.push_back(val);
}

template <class Type, class Container>
void Stack<Type, Container>::pop()
{
    container.pop_back(val);
}

template <class Type, class Container>
void Stack<Type, Container>::swap(Stack<Type, Container>& other)
{
    container.swap(other);
}