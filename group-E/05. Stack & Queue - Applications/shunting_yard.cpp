#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <unordered_map>

int comparace_precedence(char left, char right)
{
    std::unordered_map<char, int> precedences;
    precedences['^'] = 4;
    precedences['*'] = 3;
    precedences['/'] = 3;
    precedences['+'] = 2;
    precedences['-'] = 2;
    precedences['('] = 1;
    if (precedences[left] > precedences[right])
    {
        return 1;
    }
    else if (precedences[left] == precedences[right])
    {
        return 0;
    }
    return -1;
}

bool is_left_associative(char op)
{
    return op == '+' || op == '-' || op == '*' || op == '/';
}

std::string to_reverse_polish_notation(const std::string &expr)
{
    std::stack<char> operators;
    std::string output;
    for (char token : expr)
    {
        if (isdigit(token))
        {
            output.push_back(token);
        }
        else if (token == '(')
        {
            operators.push(token);
        }
        else if (token == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                char op = operators.top();
                operators.pop();
                output.push_back(op);
            }
            operators.pop();
        }
        else
        {
            if (is_left_associative(token))
            {
                while (
                    !operators.empty() &&
                    operators.top() != '(' &&
                    comparace_precedence(token, operators.top()) <= 0)
                {
                    output.push_back(operators.top());
                    operators.pop();
                }
            }
            else
            {
                while (!operators.empty() &&
                       operators.top() != '(' &&
                       comparace_precedence(token, operators.top()) == -1)
                {
                    output.push_back(operators.top());
                    operators.pop();
                }
            }
            operators.push(token);
        }
    }
    while (!operators.empty())
    {
        output.push_back(operators.top());
        operators.pop();
    }
    return output;
}

int calculate(int left_value, int right_value, char op)
{
    switch (op)
    {
    case '-':
        return left_value - right_value;
    case '+':
        return left_value + right_value;
    case '/':
        return left_value / right_value;
    case '*':
        return left_value * right_value;
    case '^':
        return pow(left_value, right_value);
    default:
        throw std::runtime_error("Invalid operation");
    }
}

int evaluate_rpn(const std::string &rpn)
{
    std::stack<int> values;
    for (char token : rpn)
    {
        if (isdigit(token))
        {
            values.push(token - '0');
        }
        else
        {
            int right_value = values.top();
            values.pop();
            int left_value = values.top();
            values.pop();
            int result = calculate(left_value, right_value, token);
            values.push(result);
        }
    }
    return values.top();
}

int main()
{
    std::string expr;
    std::cin >> expr;
    auto rpn = to_reverse_polish_notation(expr);
    std::cout << "Reverse polish notation: " << rpn << std::endl;
    std::cout << "Value: " << evaluate_rpn(rpn) << std::endl;
    return 0;
}