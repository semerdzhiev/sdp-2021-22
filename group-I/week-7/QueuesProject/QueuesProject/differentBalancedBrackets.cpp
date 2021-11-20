#include <iostream>
#include <string>
#include "stack.hpp"
using namespace std;

bool differentBalancedBrackets(string str) {
	int strLen = str.length();
	Stack<char> s;
	for (int i = 0; i < strLen; ++i) {
		char c = str[i];
		char t = s.top();
		switch (str[i]) {
		case '(':
		case '[':
		case '{':
			s.push(str[i]);
			break;
		case ')':
			if (s.top() != '(')
				return false;
			s.pop();
			break;
		case ']':
			if (s.top() != '[')
				return false;
			s.pop();
			break;
		case '}':
			if (s.top() != '{')
				return false;
			s.pop();
			break;
		default:
			break;
		}
	}
	return s.empty();
}