#pragma once
#ifndef _FORWARD_LIST_ITERATOR_IMPLEMENTATION_INCLUDED_
#define _FORWARD_LIST_ITERATOR_IMPLEMENTATION_INCLUDED_

#include "ForwardList.hpp"

template<class DataType>
FListIter<DataType>::FListIter( void* currPtr, void* nextPtr )
    : fpNode( static_cast<container_node*>( currPtr ) )
    , fpNext( static_cast<container_node*>( nextPtr ) )
{}

template<class DataType>
bool
FListIter<DataType>::operator==( const self_type& other ) const
{
    return fpNode == other.fpNode && fpNext == other.fpNext;
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
    fpNode = fpNode ? fpNode->fpNext : fpNext;
    fpNext = nullptr;
    return *this;
}

template<class DataType>
FListIter<DataType>
FListIter<DataType>::operator++( int )
{
    self_type   resIt   = *this;
    this->operator++();
    return resIt;
}

template<class DataType>
FListIter<DataType>::operator const_iterator() const
{
    return const_iterator( fpNode );
}

#endif _FORWARD_LIST_ITERATOR_IMPLEMENTATION_INCLUDED_
