#include <iostream>

/**
 * Напишете функция, която извежда n-тото число на фибоначи
 */
uint64_t FastNthFibonacci( uint16_t n )
{
    constexpr uint16_t  MAX = 4092;
    static uint64_t     arrMemoisation[ MAX ]   = { 0, };

    if ( n >= MAX )
    {
        std::cout << "Too much";
        return -1;
    }

    if ( n <= 1 )
        return n;

    if ( arrMemoisation[ n ] != 0 )
        return arrMemoisation[ n ];

    uint64_t    res = FastNthFibonacci( n - 2 ) + FastNthFibonacci( n - 1 );
    arrMemoisation[ n ] = res;

    return res;
}

uint64_t SlowNthFibonacci( uint16_t n )
{
    if ( n <= 1 )
        return n;

    return SlowNthFibonacci( n - 2 ) + SlowNthFibonacci( n - 1 );
}

int main()
{
    //std::cout << SlowNthFibonacci( 45 );
    std::cout << FastNthFibonacci( 4091 );

    return 0;
}
