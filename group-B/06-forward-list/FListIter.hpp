#pragma once
#ifndef _FORWARD_LIST_ITERATOR_HEADER_INCLUDED_
#define _FORWARD_LIST_ITERATOR_HEADER_INCLUDED_

// Forward declaration of the ForwardList class
template<class DataType>
class ForwardList;

//------------------------------------------------------------------------------
template<class DataType>
class FListIter
{
    // STL compatibility and other typenames
public:
    using   iterator_category       = std::forward_iterator_tag;
    using   value_type              = DataType;
    using   difference_type         = std::ptrdiff_t;
    using   pointer                 = value_type*;
    using   reference               = value_type&;

    using   const_value_type        = const value_type;
    using   const_pointer           = const_value_type*;
    using   const_reference         = const_value_type&;
    using   self_type               = FListIter<value_type>;
    using   container               = ForwardList<value_type>;
    using   const_iterator          = FListIter<const_value_type>;

private:
    using   non_const_value_type    = typename std::remove_const<value_type>::type;

    using   const_container         = ForwardList<const_value_type>;
    using   non_const_iterator      = FListIter<non_const_value_type>;
    using   non_const_container     = ForwardList<non_const_value_type>;

    using   container_node          = typename container::Node;

    // Objects lifetime
private:
    explicit            FListIter( void* currPtr, void* nextPtr = nullptr );

public:
                        FListIter( const self_type& )       = default;
    self_type&          operator=( const self_type& )       = default;
                        ~FListIter()                        = default;

    // Public operators
public:
                        operator const_iterator()               const;

    bool                operator==( const self_type& other )    const;
    bool                operator!=( const self_type& other )    const;

    self_type&          operator++();
    self_type           operator++( int );

    reference           operator*()             { return fpNode->fData; }
    const_reference     operator*()     const   { return fpNode->fData; }

    pointer             operator->()            { return &fpNode->fData; }
    const_pointer       operator->()    const   { return &fpNode->fData; }

private:
    friend class    non_const_container;    // Private fpNode
    friend class    const_container;        // Private fpNode
    friend class    non_const_iterator;     // Private ctor

    // Fields
private:
    container_node*     fpNode;
    container_node*     fpNext; // Nasty workaround for before_begin() to work
};

#include "FListIter.ipp"

#endif // !_FORWARD_LIST_ITERATOR_HEADER_INCLUDED_
