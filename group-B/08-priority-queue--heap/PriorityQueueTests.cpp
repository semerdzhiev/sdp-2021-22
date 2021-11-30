#define _PRIORITY_QUEUE_TESTS_
#ifdef _PRIORITY_QUEUE_TESTS_

#include <iostream>
#include <queue>
#include "PriorityQueue.hpp"

// Memory leak detection define and libraries
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

template<class PQueue>
void printPriorityQueue( PQueue pq )
{
    while ( ! pq.empty() )
    {
        std::cout << pq.top() << ' ';
        pq.pop();
    }
}

int main()
{
    // Unnamed scope so destructors of the lists will be called at the end
    {
        std::vector<int>            arr = { 5, 10, 31, 20, 15, 7, 13 };

        std::priority_queue<int>    stdPq;
        PriorityQueue<int>          ourPq;

        // Push/pop tests

        for ( size_t i = 0; i < 10; i++ )
        {
            int randNum = std::rand() % 20;
            stdPq.push( randNum );
            ourPq.push( randNum );
        }

        printPriorityQueue( stdPq );
        std::cout << '\n';
        printPriorityQueue( ourPq );

        std::cout << '\n';

        // Make heap test
        std::priority_queue<int>    stlBuiltHeap( arr.begin(), arr.end() );
        PriorityQueue<int>          ourBuiltHeap( arr.begin(), arr.end() );

        printPriorityQueue( stlBuiltHeap );
        std::cout << '\n';
        printPriorityQueue( ourBuiltHeap );

        std::cout << '\n';

        // Comparator test
        std::priority_queue<int, std::vector<int>, std::greater<int>>
            stlBuiltMinHeap( arr.begin(), arr.end() );

        PriorityQueue<int, std::vector<int>, std::greater<int>>
            ourBuiltMinHeap( arr.begin(), arr.end() );

        printPriorityQueue( stlBuiltMinHeap );
        std::cout << '\n';
        printPriorityQueue( ourBuiltMinHeap );

    }   // Destructors for all lists in the scope will be called here

        // Detect and dump any memory that hasn't been deleted in the Output window
    _CrtDumpMemoryLeaks();

    return 0;
}

#endif // !_PRIORITY_QUEUE_TESTS_
