#pragma once
#ifndef _FORWARD_LIST_IMPLEMENTATION_INCLUDED_
#define _FORWARD_LIST_IMPLEMENTATION_INCLUDED_

#include "ForwardList.hpp"

template<class DataType>
ForwardList<DataType>::ForwardList()
    : fpHead( nullptr )
{}

template<class DataType>
ForwardList<DataType>::ForwardList( const init_list& lst )
    : ForwardList<DataType>()
{
    using init_list_iterator = typename init_list::iterator;

    // Or we could just write
    //  auto    otherIt     = lst.begin();
    //  auto    endIt       = lst.end();

    init_list_iterator  otherIt     = lst.begin();
    init_list_iterator  endIt       = lst.end();
    iterator            insIt       = this->before_begin();

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
    // 
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
        const_iterator  it      = this->begin();
        const_iterator  endIt   = this->end();

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
    if ( after == this->before_begin() )
    {
        this->push_front( elem );
        return iterator( fpHead );
    }

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
    if ( after == this->end() )
        throw std::logic_error( "ForwardList<?>::erase_after() erase after end() iter!" );

    if ( after.fpNode->fpNext == nullptr )
        throw std::logic_error( "ForwardList<?>::erase_after() erase after last element!" );

    return iterator( this->erase_after( after.fpNode ) );
}

template<class DataType>
void
ForwardList<DataType>::copy( const self_type& other )
{
    if ( other.empty() )
        return;

    //const_iterator  otherIt = other.begin();
    //const_iterator  endIt   = other.end();
    iterator        insIt   = this->before_begin();
    
    //for ( ; otherIt != endIt; otherIt++ )
    for ( const DataType& elem : other )
        insIt   = this->insert_after( insIt, elem );

    // Alternative without iterators:
    //fpHead  = new Node( other.fpHead->fData );
    //Node*       pCurr   = fpHead;
    //const Node* pOther  = other.fpHead->fpNext;

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
    if ( pAfter == nullptr )
        return nullptr;

    if ( pAfter->fpNext == nullptr )
        return nullptr;

    Node*   pNext   = pAfter->fpNext;
    pAfter->fpNext  = pNext->fpNext;

    delete pNext;

    return pAfter->fpNext;
}

#endif // !_FORWARD_LIST_IMPLEMENTATION_INCLUDED_
