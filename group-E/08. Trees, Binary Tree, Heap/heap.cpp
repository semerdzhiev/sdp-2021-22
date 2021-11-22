#include <vector>
#include <stdexcept>
#include <iostream>

template <class T>
class max_heap
{
public:
    max_heap() = default;
    void insert(const T &value)
    {
        values.push_back(value);
        auto current_element_id = values.size() - 1;
        auto parent_id = get_parent_id(current_element_id);
        while (parent_id >= 0 &&
               values[parent_id] < values[current_element_id])
        {
            std::swap(values[parent_id], values[current_element_id]);
            current_element_id = parent_id;
            parent_id = get_parent_id(parent_id);
        }
    }
    void extract()
    {
        if (values.size() == 0)
        {
            throw std::length_error("Extract empty heap");
        }
        std::swap(values[0], values[values.size() - 1]);
        values.pop_back();
        heapify(0);
    }
    T max()
    {
        return values[0];
    }
    bool empty() const
    {
        return values.empty();
    }
    size_t size() const
    {
        return values.size();
    }

    void print()
    {
        for (T value : values)
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

private:
    void heapify(size_t id)
    {
        auto left = get_left_child_id(id);
        auto right = get_right_child_id(id);
        auto n = values.size();
        auto id_to_swap = id;
        if (left < n && values[left] > values[id_to_swap])
            id_to_swap = left;
        if (right < n && values[right] > values[id_to_swap])
            id_to_swap = right;
        if (id_to_swap == id)
        {
            return;
        }
        std::swap(values[id_to_swap], values[id]);
        heapify(id_to_swap);
    }
    int get_left_child_id(int id)
    {
        return id * 2 + 1;
    }
    int get_right_child_id(int id)
    {
        return id * 2 + 2;
    }
    int get_parent_id(int id)
    {
        return (id - 1) / 2;
    }
    std::vector<T> values{};
};

int main()
{
    max_heap<int> h;
    h.insert(10);
    h.print();
    h.insert(1);
    h.print();
    h.insert(15);
    h.print();
    h.insert(7);
    h.print();
    h.insert(20);
    h.print();
    std::cout << std::endl;
    while (!h.empty())
    {
        std::cout << h.max() << std::endl;
        h.extract();
        h.print();
        std::cout << std::endl;
    }
    return 0;
}