#include <iostream>

template <typename T>
class Pointer
{
public:
    // Ro3
    Pointer(T value) : pointer_to_value{new T(value)} {}
    ~Pointer()
    {
        delete pointer_to_value;
    }
    Pointer(const Pointer<T> &other)
    {
        pointer_to_value = new T(other.pointer_to_value);
    }
    // copy-and-swap
    Pointer &operator=(const Pointer<T> &other)
    {
        Pointer cpy = Pointer<T>(other);
        pointer_to_value = cpy.pointer_to_value;
    }

    T &operator*() const
    {
        return *pointer_to_value;
    }

    T *operator->() const
    {
        return pointer_to_value;
    }

private:
    T *pointer_to_value;
};

struct IntTuple
{
    int a;
    int b;
};

// GOOD
using IntPointer = Pointer<int>;

// BAD - readability issues
typedef Pointer<double> DoublePointer;

int main()
{
    Pointer<int> p1{3};
    std::cout << *p1 << std::endl; // 3

    IntTuple obj{2, 3};
    Pointer<IntTuple> p2{obj};
    std::cout << p2->a << std::endl; // 2
    return 0;
}