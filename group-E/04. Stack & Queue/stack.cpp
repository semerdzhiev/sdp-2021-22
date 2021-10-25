#include <cassert>
#include <iostream>

template <typename T>
class stack
{
public:
    stack() = default;
    ~stack()
    {
        delete[] m_arr;
    }
    stack(const stack<T> &other)
    {
        m_arr = new T[other.m_capacity];
        for (size_t i = 0; i < other.m_size; i++)
        {
            m_arr[i] = other.m_arr[i];
        }
        m_size = other.m_size;
        m_capacity = other.m_capacity;
    }
    stack<T> &operator=(const stack<T> &other)
    {
        stack<T> cpy = other;
        std::swap(m_arr, cpy.m_arr);
        std::swap(m_size, cpy.m_size);
        std::swap(m_capacity, cpy.m_capacity);
        return *this;
    }

    const T &top() const
    {
        assert(m_size != 0);
        return m_arr[m_size - 1];
    }
    T &top()
    {
        assert(m_size != 0);
        return m_arr[m_size - 1];
    }

    void push(const T &elem)
    {
        if (m_size == m_capacity)
        {
            resize();
        }
        m_arr[m_size++] = elem;
    }
    void pop()
    {
        assert(m_size != 0);
        m_size--;
    }

    bool empty() const
    {
        return m_size == 0;
    }

    size_t size() const
    {
        return m_size;
    }

private:
    void resize()
    {
        T *new_arr = new T[m_capacity * 2];
        for (size_t i = 0; i < m_size; i++)
        {
            new_arr[i] = m_arr[i];
        }
        std::swap(new_arr, m_arr);
        delete[] new_arr;
        m_capacity *= 2;
    }
    T *m_arr{new T[2]};
    size_t m_size{};
    size_t m_capacity{2};
};

int main()
{
    stack<int> s;
    s.push(1);
    std::cout << s.top() << std::endl;
    s.push(2);
    std::cout << s.top() << std::endl;
    s.push(3);
    std::cout << s.top() << std::endl;
    s.push(4);

    auto s1 = s;
    stack<int> s2;

    std::cout<<s1.top()<<std::endl;
    s1.pop();
    s2 = s1;
    std::cout<<s1.top()<<std::endl;
    std::cout<<s2.top()<<std::endl;
    s2.pop();
    std::cout<<s1.top()<<std::endl;
    std::cout<<s2.top()<<std::endl;


    std::cout << s.top() << std::endl;
    s.pop();
    std::cout << s.top() << std::endl;
    s.pop();
    std::cout << s.top() << std::endl;
    s.pop();
    std::cout << s.top() << std::endl;
    s.pop();
    std::cout << std::boolalpha << s.empty() << std::endl;
    return 0;
}