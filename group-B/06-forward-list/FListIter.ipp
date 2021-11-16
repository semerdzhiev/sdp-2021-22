#pragma once
#include "ForwardList.hpp"

template<class DataType>
FListIter<DataType>::FListIter( void* ptr )
    : fpNode( static_cast<container_node*>( ptr ) )
{}

template<class DataType>
FListIter<DataType>&
FListIter<DataType>::operator=( container_node* ptr )
{
    fpNode = ptr;
    return *this;
}

template<class DataType>
FListIter<DataType>::operator bool() const
{
    return fpNode != nullptr;
}

template<class DataType>
bool
FListIter<DataType>::operator==( const self_type& other ) const
{
    return fpNode == other.fpNode;
}

template<class DataType>
bool
FListIter<DataType>::operator!=( const self_type& other ) const
{
    return !(*this == other);
}

template<class DataType>
FListIter<DataType>&
FListIter<DataType>::operator++()
{
    fpNode = fpNode->fpNext;
    return *this;
}

template<class DataType>
FListIter<DataType>
FListIter<DataType>::operator++( int )
{
    FListIter<DataType>     resIt = *this;
    ++( *this );
    return resIt;
}

template<class DataType>
FListIter<DataType>::operator FListIter<DataType const>() const
{
    return FListIter<DataType const>( fpNode );
}
