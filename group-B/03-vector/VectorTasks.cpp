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
Vector<DataType>&       // Why Vector<DataType>& instead of void?
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

template<class DataType>                    // How can we return iterator
typename Vector<DataType>::const_iterator   // instead of const_iterator?
Vector<DataType>::findKthLargest( size_t k ) const
{
    Vector<DataType>    temp( *this );      // Can we avoid copying?

    for ( size_t i = 0; i < k; i++ )        // What would happend if we pass k
    {                                       // that is larger than this->size()?
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
