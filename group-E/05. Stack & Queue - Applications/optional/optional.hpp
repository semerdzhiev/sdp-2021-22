#pragma once

template <class T>
class optional
{
public:
    optional() = default;
    optional(const T &value);

    bool has_value() const;
    T value();

private:
    T _m_value;
    bool m_has_value{false};
};

#include "optional.inl"