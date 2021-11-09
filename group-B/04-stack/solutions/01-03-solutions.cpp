#include <iostream>
#include <string>
#include <stack>

bool isOpenBracket( char ch )
{
    return ch == '(' || ch == '[' || ch == '{';
}

bool isCloseBracket( char ch )
{
    return ch == ')' || ch == ']' || ch == '}';
}

char getOpeningBracket( char closeBracket )
{
    switch ( closeBracket )
    {
        case ')':
            return '(';

        case ']':
            return '[';

        case '}':
            return '{';

        default:
            return 0;
    }

    return 0;
}

//------------------------------------------------------------------------------
bool isCorrectlyBracketed( const std::string& str )
{
    std::stack<char> stack;

    for ( char ch : str )
    {
        if ( isOpenBracket( ch ) )
        {
            stack.push( ch );
        }
        else if ( isCloseBracket( ch ) )
        {
            if ( stack.empty() )
                return false;

            if ( getOpeningBracket( ch ) == stack.top() )
                stack.pop();
            else
                return false;
        }
    }

    return stack.empty();
}

//------------------------------------------------------------------------------
double calcPostfix( const std::string& str )
{
    std::stack<double>  stack;

    for ( char ch : str )
    {
        if ( ch >= '0' && ch <= '9' )
        {
            stack.push( ch - '0' );
        }
        else
        {
            if ( stack.size() < 2 )
                throw std::invalid_argument( "Invalid expression!" );

            double right = stack.top();
            stack.pop();
            double& left = stack.top();

            switch ( ch )
            {

                case '+':
                    left += right;
                    break;
                case '-':
                    left -= right;
                    break;
                case '*':
                    left *= right;
                    break;
                case '/':
                    left /= right;
                    break;
                default:
                    throw std::invalid_argument( "Unsupported operation" );
            }
        }
    }

    if ( stack.size() != 1 )
        throw std::invalid_argument( "Invalid expression!" );

    return stack.top();
}

//------------------------------------------------------------------------------
int main()
{
    // Task 01
    //std::stack<char, std::string>   stack;
    //std::string str = "fmi";

    //for ( char ch : str )
    //    stack.push( ch );

    //while ( !stack.empty() )
    //{
    //    std::cout << stack.top();
    //    stack.pop();
    //}

    std::stack<char>   stack;

    std::string str;
    std::cin >> str;

    //std::cout << isCorrectlyBracketed( str );
    std::cout << calcPostfix( str );
}
