#pragma once
#ifndef _FORWARD_LIST_TASKS_IMPLEMENTATION_INCLUDED_
#define _FORWARD_LIST_TASKS_IMPLEMENTATION_INCLUDED_

#include "ForwardList.hpp"

template<class DataType>
ForwardList<DataType>&
ForwardList<DataType>::reverse()
{
    Node*   pPrev   = nullptr;
    Node*   pNext   = fpHead->fpNext;

    while ( pNext )
    {
        fpHead->fpNext  = pPrev;
        pPrev           = fpHead;
        fpHead          = pNext;
        pNext           = pNext->fpNext;
    }

    fpHead->fpNext   = pPrev;

    return *this;
}

template<class DataType>
ForwardList<DataType>&
ForwardList<DataType>::erase_repeats()
{
    if ( this->empty() )
        return *this;

    Node*   pCurr   = fpHead;
    Node*   pNext   = fpHead->fpNext;

    while ( pNext )
    {
        if ( pCurr->fData == pNext->fData )
        {
            pNext   = this->erase_after( pCurr );
        }
        else
        {
            pCurr   = pCurr->fpNext;
            pNext   = pCurr->fpNext;
        }
    }

    return *this;
}

template<class DataType>
ForwardList<DataType>&
ForwardList<DataType>::erase_repeats_iters()
{
    // TODO: Implement using iterators

    return *this;
}

template<class DataType>
ForwardList<DataType>&
ForwardList<DataType>::unique()
{
    for ( Node* pCurr = fpHead; pCurr != nullptr; pCurr = pCurr->fpNext )
    {
        for ( Node* pEraser = pCurr; pEraser->fpNext != nullptr; )
        {
            if ( pCurr->fData == pEraser->fpNext->fData )
                this->erase_after( pEraser );
            else
                pEraser = pEraser->fpNext;
        }
    }

    // Alternative version with iterators
    //self_type::iterator     itCurr      = this->begin();

    //for ( ; itCurr != this->end(); itCurr++ )
    //{
    //    self_type::iterator itEraser    = itCurr;
    //    self_type::iterator itAfterEr   = itCurr;
    //    itAfterEr++;
    //    while ( itAfterEr != this->end() )
    //    {
    //        if ( *itCurr == *itAfterEr )
    //        {
    //            this->erase_after( itEraser );
    //            itAfterEr = itEraser;
    //            itAfterEr++;
    //        }
    //        else
    //        {
    //            itEraser++;
    //            itAfterEr = itEraser;
    //            itAfterEr++;
    //        }
    //    }
    //}

    return *this;
}

template<class DataType>
ForwardList<DataType>&
ForwardList<DataType>::append( self_type other )
{
    if ( this->empty() )
    {
        fpHead  = other.fpHead;
    }
    else
    {
        Node*   pCurr   = fpHead;
        while ( pCurr->fpNext )
            pCurr   = pCurr->fpNext;
        
        pCurr->fpNext   = other.fpHead;
    }

    other.fpHead    = nullptr;

    return *this;
}

template<class DataType>
template<class Predicate>
ForwardList<DataType>&
ForwardList<DataType>::divide_by( Predicate pred )
{
    if ( this->empty() || fpHead->fpNext == nullptr )
        return *this;

    size_t  elemCnt = 1;

    Node*   pLast   = fpHead;
    while ( pLast->fpNext )
    {
        pLast   = pLast->fpNext;
        ++elemCnt;
    }

    Node*   pPrev   = nullptr;
    Node*   pCurr   = fpHead;
    for ( size_t i = 0; i < elemCnt; i++ )
    {
        if ( pred( pCurr->fData ) )
        {
            if ( pCurr == fpHead )
            {
                fpHead          = fpHead->fpNext;
                pLast->fpNext   = pCurr;
                pLast           = pLast->fpNext;
                pCurr           = fpHead;
            }
            else if ( pCurr != pLast )
            {
                pPrev->fpNext   = pCurr->fpNext;
                pLast->fpNext   = pCurr;
                pLast           = pLast->fpNext;
                pCurr           = pPrev->fpNext;
            }

            pLast->fpNext   = nullptr;
        }
        else
        {
            pPrev   = pCurr;
            pCurr   = pCurr->fpNext;
        }
    }

    return *this;
}

#endif // !_FORWARD_LIST_TASKS_IMPLEMENTATION_INCLUDED_
