#pragma once
#ifndef _LIST_TASKS_IMPLEMENTATION_INCLUDED_
#define _LIST_TASKS_IMPLEMENTATION_INCLUDED_

#include "List.hpp"

template<class DataType>
List<DataType>&
List<DataType>::reverse()
{
    Node*   pCurr   = fpHead;
    while ( pCurr )
    {
        std::swap( pCurr->fpPrev, pCurr->fpNext );
        pCurr   = pCurr->fpPrev;
    }

    std::swap( fpHead, fpTail );

    return *this;
}

template<class DataType>
List<DataType>&
List<DataType>::erase_repeats()
{
    iterator    itCurr  = this->begin();
    iterator    itNext  = ++this->begin();
    iterator    itEnd   = this->end();

    while ( itNext != itEnd )
    {
        if ( *itCurr == *itNext )
        {
            itNext  = this->erase( itNext );
        }
        else
        {
            ++itCurr;
            ++itNext;
        }
    }

    // Alternative without iterators
    //Node*   pCurr   = fpHead;
    //while ( pCurr->fpNext )
    //{
    //    if ( pCurr->fData == pCurr->fpNext->fData )
    //    {
    //        this->erase( pCurr->fpNext );
    //    }
    //    else
    //    {
    //        pCurr   = pCurr->fpNext;
    //    }
    //}

    return *this;
}

template<class DataType>
List<DataType>&
List<DataType>::unique()
{
    iterator    itCurr  = this->begin();
    iterator    itEnd   = this->end();

    for ( ; itCurr != itEnd; itCurr++ )
    {
        iterator    itEraser    = itCurr;
        itEraser++;
        while ( itEraser != itEnd )
        {
            if ( *itCurr == *itEraser )
            {
                itEraser    = this->erase( itEraser );
            }
            else
            {
                ++itEraser;
            }
        }
    }

    // Alternative without iterators
    //Node*   pCurr   = fpHead;
    //for ( ; pCurr; pCurr = pCurr->fpNext )
    //{
    //    Node*   pEraser = pCurr->fpNext;
    //    while ( pEraser )
    //    {
    //        if ( pCurr->fData == pEraser->fData )
    //        {
    //            pEraser = this->erase( pEraser );
    //        }
    //        else
    //        {
    //            pEraser = pEraser->fpNext;
    //        }
    //    }
    //}

    return *this;
}

template<class DataType>
List<DataType>&
List<DataType>::append( self_type other )
{
    if ( this->empty() )
    {
        std::swap( *this, other );
    }
    else if ( ! other.empty() )
    {
        // Connect this' tail and other's head
        fpTail->fpNext          = other.fpHead;
        other.fpHead->fpPrev    = fpTail;

        // Move this' tail
        fpTail                  = other.fpTail;

        // Increase size
        fSize                  += other.fSize;

        // Invalidate other
        other.fpHead            = nullptr;
        other.fpTail            = nullptr;
        other.fSize             = 0;
    }

    return *this;
}

template<class DataType>
template<class Predicate>
List<DataType>&
List<DataType>::divide_by(Predicate pred)
{
    if ( fSize <= 1 )
        return *this;

    // Note: We are not using erase and push_back for performance reasons.
    // These methods deallocate and allocate memory.
    // We don't have to do that, as we are not removing any elements,
    // but instead we're just moving them around.

    // Three pointers used for readibility
    Node*   pPrev   = fpHead->fpPrev;
    Node*   pCurr   = fpHead;
    Node*   pNext   = fpHead->fpNext;

    // Process exactly fSize elements
    for ( size_type i = 0; i < fSize; i++ )
    {
        if ( pred( pCurr->fData ) )
        {
            // Move the head to the next if the head
            // is about to be moved to the back
            if ( pCurr == fpHead )
                fpHead  = pNext;

            // Connect the two nodes around the current
            if ( pPrev )
                pPrev->fpNext   = pNext;

            if ( pNext )
                pNext->fpPrev   = pPrev;

            // Add the current node to the end
            pCurr->fpNext   = nullptr;
            pCurr->fpPrev   = fpTail;
            fpTail->fpNext  = pCurr;
            fpTail          = pCurr;

            // Move the pointers by one except for prev
            pCurr   = pNext;
            if ( pNext )
                pNext   = pNext->fpNext;
        }
        else
        {
            // The current element doesn't satisfy the predicate
            // Move all pointers by one
            pPrev   = pCurr;
            pCurr   = pNext;
            if ( pNext )
                pNext   = pNext->fpNext;
        }
    }

    return *this;
}

#endif // !_LIST_TASKS_IMPLEMENTATION_INCLUDED_
