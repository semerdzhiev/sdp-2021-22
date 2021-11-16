#pragma once
#include "ForwardList.hpp"

template<class DataType>
ForwardList<DataType>::ForwardList()
    : fpHead( nullptr )
    //, fpTail( nullptr )
    //, fSize( 0 )
{}

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
ForwardList<DataType>::ForwardList( const std::initializer_list<value_type>& lst )
{
    auto    otherIt = lst.begin();
    auto    endIt   = lst.end();

    this->push_front( *otherIt );
    ++otherIt;

    self_type::iterator     insIt   = this->begin();

    for ( ; otherIt != endIt; otherIt++ )
        insIt   = this->insert_after( insIt, *otherIt );
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
void
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
}

template<class DataType>
typename ForwardList<DataType>::iterator
ForwardList<DataType>::insert_after( iterator after, const_reference elem )
{
    Node*   pSavedNode      = after.fpNode->fpNext;
    after.fpNode->fpNext    = new Node( elem, pSavedNode );
    return iterator( after.fpNode->fpNext );
}

template<class DataType>
void
ForwardList<DataType>::copy( const self_type& other )
{
    if ( other.empty() )
        return;

    self_type::const_iterator   otherIt = other.begin();
    self_type::const_iterator   endIt   = other.end();
    //self_type::iterator         insIt   = this->before_begin();

    this->push_front( *otherIt );
    ++otherIt;

    self_type::iterator         insIt   = this->begin();
    
    for ( ; otherIt != endIt; otherIt++ )
        insIt   = this->insert_after( insIt, *otherIt );

    // Alternative:
    //fpHead  = new Node( other.fpHead );
    //Node*   pCurr   = fpHead;
    //Node*   pOther  = other.fpHead->fpNext;

    //while ( pOther )
    //{
    //    pCurr->fpNext   = new Node( pOther->fpData );
    //    pCurr           = pCurr->fpNext;
    //    pOther          = pOther->fpNext;
    //}
}
