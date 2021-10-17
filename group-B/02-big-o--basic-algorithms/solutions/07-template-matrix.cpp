#include <iostream>

//----------------------------------------------------------------------------------------------------------------------
template<uint16_t N, class Type>
class MatrixRow
{
public:
                            MatrixRow() = default;
                            MatrixRow( const MatrixRow<N, Type>& other );
                            
    MatrixRow<N, Type>&     operator=( const MatrixRow<N, Type>& other );
    Type&                   operator[]( size_t i );
    const Type&             operator[]( size_t i ) const;
                            
private:                    
    float                   arr[ N ];
};

//----------------------------------------------------------------------------------------------------------------------
template<uint16_t ROWS, uint16_t COLS, class Type>
class Matrix
{
public:
                                    Matrix();
                                    Matrix( const Matrix<ROWS, COLS, Type>& other );
                                    Matrix( const std::initializer_list<float>& lst );

    Matrix<ROWS, COLS, Type>&       operator=( const Matrix<ROWS, COLS, Type>& other );
    MatrixRow<COLS, Type>&          operator[]( size_t i );
    const MatrixRow<COLS, Type>&    operator[]( size_t i ) const;

    template<uint16_t COLS2>
    Matrix<ROWS, COLS2, Type>       operator*( const Matrix<COLS, COLS2, Type>& other );

private:
    MatrixRow<COLS, Type>           mat[ ROWS ];
};

template<uint16_t ROWS, uint16_t COLS, class Type>
std::ostream& operator<<( std::ostream& out, const Matrix<ROWS, COLS, Type>& mat );


//----------------------------------------------------------------------------------------------------------------------
int main()
{
    Matrix<3, 4, float> mat1    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    Matrix<4, 5, float> mat2    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

    std::cout << mat1 << "\n    multiplied by\n" << mat2 << "\n    is equal to\n" << mat1 * mat2 << "\n";

    return 0;
}


//----------------------------------------------------------------------------------------------------------------------
template<uint16_t N, class Type>
MatrixRow<N, Type>::MatrixRow( const MatrixRow<N, Type>& other )
{
    this->operator=( other );
}

template<uint16_t N, class Type>
MatrixRow<N, Type>&
MatrixRow<N, Type>::operator=( const MatrixRow<N, Type>& other )
{
    for ( uint16_t i = 0; i < N; i++ )
        arr[ i ]    = other.arr[ i ];

    return *this;
}

template<uint16_t N, class Type>
Type&
MatrixRow<N, Type>::operator[]( size_t i )
{
    return arr[ i ];
}

template<uint16_t N, class Type>
const Type&
MatrixRow<N, Type>::operator[]( size_t i ) const
{
    return arr[ i ];
}


//----------------------------------------------------------------------------------------------------------------------
template<uint16_t ROWS, uint16_t COLS, class Type>
Matrix<ROWS, COLS, Type>::Matrix()
{
    for ( uint16_t i = 0; i < ROWS; i++ )
        for ( uint16_t j = 0; j < COLS; j++ )
            mat[ i ][ j ]   = 0;
}

template<uint16_t ROWS, uint16_t COLS, class Type>
Matrix<ROWS, COLS, Type>::Matrix( const Matrix<ROWS, COLS, Type>& other )
{
    this->operator=( other );
}

template<uint16_t ROWS, uint16_t COLS, class Type>
Matrix<ROWS, COLS, Type>::Matrix( const std::initializer_list<float>& lst )
{
    auto    it  = lst.begin();
    for ( uint16_t i = 0; i < ROWS; i++ )
        for ( uint16_t j = 0; j < COLS; j++ )
            mat[ i ][ j ]   = *it++;
}

template<uint16_t ROWS, uint16_t COLS, class Type>
Matrix<ROWS, COLS, Type>&
Matrix<ROWS, COLS, Type>::operator=( const Matrix<ROWS, COLS, Type>& other )
{
    for ( uint16_t i = 0; i < ROWS; i++ )
        mat[ i ]    = other.mat[ i ];

    return *this;
}

template<uint16_t ROWS, uint16_t COLS, class Type>
template<uint16_t COLS2>
Matrix<ROWS, COLS2, Type>
Matrix<ROWS, COLS, Type>::operator*( const Matrix<COLS, COLS2, Type>& other )
{
    Matrix<ROWS, COLS2, Type>  res;
    for ( uint16_t i = 0; i < ROWS; i++ )
        for ( uint16_t j = 0; j < COLS2; j++ )
            for ( uint16_t acc = 0; acc < COLS; acc++ )
                res[ i ][ j ] += mat[ i ][ acc ] * other[ acc ][ j ];

    return res;
}

template<uint16_t ROWS, uint16_t COLS, class Type>
MatrixRow<COLS, Type>&
Matrix<ROWS, COLS, Type>::operator[]( size_t i )
{
    return mat[ i ];
}

template<uint16_t ROWS, uint16_t COLS, class Type>
const MatrixRow<COLS, Type>&
Matrix<ROWS, COLS, Type>::operator[]( size_t i ) const
{
    return mat[ i ];
}

template<uint16_t ROWS, uint16_t COLS, class Type>
std::ostream& operator<<( std::ostream& out, const Matrix<ROWS, COLS, Type>& mat )
{
    for ( uint16_t i = 0; i < ROWS; i++ )
    {
        for ( uint16_t j = 0; j < COLS; j++ )
            out << mat[ i ][ j ] << "\t";

        if ( i != ROWS - 1 )
            out << "\n";
    }

    return out;
}
