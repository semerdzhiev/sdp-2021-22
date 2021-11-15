#include <iostream>
#include <string>
#include <cassert>
#include <stack>
#include "Vector.hpp"

Vector<int>     initVecWithPushBack( size_t count = 5 );
void            testPushBack();
void            testCtors();
void            testIter();
void            testConstness();
void            testIters();
void            testRandomAccess();

void            task1Find();
void            task2Reverse();
void            task3Superset();
void            task4Apply();
void            task5Filter();
void            task6KthLargest();

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int main()
{
    //testPushBack();
    //testCtors();
    //testIter();
    //testConstness();
    //testIters();
    //testRandomAccess();

    //task1Find();
    //task2Reverse();
    //task3Superset();
    //task4Apply();
    //task5Filter();
    task6KthLargest();

    return 0;
}


//------------------------------------------------------------------------------
void square( int& num )
{
    num *= num;
}

//------------------------------------------------------------------------------
//--------------------------------- TASK TESTS ---------------------------------
//------------------------------------------------------------------------------
void task1Find()
{
    Vector<int> vec     = initVecWithPushBack();
    //std::vector<int>    vec  = { 1, 2, 3, 4, 5 };

    Vector<int>::const_iterator         it      = vec.find( 5 );
    //std::vector<int>::const_iterator    it     = std::find( vec.cbegin(), vec.cend(), 5 );

    // std::find is from the algorithm library
    //  to use it -> #include <algorithm>

    if ( it != vec.cend() )
    {
        std::cout << *it;
    }
    else
    {
        std::cout << "not found!";
    }
}

//------------------------------------------------------------------------------
void task2Reverse()
{
    Vector<int> vec     = initVecWithPushBack();
    std::cout << vec << '\n';
    std::cout << vec.reverse();
}

//------------------------------------------------------------------------------
void task3Superset()
{
    Vector<int> vec     = { 0, 1, 2, 3, 4, 5 };
    Vector<int> subVec  = { 0, 5, 1 };

    std::cout << vec.isSuperSetOf( subVec );
}

//------------------------------------------------------------------------------
void task4Apply()
{
    Vector<int>         vec     = { 0, 1, 2, 3, 4, 5 };

    std::cout << vec.apply( square );
}

//------------------------------------------------------------------------------
void task5Filter()
{
    Vector<int>         vec     = { 0, 1, 2, 3, 4, 5 };

    // Lambda function / Anonymous function
    // [ captures ] ( params ) -> return_type { body }

    std::cout << vec.filter( [] ( int num ) { return num % 2 == 0; } );
}


void task6KthLargest()
{
    Vector<int>         vec     = { 4, 2, 6, 10, 13, 0, -2 };

    Vector<int>::const_iterator it  = vec.findKthLargest( 2 );
    if ( it != vec.end() )
    {
        std::cout << *it;
    }
    else
    {
        std::cout << "No such element";
    }
}


//------------------------------------------------------------------------------
//---------------------------- IMPLEMENTATION TESTS ----------------------------
//------------------------------------------------------------------------------
Vector<int> initVecWithPushBack( size_t count )
{
    Vector<int> vec;
    for ( size_t i = 1; i <= count; i++ )
        vec.push_back( i );

    assert( vec.size() == count && vec[ 0 ] == 1 );

    return vec;
}

//------------------------------------------------------------------------------
struct Student
{
    std::string name    = "";
    size_t      fn      = 0;
};

std::ostream& operator<<( std::ostream& out, const Student& st )
{
    return out << "{ " << st.name << ", " << st.fn << " }";
}

//------------------------------------------------------------------------------
void testPushBack()
{
    std::cout << "push_back() test:\n";
    std::cout << " - ints:\t" << initVecWithPushBack( 10 ) << "\n";

    Vector<Student> vec;
    vec.push_back( { "Pesho"    , 45001 } );
    vec.push_back( { "Gosho"    , 45002 } );
    vec.push_back( { "Tosho"    , 45003 } );
    vec.push_back( { "Ivancho"  , 45004 } );
    vec.push_back( { "Mariika"  , 45005 } );

    std::cout << " - structs:\t" << vec << "\n";
}

//------------------------------------------------------------------------------
void testCtors()
{
    std::cout << "\nctors test:\n";

    std::cout << " - default ctor: \t";
    Vector<int> vec;
    std::cout << vec << "\n";

    assert( vec.empty() );

    std::cout << " - size ctor: \t\t";
    Vector<int> vec2( 10 );
    std::cout << vec2 << "\n";

    assert( vec2.size() == 10 );

    std::cout << " - size + def val ctor: ";
    Vector<int> vec3( 10, 42 );
    std::cout << vec3 << "\n";

    assert( vec3.size() == 10 && vec3[ 9 ] == 42 );

    std::cout << " - init list ctor:\t";
    Vector<int> vec4    = { 1, 2, 3, 4, 5 };
    std::cout << vec4 << "\n";

    assert( vec4.size() == 5 && vec4[ 3 ] == 4 );

    std::cout << " - cpy ctor: \t\t";
    Vector<int> vec5    = vec4;
    std::cout << vec5 << "\n";

    assert( vec5.size() == 5 && vec5[ 3 ] == 4 );

    std::cout << " - operator=: \t\t";
    Vector<int> vec6;
    vec6    = vec5;
    std::cout << vec6 << "\n";

    assert( vec6.size() == 5 && vec6[ 3 ] == 4 );
}

//------------------------------------------------------------------------------
void testIter()
{
    std::cout << "\niter test:\t\t";

    Vector<int> vec = initVecWithPushBack();
    for ( int& elem : vec )
        elem    *= 2;

    assert( vec[ 2 ] == 6 );

    /**
    * Range-based for loop:
    * 
    * for ( <type> elem : vec )
    * {
    *   // code
    * }
    * 
    * Is roughly equivalent to:
    * 
    * {
    *   auto    it      = vec.begin();
    *   auto    last    = vec.end();
    *   for ( ; it != last; it++ )
    *   {
    *       <type>  elem    = *it;
    *       // code
    *   }
    * }
    */

    std::cout << vec << "\n";
}

//------------------------------------------------------------------------------
void testConstness()
{
    const Vector<int> vec = initVecWithPushBack();

    // vec.                        // only shows const methods: ✓

    //for ( int& elem : vec )               // doesn't compile: ✓
    for ( int elem : vec )          elem;   // compiles:        ✓
    for ( const int& elem : vec )   elem;   // compiles:        ✓

                                            // doesn't compile: ✓
                                            //Vector<int>::iterator   it  = vec.begin();

                                            // compiles: ✓
    Vector<int>::const_iterator   it  = vec.begin();
    // *it = 10;   // doesn't compile: ✓
}

//------------------------------------------------------------------------------
void testIters()
{
    std::cout << "\niters and manips test:\n";
    Vector<int>             vec = initVecWithPushBack( 10 );
    Vector<int>::iterator   it  = vec.begin();

    it += 2;

    it  = vec.erase( it );
    std::cout << " - erase 3rd elem:\t" << vec << "\t, capacity: " << vec.capacity() << "\n";

    assert( vec.size() == 9 );

    it  = vec.erase( it, it + 5 );
    std::cout << " - erase 5 elems:\t" << vec << "\t\t\t, capacity: " << vec.capacity() << "\n";

    assert( vec.size() == 4 );

    vec.pop_back();
    std::cout << " - pop_back:\t\t" << vec << "\t\t\t, capacity: " << vec.capacity() << "\n";

    assert( vec.size() == 3 );

    vec.insert( vec.begin() + 1, 42 );
    std::cout << " - insert at ind 1:\t" << vec << "\t\t\t, capacity: " << vec.capacity() << "\n";

    assert( vec.size() == 4 );

    vec.shrink_to_fit();
    std::cout << " - shrink_to_fit:\t" << vec << "\t\t\t, capacity: " << vec.capacity() << "\n";

    assert( vec.capacity() == vec.size() );

    std::cout << " - empty():\t\t" << (vec.empty() ? "true" : "false") << "\t\t\t\t, capacity: " << vec.capacity() << "\n";

    assert( !vec.empty() );

    vec.clear();
    std::cout << " - clear: \t\t" << vec << "\t\t\t\t, capacity: " << vec.capacity() << "\n";

    assert( vec.size() == 0 && vec.capacity() == 0 );

    std::cout << " - empty():\t\t" << (vec.empty() ? "true" : "false") << "\t\t\t\t, capacity: " << vec.capacity() << "\n";

    assert( vec.empty() );
}

//------------------------------------------------------------------------------
void testRandomAccess()
{
    constexpr size_t    SIZE    = 250;
    std::cout << "\n random access test with size " << SIZE << ":\n";
    Vector<int> vec = initVecWithPushBack( SIZE );

    std::cout << " - front():\t\t" << vec.front() << "\n";
    assert( vec.front() == 1 );

    std::cout << " - back():\t\t" << vec.back() << "\n";
    assert( vec.back() == 250 );

    std::cout << " - vec[ 13 ]:\t\t" << vec[ 13 ] << "\n";
    assert( vec[13] == 14 );

    std::cout << " - at( 13 ) = -42:\t" << (vec.at( 13 ) = -42) << "\n";
    assert( vec.at(13) == -42 );

    std::cout << " - vec[ 13 ]:\t\t" << vec[ 13 ] << "\n";
    assert( vec[13] == -42 );

    try
    {
        std::cout << " - vec.at( SIZE ):\t";
        std::cout << vec.at( SIZE );

        assert( false );    // Unreachable code
    }
    catch ( const std::out_of_range& e )
    {
        std::cout << e.what() << "\n";
    }
}
