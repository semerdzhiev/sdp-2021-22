#include <iostream>
#include <stack>

template <class T>
void sortedInsert( std::stack<T>& stack, const T& elem )
{
	if ( stack.empty() || elem < stack.top() )
	{
		stack.push( elem );
	}
	else
	{
		T temp = stack.top();
		stack.pop();
		sortedInsert( stack, elem );
		stack.push( temp );
	}
}

template <class T>
void sortStack( std::stack<T>& stack )
{
	if ( stack.empty() )
		return;

	T temp = stack.top();
	stack.pop();
	sortStack( stack );
	sortedInsert( stack, temp );
}

int main()
{
	std::stack<int> stack;
	for ( size_t i = 0; i < 10; i++ )
	{
		stack.push( rand() % 100 );
		std::cout << stack.top() << ' ';
	}
	std::cout << '\n';

	sortStack( stack );

	while ( !stack.empty() )
	{
		std::cout << stack.top() << ' ';
		stack.pop();
	}

	return 0;
}
