#pragma once
#ifndef _LIST_ITERATOR_HEADER_INCLUDED_
#define _LIST_ITERATOR_HEADER_INCLUDED_

#include <iterator>

// Forward declaration of the List class
template<class DataType>
class List;

//------------------------------------------------------------------------------
template<class DataType>
class ListIter
{
    // STL compatibility and other typenames
public:
    using   iterator_category       = std::bidirectional_iterator_tag;
    using   value_type              = DataType;
    using   difference_type         = std::ptrdiff_t;
    using   pointer                 = value_type*;
    using   reference               = value_type&;

    using   const_value_type        = const value_type;
    using   const_pointer           = const_value_type*;
    using   const_reference         = const_value_type&;
    using   self_type               = ListIter<value_type>;
    using   container               = List<value_type>;
    using   const_iterator          = ListIter<const_value_type>;

private:
    using   non_const_value_type    = typename std::remove_const<value_type>::type;

    using   const_container         = List<const_value_type>;
    using   non_const_iterator      = ListIter<non_const_value_type>;
    using   non_const_container     = List<non_const_value_type>;

    using   container_node          = typename container::Node;

    // Objects lifetime
protected:
    explicit            ListIter( void* currPtr );

public:
                        ListIter( const self_type& )        = default;
    self_type&          operator=( const self_type& )       = default;
                        ~ListIter()                         = default;

    // Public operators
public:
                        operator const_iterator()               const;

    bool                operator==( const self_type& other )    const;
    bool                operator!=( const self_type& other )    const;

    self_type&          operator++();
    self_type           operator++( int );
    self_type&          operator--();
    self_type           operator--( int );

    reference           operator*()             { return fpNode->fData; }
    const_reference     operator*()     const   { return fpNode->fData; }

    pointer             operator->()            { return &fpNode->fData; }
    const_pointer       operator->()    const   { return &fpNode->fData; }

private:
    friend class    non_const_container;    // Private fpNode
    friend class    const_container;        // Private fpNode
    friend class    non_const_iterator;     // Protected ctor

    // Fields
protected:
    container_node*     fpNode;
    //container_node*     fpPrev; // Can be used as a nasty workaround
                                  // for end()-- to work
};


//------------------------------------------------------------------------------
template<class DataType>
class ListRevIter : public ListIter<DataType>
{
    // STL compatibility and other typenames
public:
    using   iterator_category       = std::bidirectional_iterator_tag;
    using   value_type              = DataType;
    using   difference_type         = std::ptrdiff_t;
    using   pointer                 = value_type*;
    using   reference               = value_type&;

    using   const_value_type        = const value_type;
    using   const_pointer           = const_value_type*;
    using   const_reference         = const_value_type&;
    using   self_type               = ListRevIter<value_type>;
    using   container               = List<value_type>;
    using   const_iterator          = ListRevIter<const_value_type>;

private:
    using   non_const_value_type    = typename std::remove_const<value_type>::type;

    using   const_container         = List<const_value_type>;
    using   non_const_iterator      = ListRevIter<non_const_value_type>;
    using   non_const_container     = List<non_const_value_type>;

    using   container_node          = typename container::Node;

    // Objects lifetime
private:
    explicit            ListRevIter( void* currPtr );

public:
                        ListRevIter( const self_type& )     = default;
    self_type&          operator=( const self_type& )       = default;
                        ~ListRevIter()                      = default;

    // Public operators
public:
                        operator const_iterator()               const;

    bool                operator==( const self_type& other )    const;
    bool                operator!=( const self_type& other )    const;

    self_type&          operator++();
    self_type           operator++( int );
    self_type&          operator--();
    self_type           operator--( int );

private:
    friend class    non_const_iterator;     // Protected ctor
    friend class    non_const_container;    // Private fpNode
    friend class    const_container;        // Private fpNode

    // The rest of the operators and fields are inherited from ListIter
};

#include "ListIter.ipp"

#endif // !_LIST_ITERATOR_HEADER_INCLUDED_
