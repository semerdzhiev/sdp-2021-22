#include <iostream>

/**
 * Напишете функция за сумата на две матрици.
 */
constexpr uint16_t  M   = 3;
constexpr uint16_t  N   = 4;
void SumMatrices( const float mat1[][N], const float mat2[][N] )
{
    for ( uint16_t i = 0; i < m; i++ )
    {
        for ( uint16_t j = 0; j < n; j++ )
        {
            std::cout << mat1[ i ][ j ] + mat2[ i ][ j ] << "\t";
        }
        std::cout << "\n";
    }
}

int main()
{
    float   mat1[ M ][ N ]  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    float   mat2[ M ][ N ]  = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24 };

    SumMatrices( mat1, mat2 );

    return 0;
}
