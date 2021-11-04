#include <cassert>
#include <iostream>

template <typename T>
class queue
{
public:
    queue() = default;
    ~queue()
    {
        delete[] m_arr;
    }
    queue(const queue<T> &other)
    {
        m_arr = new T[other.m_capacity];
        for (size_t i = 0; i < other.m_last; i++)
        {
            m_arr[i] = other.m_arr[i];
        }
        m_first = other.m_first;
        m_last = other.m_last;
        m_capacity = other.m_capacity;
    }
    queue<T> &operator=(const queue<T> &other)
    {
        queue<T> cpy = other;
        std::swap(m_arr, cpy.m_arr);
        std::swap(m_first, cpy.m_first);
        std::swap(m_last, cpy.m_last);
        std::swap(m_capacity, cpy.m_capacity);
        return *this;
    }

    T &front()
    {
        return m_arr[m_first];
    }
    const T &front() const
    {
        return m_arr[m_first];
    }
    T &back()
    {
        assert(m_last != 0);
        return m_arr[m_last - 1];
    }
    const T &back() const
    {
        assert(m_last != 0);
        return m_arr[m_last - 1];
    }

    void push(const T &elem)
    {
        if (m_last == m_capacity)
        {
            resize();
        }
        m_arr[m_last++] = elem;
    }

    void pop()
    {
        m_first++;
    }

    size_t size() const
    {
        return m_last - m_first;
    }

    bool empty() const
    {
        return size() == 0;
    }

private:
    void resize()
    {
        T *new_arr = new T[m_capacity * 2];
        for (size_t i = m_first; i < m_last; i++)
        {
            new_arr[i] = m_arr[i];
        }
        std::swap(new_arr, m_arr);
        delete[] new_arr;
        m_capacity *= 2;
    }
    T *m_arr{new T[2]};
    size_t m_last{};
    size_t m_first{};
    size_t m_capacity{2};
};

int main()
{
    queue<int> q;
    q.push(1);
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    q.push(2);
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    q.push(3);
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    q.push(4);
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;

    queue<int> q1 = q;
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    std::cout << q.size() << " " << q1.front() << " " << q1.back() << std::endl;
    q1.pop();
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    std::cout << q.size() << " " << q1.front() << " " << q1.back() << std::endl;

    queue<int> q2;
    q2 = q1;
    q2.pop();
    std::cout << q.size() << " " << q1.front() << " " << q1.back() << std::endl;
    std::cout << q.size() << " " << q2.front() << " " << q2.back() << std::endl;

    q.pop();
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    q.pop();
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    q.pop();
    std::cout << q.size() << " " << q.front() << " " << q.back() << std::endl;
    q.pop();
    std::cout << std::boolalpha << q.empty() << std::endl;
    return 0;
}