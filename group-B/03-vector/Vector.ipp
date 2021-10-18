#include "Vector.hpp"

template<class DataType>
Vector<DataType>::Vector()
    : fpData( nullptr )
    , fCapacity( 0 )
    , fSize( 0 )
{}

template<class DataType>
Vector<DataType>::Vector( size_t count, const DataType& value )
    : Vector<DataType>()
{
    this->resize( count, value );
}

template<class DataType>
Vector<DataType>::Vector( const std::initializer_list<DataType>& lst )
    : fpData( new DataType[ lst.size() ] )
    , fSize( lst.size() )
    , fCapacity( lst.size() )
{
    std::copy( lst.begin(), lst.end(), this->begin() );
}

template<class DataType>
Vector<DataType>::Vector( const Vector<DataType>& other )
    : fpData( new DataType[ other.fCapacity ] )
    , fSize( other.fSize )
    , fCapacity( other.fCapacity )
{
    std::copy( other.cbegin(), other.cend(), this->begin() );
}

template<class DataType>
Vector<DataType>::Vector( Vector<DataType>&& other )
    : fpData( std::move( other.fpData ) )
    , fSize( std::move( other.fSize ) )
    , fCapacity( std::move( other.fCapacity ) )
{
    other.fpData    = nullptr;
    other.fSize     = 0;
    other.fCapacity = 0;
}

template<class DataType>
Vector<DataType>::~Vector()
{
    this->clear();
}

template<class DataType>
Vector<DataType>&
Vector<DataType>::operator=( Vector<DataType> other )
{
    this->swap( other );
    return *this;
}

template<class DataType>
Vector<DataType>&
Vector<DataType>::operator=( Vector<DataType>&& other )
{
    if ( this != &other )
    {
        this->clear();

        fpData      = std::move( other.fpData );
        fSize       = std::move( other.fSize );
        fCapacity   = std::move( other.fCapacity );

        other.fpData    = nullptr;
        other.fSize     = 0;
        other.fCapacity = 0;
    }
    return *this;
}

template<class DataType>
void
Vector<DataType>::swap( Vector<DataType>& other )
{
    std::swap( fpData       , other.fpData      );
    std::swap( fSize        , other.fSize       );
    std::swap( fCapacity    , other.fCapacity   );
}

template<class DataType>
typename Vector<DataType>::iterator
Vector<DataType>::begin()
{
    return iterator( fpData );
}

template<class DataType>
typename Vector<DataType>::const_iterator
Vector<DataType>::begin() const
{
    return const_iterator( fpData );
}

template<class DataType>
typename  Vector<DataType>::const_iterator
Vector<DataType>::cbegin() const
{
    return const_iterator( fpData );
}

template<class DataType>
typename Vector<DataType>::iterator
Vector<DataType>::end()
{
    return iterator( fpData + fSize );
}

template<class DataType>
typename Vector<DataType>::const_iterator
Vector<DataType>::end() const
{
    return const_iterator( fpData + fSize );
}

template<class DataType>
typename Vector<DataType>::const_iterator
Vector<DataType>::cend() const
{
    return const_iterator( fpData + fSize );
}

template<class DataType>
DataType&
Vector<DataType>::at( size_t index )
{
    return const_cast< DataType& >( std::as_const( *this ).at( index ) );
}

template<class DataType>
const DataType&
Vector<DataType>::at( size_t index ) const
{
    if ( index >= fSize )
        throw std::out_of_range( "Vector operator[ " + std::to_string( index ) + " ]: Index out of range!" );

    return fpData[ index ];
}

template<class DataType>
DataType&
Vector<DataType>::operator[]( size_t index )
{
    return fpData[ index ];
}

template<class DataType>
const DataType&
Vector<DataType>::operator[]( size_t index ) const
{
    return fpData[ index ];
}

template<class DataType>
DataType&
Vector<DataType>::front()
{
    return this->operator[]( 0 );
}

template<class DataType>
const DataType&
Vector<DataType>::front() const
{
    return this->operator[]( 0 );
}

template<class DataType>
DataType&
Vector<DataType>::back()
{
    return this->operator[]( fSize - 1 );
}

template<class DataType>
const DataType&
Vector<DataType>::back() const
{
    return this->operator[]( fSize - 1 );
}

template<class DataType>
DataType*
Vector<DataType>::data()
{
    return fpData;
}

template<class DataType>
const DataType*
Vector<DataType>::data() const
{
    return fpData;
}

template<class DataType>
bool
Vector<DataType>::empty() const
{
    return this->size() == 0;
}

template<class DataType>
size_t
Vector<DataType>::size() const
{
    return fSize;
}

template<class DataType>
size_t
Vector<DataType>::capacity() const
{
    return fCapacity;
}

template<class DataType>
void
Vector<DataType>::shrink_to_fit()
{
    this->resize( fSize );
}

template<class DataType>
void
Vector<DataType>::clear()
{
    delete[] fpData;
    fpData      = nullptr;
    fSize       = 0;
    fCapacity   = 0;
}

template<class DataType>
void
Vector<DataType>::resize( size_t newSize, const DataType& defaultElem )
{
    DataType*   pNewData    = new DataType[ newSize ];

    DataType*   pLast       = fpData + fSize;
    if ( newSize < fSize )
        pLast  = fpData + newSize;
    
    std::copy( fpData, pLast, pNewData );
    
    DataType*   pNewElems   = pNewData + fSize;
    for ( ; pNewElems < pNewData + newSize; pNewElems++ )
        *pNewElems  = defaultElem;

    delete[] fpData;
    fpData      = pNewData;
    fSize       = newSize;
    fCapacity   = newSize;
}

template<class DataType>
void
Vector<DataType>::reserve( size_t wantedCapacity )
{
    if ( wantedCapacity <= fCapacity )
        return;

    size_t  newCapacity     = fCapacity;

    if ( newCapacity == 0 )
        newCapacity = START_CAPACITY;

    while ( newCapacity < wantedCapacity )
        newCapacity = (size_t)( newCapacity * GROWTH_FACTOR );

    DataType*   pNewData    = new DataType[ newCapacity ];

    std::copy( fpData, fpData + fSize, pNewData );

    delete[] fpData;
    fpData      = pNewData;
    fCapacity   = newCapacity;
}

template<class DataType>
void
Vector<DataType>::push_back( const DataType& elem )
{
    this->reserve( fSize + 1 );

    fpData[ fSize++ ]  = elem;
}

template<class DataType>
void
Vector<DataType>::pop_back()
{
    --fSize;
}

template<class DataType>
typename Vector<DataType>::iterator
Vector<DataType>::insert( const iterator& posIt, const DataType& value )
{
    this->reserve( this->size() + 1 );

    auto    it  = this->end();
    for ( ; it != posIt; it-- )
        std::swap( *it, *(it - 1) );

    *it = value;

    ++fSize;

    return iterator();
}

template<class DataType>
typename Vector<DataType>::iterator
Vector<DataType>::erase( const iterator& posIt )
{
    return this->erase( posIt, posIt + 1 );
}

template<class DataType>
typename Vector<DataType>::iterator
Vector<DataType>::erase( iterator first, iterator last )
{
    size_t  resIndex   = first - fpData;

    for ( ; last != this->end(); last++, first++ )
        std::swap( *first, *last );

    fSize   -= last - first;

    return iterator( fpData + resIndex );
}

template<class DataType>
std::ostream&
operator<<( std::ostream& out, const Vector<DataType>& vec )
{
    if ( vec.empty() )
    {
        out << "[]";
        return out;
    }

    out << "[";

    typename Vector<DataType>::const_iterator   it  = vec.cbegin();
    out << " " << *it;

    it++;

    for ( ; it != vec.cend(); it++ )
        out << ", " << *it;

    return out << " ]";
}
