#include <iostream>
#include <stack>

template <class T>
void sortStack( std::stack<T>& stack )
{
	std::stack<T> helper;
	while ( !stack.empty() )
	{
		T temp = stack.top();
		stack.pop();
		while ( !helper.empty() && helper.top() < temp )
		{
			stack.push( helper.top() );
			helper.pop();
		}
		helper.push( temp );
	}

	std::swap( stack, helper );
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
