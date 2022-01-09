#pragma once
#ifndef _FORWARD_LIST_HEADER_INCLUDED_
#define _FORWARD_LIST_HEADER_INCLUDED_

#include <iostream>
#include <vector>
#include <forward_list>

template<class Key, class Value, class Hash = std::hash<Key>>
class HashMap
{
public:
                    HashMap();
                    HashMap( size_t buckets );
                    HashMap( const HashMap& )       = default;
    HashMap&        operator=( const HashMap& )     = default;
                    ~HashMap()                      = default;

    struct Data
    {
        Key     fKey;
        Value   fValue;
    };

    bool            insert( const Key& key, const Value& value );
    bool            insert( const Data& pair );
    bool            erase( const Key& key );
    void            clear();

    bool            contains( const Key& key ) const;
    Value&          operator[]( const Key& key );
    Value&          at( const Key& key );
    const Value&    at( const Key& key ) const;

    size_t          size()              const;
    size_t          bucket_count()      const;
    float           load_factor()       const;
    float           max_load_factor()   const;

    void            max_load_factor( float factor );
    void            rehash( size_t bucketsCount );
    void            reserve( size_t elemsCount );

    template<class Func>
    void            for_each( Func func );

    template<class Func>
    void            for_each( Func func ) const;
    void            print( std::ostream& out = std::cout ) const;

private:
    size_t          hash( const Key& key ) const;
    const Data*     find( const Key& key ) const;
    Data*           find( const Key& key );
    Data*           add( const Key& key, const Value& value = {} );
    Data*           add( const Data& pair );

private:
    using HashRow       = std::forward_list< Data >;
    using HashTableArr  = std::vector< HashRow >;
    HashTableArr    fArr;
    Hash            fHashFunc;
    size_t          fSize;
    float           fMaxLoadFactor;
};
// ---------------------- End of class HashMap declaration ---------------------


template<class Key, class Value, class Hash>
std::ostream& operator<<( std::ostream& out, const HashMap<Key, Value, Hash>& map )
{
    map.print( out );
    return out;
}


const size_t    DEFAULT_BUCKET_COUNT       = 8;
const float     DEFAULT_MAX_LOAD_FACTOR    = 1;


template<class Key, class Value, class Hash>
inline HashMap<Key, Value, Hash>::HashMap()
    : fArr( DEFAULT_BUCKET_COUNT )
    , fSize( 0 )
    , fMaxLoadFactor( DEFAULT_MAX_LOAD_FACTOR )
{}


template<class Key, class Value, class Hash>
inline HashMap<Key, Value, Hash>::HashMap( size_t buckets )
    : fArr( buckets )
    , fSize( 0 )
    , fMaxLoadFactor( DEFAULT_MAX_LOAD_FACTOR )
{}


template<class Key, class Value, class Hash>
inline bool HashMap<Key, Value, Hash>::insert( const Key& key, const Value& value )
{
    return this->insert( { key, value } );
}


template<class Key, class Value, class Hash>
inline bool HashMap<Key, Value, Hash>::insert( const Data& pair )
{
    if ( this->contains( pair.fKey ) )
        return false;

    this->add( pair );

    return true;
}


template<class Key, class Value, class Hash>
inline bool HashMap<Key, Value, Hash>::erase( const Key& key )
{
    size_t index = this->hash( key );

    typename HashRow::iterator  eraserIt    = fArr[ index ].before_begin();
    typename HashRow::iterator  comparerIt  = fArr[ index ].begin();

    for ( ; comparerIt != fArr[ index ].end(); ++eraserIt, ++comparerIt )
    {
        if ( comparerIt->fKey == key )
        {
            fArr[ index ].erase_after( eraserIt );
            --fSize;
            return true;
        }
    }

    return false;
}


template<class Key, class Value, class Hash>
inline void HashMap<Key, Value, Hash>::clear()
{
    fArr.clear();
    fSize = 0;
}


template<class Key, class Value, class Hash>
inline bool HashMap<Key, Value, Hash>::contains( const Key& key ) const
{
    if ( this->find( key ) )
        return true;

    return false;
}


template<class Key, class Value, class Hash>
inline Value& HashMap<Key, Value, Hash>::operator[]( const Key& key )
{
    if ( Data* found = this->find( key ) )
        return found->fValue;
    
    return this->add( key )->fValue;
}


template<class Key, class Value, class Hash>
inline Value& HashMap<Key, Value, Hash>::at( const Key& key )
{
    return const_cast< Value& >( std::as_const( *this ).at( key ) );
}


template<class Key, class Value, class Hash>
inline const Value& HashMap<Key, Value, Hash>::at( const Key& key ) const
{
    if ( Data* found = this->find( key ) )
        return found->fValue;

    throw std::out_of_range( "HashMap: at(...) key not found in the hashmap!" );
}


template<class Key, class Value, class Hash>
inline size_t HashMap<Key, Value, Hash>::size() const
{
    return fSize;
}


template<class Key, class Value, class Hash>
inline size_t HashMap<Key, Value, Hash>::bucket_count() const
{
    return fArr.size();
}


template<class Key, class Value, class Hash>
inline float HashMap<Key, Value, Hash>::load_factor() const
{
    return (float)this->size() / this->bucket_count();
}


template<class Key, class Value, class Hash>
inline float HashMap<Key, Value, Hash>::max_load_factor() const
{
    return fMaxLoadFactor;
}


template<class Key, class Value, class Hash>
inline void HashMap<Key, Value, Hash>::max_load_factor( float factor )
{
            fMaxLoadFactor  = factor;
    size_t  minBuckets      = std::ceil( this->size() / this->max_load_factor() );

    if ( this->bucket_count() < minBuckets )
        this->rehash( minBuckets );
}


template<class Key, class Value, class Hash>
inline void HashMap<Key, Value, Hash>::rehash( size_t bucketsCount )
{
    size_t minBuckets = std::ceil( this->size() / this->max_load_factor() );
    if ( bucketsCount < minBuckets )
        bucketsCount = minBuckets;

    if ( this->bucket_count() == bucketsCount )
        return;

    HashTableArr newArr( bucketsCount );
    std::swap( fArr, newArr );
    fSize = 0;

    for ( const std::forward_list< Data >& list : newArr )
        for ( const Data& elem : list )
            this->insert( elem.fKey, elem.fValue );
}


template<class Key, class Value, class Hash>
inline void HashMap<Key, Value, Hash>::reserve( size_t elemsCount )
{
    this->rehash( std::ceil( elemsCount / this->max_load_factor() ) );
}


template<class Key, class Value, class Hash>
template<class Func>
inline void HashMap<Key, Value, Hash>::for_each( Func func )
{
    for ( std::forward_list< Data >& list : fArr )
        for ( Data& elem : list )
            func( elem );
}


template<class Key, class Value, class Hash>
template<class Func>
inline void HashMap<Key, Value, Hash>::for_each( Func func ) const
{
    for ( const std::forward_list< Data >& list : fArr )
        for ( const Data& elem : list )
            func( elem );
}


template<class Key, class Value, class Hash>
inline void HashMap<Key, Value, Hash>::print( std::ostream& out ) const
{
    this->for_each( 
        [&] ( const Data& pair ) {
            out << "(" << pair.fKey << ", " << pair.fValue << ") ";
        }
    );
}


template<class Key, class Value, class Hash>
inline size_t HashMap<Key, Value, Hash>::hash( const Key& key ) const
{
    return fHashFunc( key ) % this->bucket_count();
}


template<class Key, class Value, class Hash>
inline typename const HashMap<Key, Value, Hash>::Data*
HashMap<Key, Value, Hash>::find( const Key& key ) const
{
    size_t index = this->hash( key );

    for ( const Data& elem : fArr[ index ] )
        if ( elem.fKey == key )
            return &elem;

    return nullptr;
}


template<class Key, class Value, class Hash>
inline typename HashMap<Key, Value, Hash>::Data*
HashMap<Key, Value, Hash>::find( const Key& key )
{
    return const_cast< Data* >( std::as_const( *this ).find( key ) );
}


template<class Key, class Value, class Hash>
inline typename HashMap<Key, Value, Hash>::Data*
HashMap<Key, Value, Hash>::add( const Key& key, const Value& value )
{
    return this->add( Data{ key, value } );
}


template<class Key, class Value, class Hash>
inline typename HashMap<Key, Value, Hash>::Data*
HashMap<Key, Value, Hash>::add( const Data& pair )
{
    size_t index = this->hash( pair.fKey );

    if ( (float) ( this->size() + 1 ) / this->bucket_count() > this->max_load_factor() )
        this->rehash( this->bucket_count() * 2 );

    fArr[ index ].push_front( pair );

    ++fSize;
    return &fArr[ index ].front();
}

#endif // !_FORWARD_LIST_HEADER_INCLUDED_
