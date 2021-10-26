#pragma once

#include <iostream>
#include <utility>
#include <iterator>
#include <algorithm>
#include <initializer_list>

// Forward declaration
template<class DataType>
class VecIter;


//------------------------------------------------------------------------------
template<class DataType>
class Vector
{
private:
    static constexpr size_t     START_CAPACITY  = 4;
    static constexpr float      GROWTH_FACTOR   = 1.5f;

public:
    using   iterator        = VecIter<DataType>;
    using   const_iterator  = VecIter<const DataType>;

    // Important!
    // const_iterator   <==>   const int*
    // const_iterator    !=    int* const

    // Big four (and a half?) (five?) + more
public:
                        Vector();
                        Vector( size_t count, const DataType& value = DataType() );
                        Vector( const std::initializer_list<DataType>& lst );
                        Vector( const Vector<DataType>& other );
                        Vector( Vector<DataType>&& other );
                        ~Vector();

    Vector&             operator=( Vector<DataType> other );    // Copy-and-swap idiom
    Vector&             operator=( Vector<DataType>&& other );

    void                swap( Vector<DataType>& other );

    // Iterators
public:
    iterator            begin();
    const_iterator      begin()     const;
    const_iterator      cbegin()    const;

    iterator            end();
    const_iterator      end()       const;
    const_iterator      cend()      const;

    // Element access
public:
    DataType&           at( size_t index );
    DataType const&     at( size_t index ) const;

    DataType&           operator[]( size_t index );
    DataType const&     operator[]( size_t index ) const;

    DataType&           front();
    DataType const&     front()     const;

    DataType&           back();
    DataType const&     back()      const;

    DataType*           data();
    DataType const*     data()      const;

    // Size and capacity
public:
    bool                empty()     const;
    size_t              size()      const;
    size_t              capacity()  const;

    void                shrink_to_fit();

    // Modifiers
public:
    void                clear();
    void                resize( size_t newSize, const DataType& defaultElem = DataType() );
    void                reserve( size_t newCapacity );

    void                push_back( const DataType& elem );
    void                pop_back();

    iterator            insert( const iterator& posIt, const DataType& value );
    iterator            erase( const iterator& posIt );
    iterator            erase( iterator first, iterator last );

    // Tasks
public:
    const_iterator      find( const DataType& elem )                    const;
    Vector<DataType>    reverse()                                       const;
    bool                isSuperSetOf( const Vector<DataType>& other )   const;
    Vector<DataType>&   apply( void (*func)(DataType&) );

    template<class Predicate>
    Vector<DataType>    filter( Predicate pred )                        const;

    const_iterator      findKthLargest( size_t k )                      const;

public:
    bool                contains( const DataType& elem )                const;

    // Private fields
private:
    DataType*       fpData;
    size_t          fSize;
    size_t          fCapacity;
};


//------------------------------------------------------------------------------
template<class DataType>
class VecIter
{
    // STL compatibility
public:
    using   iterator_category   = std::random_access_iterator_tag;
    using   value_type          = DataType;
    using   difference_type     = std::ptrdiff_t;
    using   pointer             = DataType*;
    using   const_pointer       = DataType const*;
    using   reference           = DataType&;
    using   const_reference     = DataType const&;
    using   self_type           = VecIter<DataType>;

public:
    explicit            VecIter( pointer ptr = nullptr );
                        VecIter( const self_type& )                 = default;
                        ~VecIter()                                  = default;

    self_type&          operator=( const self_type& )               = default;
    self_type&          operator=( pointer ptr );

    explicit            operator bool()                                 const;
                        operator VecIter<DataType const>()              const;

    bool                operator==( const self_type& other )            const;
    bool                operator!=( const self_type& other )            const;

    self_type&          operator+=( const difference_type& movement );
    self_type&          operator-=( const difference_type& movement );
    self_type&          operator++();
    self_type&          operator--();
    self_type           operator++( int );
    self_type           operator--( int );
    self_type           operator+( const difference_type& movement )    const;
    self_type           operator-( const difference_type& movement )    const;

    difference_type     operator-( const self_type& other )             const;

    reference           operator*()             { return *fpData; }
    const_reference     operator*()     const   { return *fpData; }

    pointer             operator->()            { return fpData;  }
    const_pointer       operator->()    const   { return fpData;  }

private:
    pointer     fpData;
};


#include "VecIter.ipp"
#include "Vector.ipp"
#include "VectorTasks.ipp"
