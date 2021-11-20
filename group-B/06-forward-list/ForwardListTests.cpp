#include <iostream>
#include <forward_list>
#include "ForwardList.hpp"

// Memory leak detection define and libraries
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

int main()
{
    // Unnamed scope so destructors of the lists will be called at the end
    {

        std::forward_list<int>  stdList;
        ForwardList<int>        ourList;

        for ( size_t i = 1; i <= 10; i++ )
        {
            std::cout << i << ' ';
            stdList.push_front( i );
            ourList.push_front( i );
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
        ForwardList<int>    initedList  = { 2, 5, 6, 7, 11 };
        initedList.print();

        std::cout << '\n';

        // Operator= test
        ourList = initedList;

        ourList.print();

        std::cout << '\n';

        // Copy ctor test
        ForwardList<int>    copiedList( ourList );

        copiedList.print();

        std::cout << '\n';

        // Pop front test
        copiedList.pop_front();

        copiedList.print();

        std::cout << '\n';

        // Push front test
        copiedList.push_front( 9 );
        copiedList.push_front( 42 );

        copiedList.print();

        std::cout << '\n';

        // -------------- Task tests --------------
        copiedList.reverse().print();

        std::cout << '\n';

        ForwardList<int>    lst2 = { 10, 30, 20, 20, 40, 20, 30, 30, 10, 10, 10 };
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

    // Detect and dump in the Output window any memory that hasn't been deleted
    _CrtDumpMemoryLeaks();

    return 0;
}
