#define _LIST_TESTS_
#ifdef _LIST_TESTS_

#include <iostream>
#include <list>
#include "List.hpp"

// Memory leak detection define and libraries
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

int main()
{
    // Unnamed scope so destructors of the lists will be called at the end
    {

        std::list<int>  stdList = { 0 };
        List<int>       ourList = { 0 };

        for ( int i = 1; i <= 5; i++ )
        {
            std::cout << i << ' ';
            stdList.push_back( i );
            ourList.push_back( i );
        }

        for ( int i = 1; i <= 5; i++ )
        {
            std::cout << -i << ' ';
            stdList.push_front( -i );
            ourList.push_front( -i );
        }

        std::cout << '\n';

        for ( int elem : stdList )
            std::cout << elem << ' ';
        std::cout << '\n';

        // Range-based for loop test
        for ( int elem : ourList )
            std::cout << elem << ' ';
        std::cout << '\n';

        ourList.print();

        std::cout << '\n';

        // Initializer list test
        List<int>    initedList  = { 2, 5, 6, 7, 11 };
        initedList.print();

        std::cout << '\n';

        // Operator= test
        ourList = initedList;

        ourList.print();

        std::cout << '\n';

        // Copy ctor test
        List<int>    copiedList( ourList );

        copiedList.print();

        std::cout << '\n';

        // Pop front/back test
        copiedList.pop_front();
        copiedList.pop_front();
        copiedList.pop_back();
        copiedList.pop_back();

        copiedList.print();

        std::cout << '\n';

        // Push front test
        copiedList.push_front( 9 );
        copiedList.push_front( 42 );
        copiedList.push_back( 1337 );

        copiedList.print();

        std::cout << '\n';

        // Insert test
        List<int>::iterator     it  = copiedList.begin();
        std::advance( it, 2 );
        it = copiedList.insert( it, 42 );
        copiedList.insert( it, -42 );

        copiedList.print();

        std::cout << '\n';

        // Reverse iterators test
        List<int>::reverse_iterator itCurr  = copiedList.rbegin();
        List<int>::reverse_iterator itEnd   = copiedList.rend();
        
        for ( ; itCurr != itEnd; itCurr++ )
            std::cout << *itCurr << " ";

        std::cout << '\n';

        itCurr  = ++copiedList.rbegin();
        copiedList.erase( itCurr );

        copiedList.print();

        std::cout << '\n';

        // -------------- Task tests --------------
        copiedList.reverse().print();

        std::cout << '\n';

        List<int>    lst2 = { 10, 30, 20, 20, 40, 20, 30, 30, 10, 10, 10 };
        lst2.print();

        std::cout << '\n';

        lst2.erase_repeats().print();

        std::cout << '\n';

        lst2.unique().print();

        std::cout << '\n';

        lst2.append( copiedList ).print();

        std::cout << '\n';

        auto    isEven  = [] ( int num ) { return num % 2 == 0; };
        lst2.divide_by( isEven ).print();

    }   // Destructors for all lists in the scope will be called here

    // Detect and dump any memory that hasn't been deleted in the Output window
    _CrtDumpMemoryLeaks();

    return 0;
}

#endif // !_LIST_TESTS_
