#include <cstddef>
using namespace std;

template <typename Type>
class DynamicArray{
private:
    Type* data;
    size_t allocated;
    size_t used;

public:
    DynamicArray();
    DynamicArray(size_t);
    DynamicArray(const DynamicArray<Type>&);
    DynamicArray<Type>& operator=(const DynamicArray<Type>&);
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
    void swap(DynamicArray&);

    //https://en.cppreference.com/w/cpp/container/vector/resize
    void resize(size_t, Type value = Type());
    //https://en.cppreference.com/w/cpp/container/vector/reserve
    void reserve(size_t);
    //https://en.cppreference.com/w/cpp/container/vector/shrink_to_fit
    void shrink_to_fit();
};