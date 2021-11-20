#include <iostream>
#include <string>
using namespace std;

bool balancedBrackets(string str) {
	int strLen = str.length();
	int currentlyOpenedBrackets = 0;
	for (int i = 0; i < strLen; ++i) {
		switch (str[i]) {
		case '(':
			++currentlyOpenedBrackets;
			break;
		case ')':
			if (currentlyOpenedBrackets < 1)
				return false;
			--currentlyOpenedBrackets;
			break;
		default:
			break;
		}
	}
	return currentlyOpenedBrackets == 0;
}