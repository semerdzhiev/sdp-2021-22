#pragma once

#include <functional>

struct A {
    int a;
    int b;

    A(int a = 0, int b = 0) : a(a), b(b) {}

    bool operator==(const A& other) { return a == other.a && b == other.b; }
    bool operator!=(const A& other) { return *this != other; }
};

template<>
struct std::hash<A>
{
    std::size_t operator()(A const& a) const noexcept
    {
        std::hash<int> intHasher;
        return intHasher(a.a) + intHasher(a.b);
    }
};