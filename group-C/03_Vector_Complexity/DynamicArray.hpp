#pragma once

#include <stdexcept>
#include <cassert>

template <class Type>
class Allocator {
public:
    Type* allocate(size_t size)
    {
        Type* ptr = new Type[size];
        return ptr;
    }

    void deallocate(Type* ptr)
    {
        delete []ptr;
    }
};

template <class Type, class Alloc = Allocator<Type>>
class DynamicArray{
protected:
    Alloc alloc;

    Type* data;
    size_t allocated;
    size_t used;

    void resize_data();
    void resize_data(size_t);

public:
    DynamicArray();
    DynamicArray(size_t);
    DynamicArray(const DynamicArray<Type, Alloc>&);
    DynamicArray<Type, Alloc>& operator=(const DynamicArray<Type, Alloc>&);
    ~DynamicArray();

public:
    void push_back(const Type&);
    void pop_back();

    Type& at(size_t);
    const Type& at(size_t)const;

    Type& operator[](size_t);
    const Type& operator[](size_t)const;

    Type& front();
    const Type& front()const;

    Type& back();
    const Type& back()const;

    size_t size()const;
    size_t capacity()const;
    bool empty()const;

    void clear();
    void swap(DynamicArray<Type, Alloc>&);

    //https://en.cppreference.com/w/cpp/container/vector/resize
    void resize(size_t, Type value = Type());
    //https://en.cppreference.com/w/cpp/container/vector/reserve
    void reserve(size_t);
    //https://en.cppreference.com/w/cpp/container/vector/shrink_to_fit
    void shrink_to_fit();
};

template <class Type, class Alloc>
void DynamicArray<Type, Alloc>::resize_data()
{
    resize(allocated*2);
}

template <class Type, class Alloc>
void DynamicArray<Type, Alloc>::resize_data(size_t size)
{   
    DynamicArray<Type, Alloc> new_array(size);

    size_t used_new_array = used < size ? used : size;

    for(size_t i = 0; i < used_new_array; ++i)
        new_array.push_back(data[i]);

    this->swap(new_array);
}

template <class Type, class Alloc>
DynamicArray<Type, Alloc>::DynamicArray() : DynamicArray(4)
{

}

template <class Type, class Alloc>
DynamicArray<Type, Alloc>::DynamicArray(size_t size)
    : alloc(),
      data(alloc.allocate(size)),
      allocated(size),
      used(0)
{

}

template <class Type, class Alloc>
DynamicArray<Type, Alloc>::DynamicArray(const DynamicArray<Type, Alloc>& other)
    : alloc(),
      data(alloc.allocate(other.size)),
      allocated(other.allocated),
      used(other.used)
{
    for(size_t i = 0; i < used; ++i)
        data[i] = other.data[i];
}

template <class Type, class Alloc>
DynamicArray<Type, Alloc>& DynamicArray<Type, Alloc>::operator=(const DynamicArray<Type, Alloc>& other)
{
    if(this != &other)
    {
        DynamicArray<Type, Alloc> copy(other);
        this->swap(other);
    }
    return *this;
}

template <class Type, class Alloc>
DynamicArray<Type, Alloc>::~DynamicArray()
{
    alloc.deallocate(data);
}

template <class Type, class Alloc>
void DynamicArray<Type, Alloc>::push_back(const Type& value)
{   
    if(allocated >= used)
        resize_data();

    data[used++] = value;
}

template <class Type, class Alloc>
void DynamicArray<Type, Alloc>::pop_back()
{   
    if(used > 0)
        --used;
}

template <class Type, class Alloc>
Type& DynamicArray<Type, Alloc>::at(size_t index)
{
    if(index < used)
        return data[index];
    throw std::out_of_range("The index is out of range!");
}

template <class Type, class Alloc>
const Type& DynamicArray<Type, Alloc>::at(size_t index) const
{
    if(index < used)
        return data[index];
    throw std::out_of_range("The index is out of range!");
}

template <class Type, class Alloc>
Type& DynamicArray<Type, Alloc>::operator[](size_t index)
{
    assert(index < used);
    return data[index];
}

template <class Type, class Alloc>
const Type& DynamicArray<Type, Alloc>::operator[](size_t index) const
{
    assert(index < used);
    return data[index];
}

template <class Type, class Alloc>
Type& DynamicArray<Type, Alloc>::front()
{
    if(!empty())
        return data[0];
    throw std::out_of_range("The array is empty!");
}

template <class Type, class Alloc>
const Type& DynamicArray<Type, Alloc>::front() const
{
    if(!empty())
        return data[0];
    throw std::out_of_range("The array is empty!");
}

template <class Type, class Alloc>
Type& DynamicArray<Type, Alloc>::back()
{
    if(!empty())
        return data[used - 1];
    throw std::out_of_range("The array is empty!");
}

template <class Type, class Alloc>
const Type& DynamicArray<Type, Alloc>::back() const
{
    if(!empty())
        return data[used - 1];
    throw std::out_of_range("The array is empty!");
}

template <class Type, class Alloc>
size_t DynamicArray<Type, Alloc>::size()const
{
    return used;
}

template <class Type, class Alloc>
size_t DynamicArray<Type, Alloc>::capacity()const
{
    return allocated;
}

template <class Type, class Alloc>
bool DynamicArray<Type, Alloc>::empty()const
{
    return used == 0;
}

template <class Type, class Alloc>
void DynamicArray<Type, Alloc>::clear()
{
    used = 0;
}

template <class Type, class Alloc>
void DynamicArray<Type, Alloc>::swap(DynamicArray<Type, Alloc>& other)
{
    if(this != &other)
    {
        std::swap(data, other.data);
        std::swap(used, other.used);
        std::swap(allocated, other.allocated);
    }
}

template <class Type, class Alloc>
void DynamicArray<Type, Alloc>::resize(size_t size, Type value)
{
    if(size == allocated)
        return;

    resize_data(size);

    for(size_t i = 0; i < size - used; ++i)
        push_back(value);
}

template <class Type, class Alloc>
void DynamicArray<Type, Alloc>::reserve(size_t size)
{
    if(size <= allocated)
        return;
    
    size = size > allocated*2 ? size : allocated*2;

    resize_data(size);
}

template <class Type, class Alloc>
void DynamicArray<Type, Alloc>::shrink_to_fit()
{
    if(!empty() && used < allocated)
    {
        resize_data(used);
    }
}