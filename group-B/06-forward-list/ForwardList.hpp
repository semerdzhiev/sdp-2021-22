#pragma once
#include <iterator>

// Forward declaration
template<class DataType>
class FListIter;

//------------------------------------------------------------------------------
template<class DataType>
class ForwardList
{
    // STL compatibility
public:
    using   iterator            = FListIter<DataType>;
    using   const_iterator      = FListIter<const DataType>;

    // Important!
    //  const_iterator   <==>   const int*
    //  const_iterator    !=    int* const

    using   self_type           = ForwardList<DataType>;
    using   value_type          = DataType;
    using   pointer             = DataType*;
    using   reference           = DataType&;
    using   const_pointer       = DataType const*;
    using   const_reference     = DataType const&;
    using   difference_type     = ptrdiff_t;
    using   size_type           = size_t;

    // Forward declaration
private:
    struct Node;

    // Objects lifetime
public:
                        ForwardList();
                        ForwardList( const std::initializer_list<value_type>& lst );
                        ForwardList( const self_type& other );
      self_type&        operator=( const self_type& other );
                        ~ForwardList();

    // Public methods
public:
    void                push_front( const_reference elem );
    void                pop_front();

    //void                push_back( const_reference elem );    // Note: Not in STL

    reference           front()         { return fpHead->fData; }
    const_reference     front() const   { return fpHead->fData; }

    bool                empty() const   { return fpHead == nullptr; }
    void                clear();

    //size_type           size() const;   // Note: Not in STL;
    void                print() const;

    iterator            begin()         { return iterator( fpHead ); }
    const_iterator      begin() const   { return iterator( fpHead ); }

    iterator            end()           { return iterator( nullptr ); }
    const_iterator      end()   const   { return iterator( nullptr ); }

    iterator            insert_after( iterator after, const_reference elem );

    // Private methods
private:
    void                copy( const self_type& other );

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

    friend class    iterator;

    // Fields
private:
    Node*       fpHead;
    //Node*       fpTail; // Note: Not in STL
    //size_type   fSize;  // Note: Not in STL
};


//------------------------------------------------------------------------------
template<class DataType>
class FListIter
{
    // STL compatibility
public:
    using   iterator_category   = std::forward_iterator_tag;
    using   value_type          = DataType;
    using   difference_type     = std::ptrdiff_t;
    using   pointer             = DataType*;
    using   reference           = DataType&;

    using   const_pointer       = DataType const*;
    using   const_reference     = DataType const&;
    using   self_type           = FListIter<DataType>;
    using   container           = ForwardList<DataType>;
    using   container_node      = typename container::Node;

public:
    explicit            FListIter( void* ptr = nullptr );
                        FListIter( const self_type& )               = default;
                        ~FListIter()                                = default;

    self_type&          operator=( const self_type& )               = default;
    self_type&          operator=( container_node* ptr );

    explicit            operator bool()                                 const;
                        operator FListIter<DataType const>()            const;

    bool                operator==( const self_type& other )            const;
    bool                operator!=( const self_type& other )            const;

    self_type&          operator++();
    self_type           operator++( int );

    reference           operator*()             { return fpNode->fData; }
    const_reference     operator*()     const   { return fpNode->fData; }

    pointer             operator->()            { return &fpNode->fData; }
    const_pointer       operator->()    const   { return &fpNode->fData; }

private:
    friend class    container;

private:
    container_node*     fpNode;
};

#include "ForwardList.ipp"
#include "FListIter.ipp"
