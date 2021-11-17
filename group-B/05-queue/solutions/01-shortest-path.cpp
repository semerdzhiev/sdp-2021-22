#include <iostream>
#include <queue>
#include <stack>

enum Cell
{
    FREE = 0,
    TAKEN,
    START,
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

std::ostream& operator<<( std::ostream& out, Cell cell );

struct Coord
{
    int row;
    int col;

    bool operator==( const Coord& other ) { return row == other.row && col == other.col; }
    bool operator!=( const Coord& other ) { return !(*this == other); }
};

constexpr int       MAX_ROWS        = 8;
constexpr int       MAX_COLS        = 10;
constexpr Coord     START_COORD     = { 0, 0 };
constexpr Coord     END_COORD       = { MAX_ROWS - 1, MAX_COLS - 1 };

void printMap( Cell map[ MAX_ROWS ][ MAX_COLS ] );
bool isValidCoord( Cell map[ MAX_ROWS ][ MAX_COLS ], Coord coord );
void fillShortestPath( Cell map[ MAX_ROWS ][ MAX_COLS ] );
void printPath( Cell map[ MAX_ROWS ][ MAX_COLS ] );

//------------------------------------------------------------------------------
int main()
{
    Cell map[ MAX_ROWS ][ MAX_COLS ] =
    {
        { FREE , TAKEN , FREE , FREE  , FREE , FREE  , FREE , TAKEN , FREE , FREE },
        { FREE , TAKEN , FREE , FREE  , FREE , FREE  , FREE , TAKEN , FREE , FREE },
        { FREE , TAKEN , FREE , TAKEN , FREE , TAKEN , FREE , TAKEN , FREE , FREE },
        { FREE , TAKEN , FREE , TAKEN , FREE , TAKEN , FREE , FREE  , FREE , FREE },
        { FREE , TAKEN , FREE , FREE  , FREE , TAKEN , FREE , FREE  , FREE , FREE },
        { FREE , FREE  , FREE , TAKEN , FREE , TAKEN , FREE , FREE  , FREE , FREE },
        { FREE , TAKEN , FREE , TAKEN , FREE , TAKEN , FREE , FREE  , FREE , FREE },
        { FREE , TAKEN , FREE , FREE  , FREE , TAKEN , FREE , FREE  , FREE , FREE },
    };

    std::cout << "Starting map:\n";
    
    printMap( map );

    fillShortestPath( map );

    std::cout << "\nFilled map:\n";

    printMap( map );

    std::cout << "\nPath: ";

    printPath( map );

    std::cout << '\n';

    return 0;
}

//------------------------------------------------------------------------------
bool isValidCoord( Cell map[ MAX_ROWS ][ MAX_COLS ], Coord coord )
{
    if (    coord.row >= 0
        &&  coord.col >= 0
        &&  coord.row < MAX_ROWS
        &&  coord.col < MAX_COLS )
    {
        return map[ coord.row ][ coord.col ] == FREE;
    }

    return false;
}

//------------------------------------------------------------------------------
void fillShortestPath( Cell map[ MAX_ROWS ][ MAX_COLS ] )
{
    std::queue<Coord> wave;
    wave.push( START_COORD );
    map[ START_COORD.row ][ START_COORD.col ] = START;

    while ( !wave.empty() )
    {
        Coord curr = wave.front();
        wave.pop();

        // Stop searching when we've found the end
        if ( curr == END_COORD )
            return;

        Coord downCoord { curr.row + 1, curr.col };
        if ( isValidCoord( map, downCoord ) )
        {
            wave.push( downCoord );
            map[ curr.row + 1 ][ curr.col ] = UP;
        }

        Coord rightCoord { curr.row, curr.col + 1 };
        if ( isValidCoord( map, rightCoord ) )
        {
            wave.push( rightCoord );
            map[ curr.row ][ curr.col + 1 ] = LEFT;
        }

        Coord upCoord { curr.row - 1, curr.col };
        if ( isValidCoord( map, upCoord ) )
        {
            wave.push( upCoord );
            map[ curr.row - 1 ][ curr.col ] = DOWN;
        }

        Coord leftCoord { curr.row, curr.col - 1 };
        if ( isValidCoord( map, leftCoord ) )
        {
            wave.push( leftCoord );
            map[ curr.row ][ curr.col - 1 ] = RIGHT;
        }
    }
}

//------------------------------------------------------------------------------
void printMap( Cell map[ MAX_ROWS ][ MAX_COLS ] )
{
    for ( size_t i = 0; i < MAX_COLS + 2; i++ )
    {
        std::cout << Cell::TAKEN;
    }

    std::cout << '\n';

    for ( size_t i = 0; i < MAX_ROWS; i++ )
    {
        std::cout << Cell::TAKEN;
        for ( size_t j = 0; j < MAX_COLS; j++ )
        {
            std::cout << map[ i ][ j ];
        }
        std::cout << Cell::TAKEN << '\n';
    }

    for ( size_t i = 0; i < MAX_COLS + 2; i++ )
    {
        std::cout << Cell::TAKEN;
    }

    std::cout << '\n';
}

//------------------------------------------------------------------------------
void printPath( Cell map[ MAX_ROWS ][ MAX_COLS ] )
{
    std::stack<Coord> path;

    Coord   curr        = { MAX_ROWS - 1, MAX_COLS - 1 };
    bool    wrongCoord  = false;
    while ( curr != START_COORD && !wrongCoord )
    {
        path.push( curr );

        switch ( map[ curr.row ][ curr.col ] )
        {
            case UP:
                --curr.row;
                break;
            case DOWN:
                ++curr.row;
                break;
            case LEFT:
                --curr.col;
                break;
            case RIGHT:
                ++curr.col;
                break;
            default:
                wrongCoord = true;
                break;
        }
    }

    path.push( START_COORD );

    while ( !path.empty() )
    {
        Coord curr = path.top();
        path.pop();
        std::cout << '(' << curr.row << ", " << curr.col << ") ";
    }
}

//------------------------------------------------------------------------------
std::ostream& operator<<( std::ostream& out, Cell cell )
{
    switch ( cell )
    {
        case FREE:
            out << ' ';
            break;
        case TAKEN:
            out << '#';
            break;
        case START:
            out << 'O';
            break;
        case UP:
            out << '^';
            break;
        case DOWN:
            out << 'v';
            break;
        case LEFT:
            out << '<';
            break;
        case RIGHT:
            out << '>';
            break;
        default:
            out << '?';
            break;
    }

    return out;
}
