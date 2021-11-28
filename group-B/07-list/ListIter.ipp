#pragma once
#ifndef _LIST_ITERATOR_IMPLEMENTATION_INCLUDED_
#define _LIST_ITERATOR_IMPLEMENTATION_INCLUDED_

#include "ListIter.hpp"
#include <stdexcept>

template<class DataType>
ListIter<DataType>::ListIter( void* currPtr )
    : fpNode( static_cast<container_node*>( currPtr ) )
{}

template<class DataType>
ListIter<DataType>::operator const_iterator() const
{
    return const_iterator( fpNode );
}

template<class DataType>
bool
ListIter<DataType>::operator==( const self_type& other ) const
{
    return fpNode == other.fpNode;
}

template<class DataType>
bool
ListIter<DataType>::operator!=( const self_type& other ) const
{
    return !(*this == other);
}

template<class DataType>
ListIter<DataType>&
ListIter<DataType>::operator++()
{
    if ( !fpNode )
        throw std::logic_error( "ListIter<?>: Cannot increment end() iterator" );

    fpNode  = fpNode->fpNext;
    return *this;
}

template<class DataType>
ListIter<DataType>
ListIter<DataType>::operator++( int )
{
    self_type   resIt   = *this;
    this->operator++();
    return resIt;
}

template<class DataType>
ListIter<DataType>&
ListIter<DataType>::operator--()
{
    if ( ! fpNode )
        throw std::logic_error( "ListIter<?>: Cannot decrement end() iterator (not implemented)" );

    if ( ! fpNode->fpPrev )
        throw std::logic_error( "ListIter<?>: Cannot decrement begin() iterator" );

    fpNode  = fpNode->fpPrev;
    return *this;
}

template<class DataType>
ListIter<DataType>
ListIter<DataType>::operator--( int )
{
    self_type   resIt   = *this;
    this->operator--();
    return resIt;
}

//------------------------------------------------------------------------------

template<class DataType>
ListRevIter<DataType>::ListRevIter( void* currPtr )
    : ListIter<DataType>( currPtr )
{}

template<class DataType>
ListRevIter<DataType>::operator const_iterator() const
{
    return const_iterator( this->fpNode );
}

template<class DataType>
bool
ListRevIter<DataType>::operator==( const self_type& other ) const
{
    return ListIter<DataType>::operator==( other );
}

template<class DataType>
bool
ListRevIter<DataType>::operator!=( const self_type& other ) const
{
    return ListIter<DataType>::operator!=( other );
}

template<class DataType>
ListRevIter<DataType>&
ListRevIter<DataType>::operator++()
{
    if ( ! this->fpNode )
        throw std::logic_error( "ListIter<?>: Cannot increment rend() iterator" );

    this->fpNode    = this->fpNode->fpPrev;
    return *this;
}

template<class DataType>
ListRevIter<DataType>
ListRevIter<DataType>::operator++( int )
{
    self_type   resIt   = *this;
    this->operator++();
    return resIt;
}

template<class DataType>
ListRevIter<DataType>&
ListRevIter<DataType>::operator--()
{
    if ( ! this->fpNode )
        throw std::logic_error( "ListIter<?>: Cannot decrement rend() iterator (not implemented)" );

    if ( ! this->fpNode->fpNext )
        throw std::logic_error( "ListIter<?>: Cannot decrement rbegin() iterator" );

    this->fpNode    = this->fpNode->fpNext;
    return *this;
}

template<class DataType>
ListRevIter<DataType>
ListRevIter<DataType>::operator--( int )
{
    self_type   resIt   = *this;
    this->operator--();
    return resIt;
}

#endif _LIST_ITERATOR_IMPLEMENTATION_INCLUDED_
