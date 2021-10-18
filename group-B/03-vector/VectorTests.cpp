#include <iostream>
#include <string>
#include "Vector.hpp"

//------------------------------------------------------------------------------
Vector<int> initVecWithPushBack(size_t count = 5)
{
    Vector<int> vec;
    for ( size_t i = 1; i <= count; i++ )
        vec.push_back( i );

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

    std::cout << " - size ctor: \t\t";
    Vector<int> vec2( 10 );
    std::cout << vec2 << "\n";

    std::cout << " - size + def val ctor: ";
    Vector<int> vec3( 10, 42 );
    std::cout << vec3 << "\n";

    std::cout << " - init list ctor:\t";
    Vector<int> vec4    = { 1, 2, 3, 4, 5 };
    std::cout << vec4 << "\n";

    std::cout << " - cpy ctor: \t\t";
    Vector<int> vec5    = vec4;
    std::cout << vec5 << "\n";

    std::cout << " - operator=: \t\t";
    Vector<int> vec6;
    vec6    = vec5;
    std::cout << vec6 << "\n";
}

//------------------------------------------------------------------------------
void testIter()
{
    std::cout << "\niter test:\t\t";
    
    Vector<int> vec = initVecWithPushBack();
    for ( int& elem : vec )
        elem    *= 2;

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

    it  = vec.erase( it, it + 5 );
    std::cout << " - erase 5 elems:\t" << vec << "\t\t\t, capacity: " << vec.capacity() << "\n";

    vec.pop_back();
    std::cout << " - pop_back:\t\t" << vec << "\t\t\t, capacity: " << vec.capacity() << "\n";

    vec.insert( vec.begin() + 1, 42 );
    std::cout << " - insert at ind 1:\t" << vec << "\t\t\t, capacity: " << vec.capacity() << "\n";

    vec.shrink_to_fit();
    std::cout << " - shrink_to_fit:\t" << vec << "\t\t\t, capacity: " << vec.capacity() << "\n";

    std::cout << " - empty():\t\t" << (vec.empty() ? "true" : "false") << "\t\t\t\t, capacity: " << vec.capacity() << "\n";

    vec.clear();
    std::cout << " - clear: \t\t" << vec << "\t\t\t\t, capacity: " << vec.capacity() << "\n";

    std::cout << " - empty():\t\t" << (vec.empty() ? "true" : "false") << "\t\t\t\t, capacity: " << vec.capacity() << "\n";
}

//------------------------------------------------------------------------------
void testRandomAccess()
{
    constexpr size_t    SIZE    = 250;
    std::cout << "\n random access test with size " << SIZE << ":\n";
    Vector<int> vec = initVecWithPushBack( SIZE );

    std::cout << " - front():\t\t" << vec.front() << "\n";
    std::cout << " - back():\t\t" << vec.back() << "\n";
    std::cout << " - vec[ 13 ]:\t\t" << vec[ 13 ] << "\n";
    std::cout << " - at( 13 ) = 42:\t" << (vec.at( 13 ) = -42) << "\n";
    std::cout << " - vec[ 13 ]:\t\t" << vec[ 13 ] << "\n";

    try
    {
        std::cout << " - vec.at( SIZE ):\t";
        std::cout << vec.at( SIZE );
    }
    catch ( const std::out_of_range& e )
    {
        std::cout << e.what() << "\n";
    }
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int main()
{
    testPushBack();
    testCtors();
    testIter();
    testConstness();
    testIters();
    testRandomAccess();

    return 0;
}
