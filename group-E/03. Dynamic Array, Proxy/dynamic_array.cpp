#include <unordered_set>
#include <stdexcept>
#include <iostream>

template <typename T>
class Allocator
{
public:
    T *allocate(size_t size)
    {
        return new T[size];
    }
    void free(T *arr)
    {
        delete[] arr;
    }
};

template <typename T>
class DebugAllocator
{
    std::unordered_set<T *> allocations{};

public:
    T *allocate(size_t size)
    {
        T *arr = new T[size];
        allocations.insert(arr);
        return arr;
    }
    void free(T *arr)
    {
        if (allocations.count(arr) != 1)
            throw std::invalid_argument("arr is not allocated by this instance");

        allocations.erase(arr);
        delete[] arr;
    }
    size_t allocations_count() const
    {
        return allocations.size();
    }
};

template <class T, class AllocatorType = Allocator<T>>
class DynamicArray
{
public:
    DynamicArray(size_t capacity) : size{0}, capacity{capacity}
    {
        data = alloc.allocate(capacity);
    }
    ~DynamicArray()
    {
        alloc.free(data);
    }
    DynamicArray(const DynamicArray<T, AllocatorType> &other)
    {
        data = alloc.allocate(other.capacity);
        size = other.size;
        capacity = other.capacity;

        for (int i = 0; i < other.size; i++)
        {
            data[i] = other.data[i];
        }
    }
    DynamicArray &operator=(const DynamicArray<T, AllocatorType> &other)
    {
        DynamicArray<T, AllocatorType> cpy{other};
        std::swap(data, cpy.data);
        std::swap(size, cpy.size);
        std::swap(capacity, cpy.capacity);
        std::swap(alloc, cpy.alloc);
        return *this;
    }

    AllocatorType get_alloc() const
    {
        return alloc;
    }

private:
    T *data;
    size_t size;
    size_t capacity;
    AllocatorType alloc;
};