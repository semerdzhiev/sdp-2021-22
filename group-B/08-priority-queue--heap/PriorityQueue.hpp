#pragma once
#ifndef _PRIORITY_QUEUE_HEADER_INCLUDED_
#define _PRIORITY_QUEUE_HEADER_INCLUDED_

#include <vector>

template<class T, class Container = std::vector<T>, class Comparator = std::less<T>>
class PriorityQueue
{
public:
    using   value_type          = T;
    using   reference           = T&;
    using   const_reference     = T const&;
    using   container_type      = Container;
    using   value_compare       = Comparator;
    using   size_type           = typename Container::size_type;

private:
    using   iterator            = typename Container::iterator;
    using   reverse_iterator    = typename Container::reverse_iterator;
    using   difference_type     = typename iterator::difference_type;

public:
    PriorityQueue() = default;

    template<class InputIt>
    PriorityQueue( InputIt first, InputIt last );

public:
    void                push( const_reference elem );
    void                pop();

    const_reference     top()   const   { return fContainer.front(); }

    bool                empty() const   { return fContainer.empty(); }
    size_type           size()  const   { return fContainer.size();  }

private:
    iterator            parent( iterator it );
    iterator            left_child( iterator it );
    iterator            right_child( iterator it );

    difference_type     index( iterator it );
    iterator            iter( size_type index );

    iterator            begin()         { return fContainer.begin(); }
    iterator            end()           { return fContainer.end();   }
    iterator            rend()          { return fContainer.rend();  }

    iterator            last()          { return --fContainer.end(); }

    void                make_heap();
    void                heapify( iterator it );

private:
    Container   fContainer;
    Comparator  fComparator;
};

#include "PriorityQueue.ipp"

#endif // !_PRIORITY_QUEUE_HEADER_INCLUDED_
