#include <iostream>

class RoundTable
{
    // Objects lifetime
public:
                    RoundTable( size_t initialSize = 0 );
                    ~RoundTable();

                    RoundTable( const RoundTable& )     = delete;
    RoundTable&     operator=( const RoundTable& )      = delete;

    // Public methods
public:
    size_t          CalculateWinningKnight();

    // Node structure
private:
    struct Knight
    {
        size_t      fNumber;
        Knight*     fpNext;
    };

    // Private methods
private:
    Knight*         AddKnightAfter( Knight* pos );
    Knight*         KillKnightAfter( Knight* pos );

    // Fields
private:
    Knight*     fpFirst;
    Knight*     fpLast;
    size_t      fLastKnightNumber;
};


//------------------------------------------------------------------------------
int main()
{
    size_t  num;
    std::cin >> num;

    RoundTable  table( num );

    std::cout << table.CalculateWinningKnight() << '\n';

    return 0;
}


//------------------------------------------------------------------------------
RoundTable::RoundTable( size_t initialSize )
    : fLastKnightNumber( 1 )
    , fpFirst( nullptr )
    , fpLast( nullptr )
{
    Knight*     pCurr   = fpFirst;
    for ( size_t i = 0; i < initialSize; i++ )
        pCurr   = this->AddKnightAfter( pCurr );
}


RoundTable::~RoundTable()
{
    while ( fpFirst )
        this->KillKnightAfter( fpFirst );
}


size_t RoundTable::CalculateWinningKnight()
{
    if ( fpFirst == nullptr )
        return 0;

    Knight*     pCurr   = fpFirst;
    while ( fpFirst != fpLast )
        pCurr   = this->KillKnightAfter( pCurr );

    return pCurr->fNumber;
}


RoundTable::Knight* RoundTable::AddKnightAfter( Knight* pPos )
{
    Knight*     pNewKnight  = nullptr;

    // Empty table
    if ( fpFirst == nullptr && pPos == nullptr )
    {
        pNewKnight          = new Knight { fLastKnightNumber++, nullptr };
        pNewKnight->fpNext  = pNewKnight;
        fpFirst             = pNewKnight;
        fpLast              = pNewKnight;
    }
    else
    {
        pNewKnight          = new Knight { fLastKnightNumber++, pPos->fpNext };
        pPos->fpNext        = pNewKnight;

        if ( pPos == fpLast )
            fpLast  = pNewKnight;
    }

    return pNewKnight;
}


RoundTable::Knight* RoundTable::KillKnightAfter( Knight* pPos )
{
    // Empty table
    if ( ! pPos )
        return nullptr;
    
    // One knight remaining
    if ( pPos->fpNext == pPos && pPos == fpFirst )
    {
        delete pPos;
        fpFirst = nullptr;
        fpLast  = nullptr;

        return nullptr;
    }

    if ( pPos->fpNext == fpLast )
        fpLast  = pPos;

    Knight*     pNextNext   = pPos->fpNext->fpNext;
    delete pPos->fpNext;
    pPos->fpNext            = pNextNext;

    if ( pPos == fpLast )
        fpFirst     = fpLast->fpNext;

    return pNextNext;
}
