#pragma once
#ifndef _FORWARD_LIST_IMPLEMENTATION_INCLUDED_
#define _FORWARD_LIST_IMPLEMENTATION_INCLUDED_

#include "ForwardList.hpp"

template<class DataType>
ForwardList<DataType>::ForwardList()
    : fpHead( nullptr )
{}

template<class DataType>
ForwardList<DataType>::ForwardList( const std::initializer_list<value_type>& lst )
    : ForwardList<DataType>()
{
    using init_list_iterator = const typename std::initializer_list<value_type>::value_type*;

    // Or we could just write
    //  auto    otherIt     = lst.begin();
    //  auto    endIt       = lst.end();

    init_list_iterator  otherIt     = lst.begin();
    init_list_iterator  endIt       = lst.end();

    this->push_front( *otherIt );
    ++otherIt;

    self_type::iterator     insIt   = this->begin();

    for ( ; otherIt != endIt; otherIt++ )
        insIt   = this->insert_after( insIt, *otherIt );
}

template<class DataType>
ForwardList<DataType>::ForwardList( const self_type& other )
    : ForwardList<DataType>()
{
    this->copy( other );
}

template<class DataType>
ForwardList<DataType>&
ForwardList<DataType>::operator=( const self_type& other )
{
    if ( this != &other )
    {
        this->clear();
        this->copy( other );
    }

    return *this;
}

template<class DataType>
ForwardList<DataType>::~ForwardList()
{
    this->clear();
}

template<class DataType>
void
ForwardList<DataType>::push_front( const_reference elem )
{
    fpHead  = new Node( elem, fpHead );
}

template<class DataType>
void
ForwardList<DataType>::pop_front()
{
    Node*   pToDel  = fpHead;
    fpHead  = fpHead->fpNext;

    delete  pToDel;
}

template<class DataType>
void
ForwardList<DataType>::clear()
{
    while ( !this->empty() )
        this->pop_front();

    // Alternative:
    //Node*   pToDel  = fpHead;
    //while ( pToDel )
    //{
    //    fpHead  = fpHead->fpNext;
    //    delete pToDel;
    //    pToDel  = fpHead;
    //}
}

template<class DataType>
const ForwardList<DataType>&
ForwardList<DataType>::print() const
{
    std::cout << "[";

    if ( !this->empty() )
    {
        self_type::const_iterator   it      = this->begin();
        self_type::const_iterator   endIt   = this->end();

        std::cout << ' ' << *it << ' ';
        ++it;

        for ( ; it != endIt; it++ )
            std::cout << "-> " << *it << ' ';
    }

    std::cout << "]";

    return *this;
}

template<class DataType>
typename ForwardList<DataType>::iterator
ForwardList<DataType>::insert_after( iterator after, const_reference elem )
{
    Node*   pSavedNode      = after.fpNode->fpNext;
    after.fpNode->fpNext    = new Node( elem, pSavedNode );
    return iterator( after.fpNode->fpNext );
    
    // Can be written as:
    //  return iterator( after.fpNode->fpNext = new Node( elem, after.fpNode->fpNext ) );
    // but it becomes quite difficult to read.
}

template<class DataType>
typename ForwardList<DataType>::iterator
ForwardList<DataType>::erase_after( iterator after )
{
    // TODO: Implement
    throw std::logic_error( "ForwardList<DataType>::erase_after( iterator after ) is not implemented!" );

    return after;
}

template<class DataType>
void
ForwardList<DataType>::copy( const self_type& other )
{
    if ( other.empty() )
        return;

    self_type::const_iterator   otherIt = other.begin();
    self_type::const_iterator   endIt   = other.end();

    //  self_type::iterator         insIt   = this->before_begin();
    //
    // STL's forward_list has before_begin() that can be used
    // with insert_after() to insert an element at the begining.
    // Unfortunately it is not trivial to implement before_begin()

    this->push_front( *otherIt );
    ++otherIt;

    self_type::iterator         insIt   = this->begin();
    
    for ( ; otherIt != endIt; otherIt++ )
        insIt   = this->insert_after( insIt, *otherIt );

    // Alternative without iterators:
    //fpHead  = new Node( other.fpHead->fData );
    //Node*   pCurr   = fpHead;
    //Node*   pOther  = other.fpHead->fpNext;

    //while ( pOther )
    //{
    //    pCurr->fpNext   = new Node( pOther->fpData );
    //    pCurr           = pCurr->fpNext;
    //    pOther          = pOther->fpNext;
    //}
}

template<class DataType>
typename ForwardList<DataType>::Node*
ForwardList<DataType>::erase_after( Node* pAfter )
{
    // TODO: Implement
    throw std::logic_error( "ForwardList<DataType>::erase_after( Node* pAfter ) is not implemented!" );

    return pAfter;
}

#endif // !_FORWARD_LIST_IMPLEMENTATION_INCLUDED_
