
#include <iostream>
#include <cassert>
#include <stdexcept>

template <class T>
struct node
{
    T value{};
    node *next_element_ptr{};
};

template <class T>
struct linked_list
{
public:
    linked_list() = default;
    ~linked_list()
    {
        auto current = first;
        while (current != nullptr)
        {
            auto next = current->next_element_ptr;
            delete current;
            current = next;
        }
    }
    // Ro3

    void push_back(const T &value)
    {
        node<T> *new_last = new node<T>();
        new_last->value = value;
        if (last != nullptr)
        {
            last->next_element_ptr = new_last;
        }
        if (first == nullptr)
        {
            assert(last == nullptr);
            first = new_last;
        }
        last = new_last;
    }

    void push_front(const T &value)
    {
        node<T> *new_first = new node<T>();
        new_first->value = value;
        new_first->next_element_ptr = first;
        if (last == nullptr)
        {
            assert(first == nullptr);
            last = new_first;
        }
        first = new_first;
    }

    void pop_front()
    {
        if (first == nullptr)
        {
            assert(last == nullptr);
            throw std::invalid_argument("Cannot pop empty list");
        }
        node<T> *first_cpy = first;
        first = first->next_element_ptr;
        delete first_cpy;
        if(first == nullptr)
        {
            last = nullptr;
        }
    }

    // NB - linear complexity
    void pop_back()
    {
        if (last == nullptr)
        {
            assert(first == nullptr);
            throw std::invalid_argument("Cannot pop empty list");
        }
        if(first == last)
        {
            delete first;
            first = nullptr;
            last = nullptr;
            return;
        }
        node<T> *last_cpy = last;
        node<T> *current = first;
        while (current->next_element_ptr != last)
        {
            current = current->next_element_ptr;
        }
        current->next_element_ptr = nullptr;
        last = current;
        delete last_cpy;
    }

    void print()
    {
        auto current = first;
        while (current != nullptr)
        {
            std::cout << current->value << " ";
            current = current->next_element_ptr;
        }
        std::cout << std::endl;
    }

        // NB linear operation
    const T &operator[](size_t index) const
    {
        auto current = first;
        for (size_t id = 0; id < index; id++)
        {
            current = current->next_element_ptr;
        }
        return current->value;
    }
    // inserts value on index
    // NB linear operation
    void insert(size_t index, const T &value)
    {
        node<T> *new_node = new node<T>();
        new_node->value = value;
        auto current = first;
        for (size_t id = 0; id < index - 1; id++)
        {
            current = current->next_element_ptr;
        }
        auto prev_element_ptr = current;
        auto next_element_ptr = current->next_element_ptr;
        prev_element_ptr->next_element_ptr = new_node;
        new_node->next_element_ptr = next_element_ptr;
    }

private:
    node<T> *first{};
    node<T> *last{};
};

int main()
{
    linked_list<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.print();
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.print();
    list.pop_front();
    list.pop_back();
    list.print();
    list.pop_front();
    list.pop_back();
    list.print();
    list.pop_front();
    list.pop_back();
    list.print();
    return 0;
}