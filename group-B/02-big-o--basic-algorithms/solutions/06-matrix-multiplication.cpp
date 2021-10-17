#include <iostream>

/**
 * Напишете функция за произведението на две матрици.
 */
constexpr uint16_t  M   = 3;
constexpr uint16_t  N   = 4;
constexpr uint16_t  P   = 5;
void SumMatrices( const float mat1[][ N ], const float mat2[][ P ])
{
    for ( uint16_t i = 0; i < M; i++ )
    {
        for ( uint16_t j = 0; j < P; j++ )
        {
            float   res = 0;
            for ( uint16_t acc = 0; acc < N; acc++ )
                res += mat1[ i ][ acc ] * mat2[ acc ][ j ];

            std::cout << res << "\t";
        }
        std::cout << "\n";
    }
}

int main()
{
    float   mat1[ M ][ N ]  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    float   mat2[ N ][ P ]  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

    SumMatrices( mat1, mat2 );

    return 0;
}
