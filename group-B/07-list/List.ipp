#pragma once
#ifndef _LIST_IMPLEMENTATION_INCLUDED_
#define _LIST_IMPLEMENTATION_INCLUDED_

#include <stdexcept>
#include "List.hpp"

template<class DataType>
List<DataType>::List()
    : fpHead( nullptr )
    , fpTail( nullptr )
    , fSize( 0 )
{}

template<class DataType>
List<DataType>::List( const init_list& initList )
    : List<DataType>()  // push_back() relies on 'this' being in a valid state!
{
    for ( const value_type& elem : initList )
        this->push_back( elem );
}

template<class DataType>
List<DataType>::List( const self_type& other )
    : List<DataType>()  // push_back() relies on 'this' being in a valid state!
{
    for ( const value_type& elem : other )
        this->push_back( elem );

    // Alternative version without iterators:
    //const Node* pOther  = other.fpHead;
    // 
    //while ( pOther )
    //{
    //    this->push_back( pOther->fData );
    //    pOther  = pOther.fpNext;
    //}
}

template<class DataType>
List<DataType>&
List<DataType>::operator=( const self_type& other )
{
    if ( this != &other )
    {
        List<DataType>  otherCopy( other );
        swap( *this, otherCopy );
    }

    return *this;
}

template<class DataType>
List<DataType>::~List()
{
    this->clear();
}

template<class DataType>
void
List<DataType>::push_front( const_reference elem )
{
    if ( fpHead == nullptr )
    {
        fpHead  = new Node( elem );
        fpTail  = fpHead;
    }
    else
    {
        fpHead->fpPrev  = new Node( elem, nullptr, fpHead );
        fpHead          = fpHead->fpPrev;
    }

    ++fSize;
}

template<class DataType>
void
List<DataType>::push_back( const_reference elem )
{
    if ( fpHead == nullptr )
    {
        fpHead  = new Node( elem );
        fpTail  = fpHead;
    }
    else
    {
        fpTail->fpNext  = new Node( elem, fpTail, nullptr );
        fpTail          = fpTail->fpNext;
    }

    ++fSize;
}

template<class DataType>
void
List<DataType>::pop_front()
{
    if ( this->empty() )
        throw std::logic_error( "List<?>::pop_front() from an empty list!" );

    if ( fpHead == fpTail )
    {
        delete  fpHead;
        fpHead  = nullptr;
        fpTail  = nullptr;
    }
    else
    {
        fpHead  = fpHead->fpNext;
        delete  fpHead->fpPrev;

        fpHead->fpPrev  = nullptr;
    }

    --fSize;
}

template<class DataType>
void
List<DataType>::pop_back()
{
    if ( this->empty() )
        throw std::logic_error( "List<?>::pop_back() from an empty list!" );

    if ( fpHead == fpTail )
    {
        delete  fpHead;
        fpHead  = nullptr;
        fpTail  = nullptr;
    }
    else
    {
        fpTail  = fpTail->fpPrev;
        delete  fpTail->fpNext;

        fpTail->fpNext  = nullptr;
    }

    --fSize;
}

template<class DataType>
void
List<DataType>::clear()
{
    while ( ! this->empty() )
        this->pop_back();   // or pop_front()

    // Alternative:
    //Node*   pToDel  = fpHead;
    // 
    //while ( pToDel )
    //{
    //    fpHead  = fpHead->fpNext;
    //    delete pToDel;
    //    pToDel  = fpHead;
    //}
    // 
    //fpTail  = nullptr;
    //fSize   = 0;
}

template<class DataType>
const List<DataType>&
List<DataType>::print() const
{
    std::cout << "[";

    if ( ! this->empty() )
    {
        const_iterator  it      = this->begin();
        const_iterator  endIt   = this->end();

        std::cout << ' ' << *it << ' ';
        ++it;

        for ( ; it != endIt; it++ )
            std::cout << "<> " << *it << ' ';
    }

    std::cout << "]";

    return *this;
}

template<class DataType>
void swap( List<DataType>& lhs, List<DataType>& rhs )
{
    using std::swap;
    swap( lhs.fpHead    , rhs.fpHead );
    swap( lhs.fpTail    , rhs.fpTail );
    swap( lhs.fSize     , rhs.fSize  );
}

template<class DataType>
typename List<DataType>::iterator
List<DataType>::insert( iterator position, const_reference elem )
{
    if ( position == this->end() )
    {
        this->push_back( elem );
        return iterator( fpTail );
    }

    if ( position == this->begin() )
    {
        this->push_front( elem );
        return this->begin();
    }

    Node*   currNode    = position.fpNode;
    Node*   prevNode    = currNode->fpPrev;
    Node*   newNode     = new Node( elem, currNode->fpPrev, currNode );

    currNode->fpPrev    = newNode;
    prevNode->fpNext    = newNode;

    ++fSize;

    return iterator( newNode );
}

template<class DataType>
typename List<DataType>::iterator
List<DataType>::erase( iterator position )
{
    return iterator( this->erase( position.fpNode ) );
}

template<class DataType>
typename List<DataType>::Node*
List<DataType>::erase( Node* pNode )
{
    if ( this->empty() )
        throw std::logic_error( "List<?>::erase() from an empty list!" );

    // Case: pNode is the first element
    if ( pNode == fpHead )
    {
        pop_front();
        return fpHead;
    }

    // Case: pNode is the last element
    if ( pNode == fpTail )
    {
        pop_back();
        return nullptr;
    }

    // General case: At least 3 elements exist
    Node*   pPrev   = pNode->fpPrev;
    Node*   pNext   = pNode->fpNext;

    pPrev->fpNext   = pNext;
    pNext->fpPrev   = pPrev;

    delete  pNode;

    --fSize;

    return pNext;
}

#endif // !_LIST_IMPLEMENTATION_INCLUDED_
