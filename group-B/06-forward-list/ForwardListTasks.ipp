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
ForwardList<DataType>::erase_repeats()      // TODO: Version with iterators
{
    if ( this->empty() )
        return *this;

    Node*   pCurr   = fpHead;
    Node*   pNext   = fpHead->fpNext;

    while ( pNext )
    {
        if ( pCurr->fData == pNext->fData )
        {
            Node* pTemp     = pNext;
            pCurr->fpNext   = pNext->fpNext;
            delete  pTemp;

            pNext   = pCurr->fpNext;
        }
        else
        {
            pCurr   = pCurr->fpNext;
            pNext   = pCurr->fpNext;
        }
    }

    return *this;
}

#endif // !_FORWARD_LIST_TASKS_IMPLEMENTATION_INCLUDED_
