#include <stack>
#include <iostream>
#include <string>

void print(std::stack<int> s)
{
    while(!s.empty())
    {
        std::cout << s.top() << ' ';
        s.pop(); 
    }

    std::cout << std::endl;
}

void reverse(std::stack<int>& s)
{
    std::stack<int> temp;

    while(!s.empty())
    {
        temp.push(s.top());
        s.pop();
    }

    s.swap(temp);
}

bool is_open_bracket(char c)
{
    return c == '{' || c == '(' || c == '[';
}

bool match(char l, char r)
{
    return (l == '{' && r == '}') ||
           (l == '(' && r == ')') ||
           (l == '[' && r ==']');
}

bool balanced_brackets(const std::string& expr)
{
    std::stack<char> brackets;

    for(size_t i = 0; i < expr.size(); ++i)
    {
        if(is_open_bracket(expr[i]))
            brackets.push(expr[i]);
        else
        {
            if(brackets.empty())
                return false;

            if(match(expr[i], brackets.top()))
                brackets.pop();
            else
                return false;
        }
    }

    if(!brackets.empty())
        return false;

    return true;
}

//1 - push 5
//2 - pop
//3 - print max elem

//        elements       max_elements
//1 20 -> 20          -> 20
//1 30 -> 20, 30      -> 20, 30
//2    -> 20          -> 20
//1 50 -> 20, 50      -> 20, 50
//1 60 -> 20, 50, 60  -> 20, 50, 60
//3    -> 60          
//2    -> 20, 50      -> 20, 50
//3    -> 50
//1 -1 -> 20, 50, -1  -> 20, 50

int main()
{

    return 0;
}