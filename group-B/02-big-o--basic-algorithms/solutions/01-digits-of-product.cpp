#include <iostream>
#include <cmath>

/**
 * Напишете функция, която приема 3 числа от интервала
 * [0; 10'000'000] и намира броя на цифрите на
 * произведението им.
 */
int ProductDigitsCount( uint32_t num1, uint32_t num2, uint32_t num3 )
{
    // Math trick 1: floor( log10(a) ) = ( #digits of a ) - 1
    // Math trick 2: log( a*b ) = log( a ) + log( b )
    return (int) (log10( num1 ) + log10( num2 ) + log10( num3 )) + 1;
}

int main()
{
    uint32_t num1, num2, num3;
    std::cin >> num1 >> num2 >> num3;

    std::cout   << num1 << " * " << num2 << " * " << num3 << " has " 
                << ProductDigitsCount( num1, num2, num3 ) << " digits\n";

    return 0;
}
