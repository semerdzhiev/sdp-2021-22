#pragma once
#include "Vector.hpp"

template<class DataType>
typename Vector<DataType>::const_iterator
Vector<DataType>::find( const DataType& elem ) const
{
    const_iterator  it  = this->cbegin();
    for ( ; it != this->cend(); it++ )
        if ( *it == elem )
            return it;

    return this->cend();
}

template<class DataType>
Vector<DataType>
Vector<DataType>::reverse() const
{
    Vector<DataType>    res( *this );

    for ( size_t i = 0; i < this->size() / 2; i++ )
        std::swap( res[ i ], res[ this->size() - i - 1 ] );

    return res;
}

template<class DataType>
bool
Vector<DataType>::isSuperSetOf( const Vector<DataType>& other ) const
{
    for ( const DataType& elem : other )
        if ( !this->contains( elem ) )
            return false;

    return true;
}

template<class DataType>
Vector<DataType>&
Vector<DataType>::apply( void (*func)(DataType&) )
{
    for ( DataType& elem : *this )
        func( elem );

    return *this;
}

template<class DataType>
template<class Predicate>
Vector<DataType>
Vector<DataType>::filter( Predicate pred ) const
{
    Vector<DataType>    res;

    for ( const DataType& elem : *this )
        if ( pred( elem ) )
            res.push_back( elem );

    return res;
}

template<class DataType>
typename Vector<DataType>::iterator
Vector<DataType>::findKthLargest( size_t k )
{
    int diff = std::as_const( *this ).findKthLargest( k ) - this->begin();

    return iterator( this->begin() + diff );
}

template<class DataType>
typename Vector<DataType>::const_iterator
Vector<DataType>::findKthLargest( size_t k ) const
{
    if ( k >= this->size() )
        return this->end();

    Vector<DataType>    temp( *this );

    for ( size_t i = 0; i < k; i++ )
    {
        size_t  maxIndex    = i;
        for ( size_t j = i; j < this->size(); j++ )
            if ( temp[ j ] > temp[ maxIndex ] )
                maxIndex = j;

        if ( i != maxIndex )
            std::swap( temp[ i ], temp[ maxIndex ] );
    }

    const DataType&     kthLargest  = temp[ k - 1 ];

    return this->find( kthLargest );
}

template<class DataType>
Vector<DataType>
Vector<DataType>::unique() const
{
    Vector<DataType>    temp( *this );

    std::sort( temp.begin(), temp.end() );

    for ( size_t i = 0; i < temp.size() - 1; i++ )
    {
        if ( temp[ i ] == temp[ i + 1 ] )
        {
            temp.erase( temp.begin() + i + 1 );
            i--;
        }
    }

    return temp;
}
