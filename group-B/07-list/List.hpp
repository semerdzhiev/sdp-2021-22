#pragma once
#ifndef _LIST_HEADER_INCLUDED_
#define _LIST_HEADER_INCLUDED_

#include <iterator>
#include "ListIter.hpp"

//------------------------------------------------------------------------------
template<class DataType>
class List
{
    // STL compatibility and other typenames
public:
    using   value_type              = DataType;
    using   const_value_type        = const DataType;

    using   iterator                = ListIter<value_type>;
    using   const_iterator          = ListIter<const_value_type>;

    using   reverse_iterator        = ListRevIter<value_type>;
    using   const_reverse_iterator  = ListRevIter<const_value_type>;

    // Important!
    //  const_iterator   <==>   const int*
    //  const_iterator    !=    int* const

    using   self_type               = List<value_type>;
    using   pointer                 = value_type*;
    using   reference               = value_type&;
    using   const_pointer           = const_value_type*;
    using   const_reference         = const_value_type&;
    using   difference_type         = ptrdiff_t;
    using   size_type               = size_t;

    // Forward declaration
private:
    struct Node;

    using   init_list   = std::initializer_list<value_type>;

    // Objects lifetime
public:
                        List();
                        List( const init_list& initList );
                        List( const self_type& other );
    self_type&          operator=( const self_type& other );
                        ~List();

    // Public methods
public:
    void                push_front( const_reference elem );
    void                push_back( const_reference elem );
    void                pop_front();
    void                pop_back();

    reference           front()             { return fpHead->fData; }
    const_reference     front()     const   { return fpHead->fData; }

    reference           back()              { return fpTail->fData; }
    const_reference     back()      const   { return fpTail->fData; }

    size_type           size()      const   { return fSize;         }
    bool                empty()     const   { return fSize == 0;    }
    void                clear();    

    const self_type&    print()     const;

    template<class T>
    friend void         swap( List<T>& lhs, List<T>& rhs );

    // Iterator methods
public:
    iterator            begin()             { return iterator( fpHead ); }
    const_iterator      begin()     const   { return iterator( fpHead ); }
    reverse_iterator    rbegin()            { return reverse_iterator( fpTail ); }
    const_reverse_iterator rbegin() const   { return reverse_iterator( fpTail ); }

    iterator            end()               { return iterator( nullptr ); }
    const_iterator      end()       const   { return iterator( nullptr ); }
    reverse_iterator    rend()              { return reverse_iterator( nullptr ); }
    const_reverse_iterator rend()   const   { return reverse_iterator( nullptr ); }

    iterator            insert( iterator position, const_reference elem );
    iterator            erase( iterator position );

    // Tasks
public:
    self_type&          reverse();
    self_type&          erase_repeats();
    self_type&          unique();
    self_type&          append( self_type other );

    template<class Predicate>
    self_type&          divide_by( Predicate pred );

    // Private methods
private:
    Node*               erase( Node* pAfter );

    // Node structure
private:
    struct Node
    {
        Node( const_reference data, Node* prevNode = nullptr, Node* nextNode = nullptr )
            : fData( data ), fpPrev( prevNode ), fpNext( nextNode )
        {}

        value_type  fData;
        Node*       fpPrev;
        Node*       fpNext;
    };

    friend class    iterator;                   // Private Node structure
    friend class    const_iterator;             // Private Node structure
    friend class    reverse_iterator;           // Private Node structure
    friend class    const_reverse_iterator;     // Private Node structure

    // Fields
private:
    Node*       fpHead;
    Node*       fpTail;
    size_type   fSize;
};

#include "List.ipp"
#include "ListTasks.ipp"

#endif // !_LIST_HEADER_INCLUDED_
