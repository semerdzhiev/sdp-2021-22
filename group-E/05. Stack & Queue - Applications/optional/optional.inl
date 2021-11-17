#pragma once

#include <stdexcept>

template <class T>
optional<T>::optional(const T &value) : _m_value{value}, m_has_value{true} {}

template <class T>
bool optional<T>::has_value() const
{
    return m_has_value;
}

template <class T>
T optional<T>::value()
{
    if(!m_has_value)
    {
        throw std::runtime_error("Optional has no value");
    }
    return _m_value;
}

