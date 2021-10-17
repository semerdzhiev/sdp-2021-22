#include <iostream>
#include <cmath>

/**
 * Напишете алгоритъм, който извежда всички прости числа до n
 * Алгоритъмът се нарича "Ситото на Ератостен"
 */
void PrintAllPrimesUpToN( uint32_t last )
{
    // This can be avoided using a vector and .reserve()
    constexpr uint32_t  MAX_N   = 1024;

    if ( last >= 1024 )
    {
        std::cout << "Too large\n";
        return;
    }

    bool    arrIsComposite[ MAX_N ] = { false, };

    for ( uint32_t curr = 2; curr <= last; curr++ )
    {
        if ( arrIsComposite[ curr ] )
            continue;

        for ( uint32_t run = curr; run <= last; run += curr )
            arrIsComposite[ run ]   = true;

        arrIsComposite[ curr ]  = false;
        std::cout << curr << " ";
    }
}

int main()
{
    uint32_t num;
    std::cin >> num;

    PrintAllPrimesUpToN( num );

    return 0;
}
