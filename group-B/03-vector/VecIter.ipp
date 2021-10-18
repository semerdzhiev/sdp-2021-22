#include "Vector.hpp"

template<class DataType>
VecIter<DataType>::VecIter( DataType* ptr )
    : fpData( ptr )
{}

template<class DataType>
VecIter<DataType>&
VecIter<DataType>::operator=( DataType* ptr )
{
    fpData  = ptr;
    return *this;
}

template<class DataType>
VecIter<DataType>::operator bool() const
{
    return fpData != nullptr;
}

template<class DataType>
bool
VecIter<DataType>::operator==( const VecIter<DataType>& other ) const
{
    return fpData == other.fpData;
}

template<class DataType>
bool
VecIter<DataType>::operator!=( const VecIter<DataType>& other ) const
{
    return !this->operator==( other );
}

template<class DataType>
VecIter<DataType>&
VecIter<DataType>::operator+=( const difference_type& movement )
{
    fpData  += movement;
    return *this;
}

template<class DataType>
VecIter<DataType>& VecIter<DataType>::operator-=( const difference_type& movement )
{
    fpData  -= movement;
    return *this;
}

template<class DataType>
VecIter<DataType>&
VecIter<DataType>::operator++()
{
    ++fpData;
    return *this;
}

template<class DataType>
VecIter<DataType>&
VecIter<DataType>::operator--()
{
    --fpData;
    return *this;
}

template<class DataType>
VecIter<DataType>
VecIter<DataType>::operator++( int )
{
    VecIter<DataType>   res( *this );
    ++(*this);
    return res;
}

template<class DataType>
VecIter<DataType>
VecIter<DataType>::operator--( int )
{
    VecIter<DataType>   res( *this );
    --(*this);
    return res;
}

template<class DataType>
VecIter<DataType>
VecIter<DataType>::operator+( const difference_type& movement ) const
{
    VecIter<DataType>   res( *this );
    res += movement;
    return res;
}

template<class DataType>
VecIter<DataType>
VecIter<DataType>::operator-( const difference_type& movement ) const
{
    VecIter<DataType>   res( *this );
    res -= movement;
    return res;
}

template<class DataType>
typename VecIter<DataType>::difference_type
VecIter<DataType>::operator-( const VecIter<DataType>& other ) const
{
    return std::distance( other.fpData, fpData );
}

template<class DataType>
VecIter<DataType>::operator VecIter<DataType const>() const
{
    return VecIter<const DataType>( fpData );
}
