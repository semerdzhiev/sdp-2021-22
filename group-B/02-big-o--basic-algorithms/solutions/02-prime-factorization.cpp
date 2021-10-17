#include <iostream>
#include <cmath>

/**
 * Напишете функция, която разлага число на прости делители
 */
void PrintPrimeFactorization( uint32_t num )
{
    uint32_t    div = 2;
    while ( num > 1 )
    {
        while ( num % div == 0 )
        {
            std::cout << div << " ";
            num /= div;
        }

        ++div;
    }
}

int main()
{
    uint32_t num;
    std::cin >> num;

    PrintPrimeFactorization( num );

    return 0;
}
