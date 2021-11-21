#pragma once
#ifndef _FORWARD_LIST_HEADER_INCLUDED_
#define _FORWARD_LIST_HEADER_INCLUDED_

#include <iterator>
#include "FListIter.hpp"

//------------------------------------------------------------------------------
template<class DataType>
class ForwardList
{
    // STL compatibility and other typenames
public:
    using   value_type          = DataType;
    using   const_value_type    = const DataType;

    using   iterator            = FListIter<value_type>;
    using   const_iterator      = FListIter<const_value_type>;

    // Important!
    //  const_iterator   <==>   const int*
    //  const_iterator    !=    int* const

    using   self_type           = ForwardList<value_type>;
    using   pointer             = value_type*;
    using   reference           = value_type&;
    using   const_pointer       = const_value_type*;
    using   const_reference     = const_value_type&;
    using   difference_type     = ptrdiff_t;
    using   size_type           = size_t;

    // Forward declaration
private:
    struct Node;

    using   init_list           = std::initializer_list<value_type>;

    // Objects lifetime
public:
                        ForwardList();
                        ForwardList( const init_list& initList );
                        ForwardList( const self_type& other );
      self_type&        operator=( const self_type& other );
                        ~ForwardList();

    // Public methods
public:
    void                push_front( const_reference elem );
    void                pop_front();

    reference           front()         { return fpHead->fData; }
    const_reference     front() const   { return fpHead->fData; }

    bool                empty() const   { return fpHead == nullptr; }
    void                clear();

    const self_type&    print() const;

    // Iterator methods
public:
    iterator            begin()         { return iterator( fpHead ); }
    const_iterator      begin() const   { return iterator( fpHead ); }

    iterator            end()           { return iterator( nullptr ); }
    const_iterator      end()   const   { return iterator( nullptr ); }

    iterator            before_begin()          { return iterator( nullptr, fpHead ); }
    const_iterator      before_begin()  const   { return iterator( nullptr, fpHead ); }

    iterator            insert_after( iterator after, const_reference elem );
    iterator            erase_after( iterator after );

    // Tasks
public:
    self_type&          reverse();
    self_type&          erase_repeats();
    self_type&          erase_repeats_iters();
    self_type&          unique();
    self_type&          append( self_type other );

    template<class Predicate>
    self_type&          divide_by( Predicate pred );

    // Private methods
private:
    void                copy( const self_type& other );
    Node*               erase_after( Node* pAfter );

    // Node structure
private:
    struct Node
    {
        Node( const_reference data, Node* nextNode = nullptr )
            : fData( data ), fpNext( nextNode )
        {}

        value_type  fData;
        Node*       fpNext;
    };

    friend class    iterator;           // Private Node structure
    friend class    const_iterator;     // Private Node structure

    // Fields
private:
    Node*       fpHead;
};

#include "ForwardList.ipp"
#include "ForwardListTasks.ipp"

#endif // !_FORWARD_LIST_HEADER_INCLUDED_
