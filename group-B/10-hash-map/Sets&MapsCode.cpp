//#define _SETS_MAPS_CODE_
#ifdef _SETS_MAPS_CODE_

#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>

// printing out pairs
template<class T, class U>
std::ostream& operator<<( std::ostream& out, const std::pair<T, U>& pair )
{
    return out << '(' << pair.first << ", " << pair.second << ')';
}

int main()
{
    std::set<int>   mySet   = { 2, 6, 3, 1, 5, 4 }; // red-black tree

    std::unordered_set<int> myHashSet   = { 2, 6, 3, 1, 5, 4 }; // hash table

    std::map<int, char> myMap   // red-black tree with key-value pairs
        = { {2, 'B'}, {6, 'F'}, {3, 'C'}, {1, 'A'}, {5, 'E'}, {4, 'D'} };

    std::unordered_map<int, char>   myHashMap   // hash table with key-value pairs
        = { {2, 'B'}, {6, 'F'}, {3, 'C'}, {1, 'A'}, {5, 'E'}, {4, 'D'} };


    std::cout << " --- Set ---\n";

    for ( int val : mySet )
        std::cout << val << ' ';

    std::cout << "\n\n --- Unordered Set ---\n";

    for ( int val : myHashSet )
        std::cout << val << ' ';

    std::cout << "\n\n --- Map ---\n";

    for ( const std::pair<int, char>& pair : myMap )
        std::cout << pair << ' ';

    std::cout << "\n\n --- Unordered Map ---\n";

    for ( const std::pair<int, char>& pair : myHashMap )
        std::cout << pair << ' ';


    std::cout << "\n\n --- Unordered Map changed 6's value to Y ---\n";

    std::unordered_map<int, char>::iterator it = myHashMap.find( 6 );
    if ( it != myHashMap.end() )
        it->second = 'Y';
    
    for ( const std::pair<int, char>& pair : myHashMap )
        std::cout << pair << ' ';

    std::cout << "\n\n --- Unordered Map [ 7 ] = 'M' ---\n";

    //myHashMap[ 7 ];       // finds value of key 7 or creates a pair ( 7, {} )
    myHashMap[ 7 ] = 'M';   // + assignment
    for ( const std::pair<int, char>& pair : myHashMap )
        std::cout << pair << ' ';

    std::cout << "\n\n --- Unordered Map insert (8, N) and (9, Z) ---\n";

    std::pair<int, char> pair = { 8, 'N' };
    myHashMap.insert( pair );
    myHashMap.insert( std::make_pair( 9, 'Z' ) );
    for ( const std::pair<int, char>& pair : myHashMap )
        std::cout << pair << ' ';

    std::cout << "\n\n --- Unordered Map insert (9, P) [same key] ---\n";

    using ResPair = std::pair< std::unordered_map<int, char>::iterator, bool >;
    ResPair resPair = myHashMap.insert( std::make_pair( 9, 'P' ) );

    if ( !resPair.second )
        std::cout << "The container already contains a pair with that key - " << *resPair.first << '\n';

    for ( const std::pair<int, char>& pair : myHashMap )
        std::cout << pair << ' ';

    std::cout << '\n';

	return 0;
}

#endif // !_SETS_MAPS_CODE_
