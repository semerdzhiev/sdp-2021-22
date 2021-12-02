#pragma once
#ifndef _PRIORITY_QUEUE_IMPLEMENTATION_INCLUDED_
#define _PRIORITY_QUEUE_IMPLEMENTATION_INCLUDED_

#include <algorithm>
#include <iterator>
#include "PriorityQueue.hpp"

template<class T, class Container, class Comparator>
template<class InputIt>
PriorityQueue<T, Container, Comparator>::PriorityQueue( InputIt first, InputIt last )
{
    fContainer.insert( fContainer.end(), first, last );

    // .insert() - for vector is more or less equivalent to:
    //fContainer.reserve( last - first );
    //for ( ; first != last; first++ )
    //    fContainer.push_back( *first );

    make_heap();
}

template<class T, class Container, class Comparator>
void
PriorityQueue<T, Container, Comparator>::push( const_reference elem )
{
    // In STL:
    //fContainer.push_back( elem );
    //std::push_heap( fContainer.begin(), fContainer.end(), fComparator );

    fContainer.push_back( elem );
    iterator    itCurr      = last();
    iterator    itParent    = parent( itCurr );

    // If it and its parent violate the invariant
    while ( itCurr != begin() && !fComparator( *itCurr, *itParent ) )
    {
        std::swap( *itCurr, *itParent );

        itCurr      = itParent;
        itParent    = parent( itCurr );
    }
}

template<class T, class Container, class Comparator>
void
PriorityQueue<T, Container, Comparator>::pop()
{
    std::swap( *begin(), *last() );
    fContainer.pop_back();

    iterator    itCurr  = begin();
    while ( itCurr != end() )
    {
        iterator    itLeft  = left_child( itCurr );
        iterator    itRight = right_child( itCurr );

        iterator    itSwap  = itCurr;
        if ( itLeft != end() && fComparator( *itSwap, *itLeft ) )
            itSwap  = itLeft;

        if ( itRight != end() && fComparator( *itSwap, *itRight ) )
            itSwap  = itRight;

        if ( itSwap != itCurr )
        {
            std::swap( *itCurr, *itSwap );
            itCurr  = itSwap;
        }
        else
        {
            itCurr  = end();
        }
    }
}

template<class T, class Container, class Comparator>
typename Container::iterator
PriorityQueue<T, Container, Comparator>::parent( iterator it )
{
    if ( it == begin() )
        return end();

    return iter( (index(it) - 1) / 2 );
}

template<class T, class Container, class Comparator>
typename Container::iterator
PriorityQueue<T, Container, Comparator>::left_child( iterator it )
{
    return iter( 2 * index(it) + 1 );
}

template<class T, class Container, class Comparator>
typename Container::iterator
PriorityQueue<T, Container, Comparator>::right_child( iterator it )
{
    return iter( 2 * index(it) + 2 );
}

template<class T, class Container, class Comparator>
typename Container::iterator::difference_type
PriorityQueue<T, Container, Comparator>::index( iterator it )
{
    return std::distance( begin(), it );
}

template<class T, class Container, class Comparator>
typename Container::iterator
PriorityQueue<T, Container, Comparator>::iter( size_type index )
{
    if ( index >= size() )
        return end();

    iterator    it  = begin();
    std::advance( it, index );
    return it;
}

template<class T, class Container, class Comparator>
void
PriorityQueue<T, Container, Comparator>::make_heap()
{
    if ( size() <= 1 )
        return;

    for ( int i = size() / 2 - 1; i >= 0; i-- )
        heapify( iter(i) );
}

template<class T, class Container, class Comparator>
void
PriorityQueue<T, Container, Comparator>::heapify( iterator it )
{
    iterator    itSwap  = it;
    iterator    itLeft  = left_child( it );
    iterator    itRight = right_child( it );

    if ( itLeft != end() && !fComparator( *itLeft, *itSwap ) )
        itSwap  = itLeft;

    if ( itRight != end() && !fComparator( *itRight, *itSwap ) )
        itSwap  = itRight;

    if ( itSwap != it )
    {
        std::swap( *it, *itSwap );
        heapify( itSwap );
    }
}

#endif  // !_PRIORITY_QUEUE_IMPLEMENTATION_INCLUDED_
