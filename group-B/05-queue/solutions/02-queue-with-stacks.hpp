#pragma once
#include <stack>
#include <stdexcept>

template<class T>
class QueueWith2Stacks
{
public:
    void enqueue( const T& elem )
    {
        fLeftStack.push( elem );
    }

    T dequeue()
    {
        if ( fLeftStack.empty() )
            throw std::logic_error( "Queue2Stacks: Called .dequeue() on an empty queue!" );

        // Move all elements from fLeftStack to fRightStack
        while ( fLeftStack.size() > 1 )
        {
            fRightStack.push( fLeftStack.top() );
            fLeftStack.pop();
        }

        // Save the last element
        T   resElem     = fLeftStack.top();
        fLeftStack.pop();

        // Put everything back into fLeftStack
        while ( ! fRightStack.empty() )
        {
            fLeftStack.push( fRightStack.top() );
            fRightStack.pop();
        }

        return resElem;
    }

    bool empty() const
    {
        return fLeftStack.empty();
    }

private:
    std::stack<T>   fLeftStack;
    std::stack<T>   fRightStack;
};

//------------------------------------------------------------------------------
template<class T>
class QueueWith1Stack
{
public:
    void enqueue( const T& elem )
    {
        fStack.push( elem );
    }

    T dequeue()
    {
        if ( fStack.empty() )
            throw std::logic_error( "Queue1Stack: Called .dequeue() on an empty queue!" );

        // Base case: Only one element - return it
        if ( fStack.size() == 1 )
        {
            T   resElem     = fStack.top();
            fStack.pop();

            return resElem;
        }

        // General case: More than one element - save the top element
        T   savedElem   = fStack.top();
        fStack.pop();

        // Call dequeue() on the rest of the element - save the result
        T   resElem     = this->dequeue();

        // Return the saved element back in the stack
        fStack.push( savedElem );

        return resElem;
    }

    bool empty() const
    {
        return fStack.empty();
    }

private:
    std::stack<T>   fStack;
};
