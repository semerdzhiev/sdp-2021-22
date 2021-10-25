#include <iostream>
#define MAX_SIZE 100
using namespace std;

/*class Collection {
    void add();
    void remove();
    // iterator
};*/

template <class T> class Stack {
    T arr[MAX_SIZE];
    int top; // only positive number
public:
    Stack() {top = 0;}
    bool push(T x) { arr[top++] = x; } // validation for the size
    void pop() { top--; }; // validation of the size
    T& peek() {return arr[top-1];}; // validation of the size, adding this object to be const
    bool isEmpty() {return top== 0;}
};

// 1) static array, push() - O(1), pop() - O(1), peek() - 0(1), isEmpty() - O(1)
// 2) dynamic array, push() - O(1) (amortizirana slojnost), pop() - O(1), peek() - 0(1), isEmpty() - O(1)
// 3) Linked list
// 4) Vector from STD
bool solve(const char* str) {
    Stack<char> s;
    int index = 0;
    while(str[index] != '\0') {
        char el = str[index];
        if (el == ')') {
            if (s.isEmpty()) {
                return 0;
            } else {
                s.pop();
            }
        }
        else // el == '('
          s.push('(');
        index++;
    }
    return s.isEmpty();
}
int main() {
    Stack<char> s;
    char str[10] = {"()()())\0"};
    cout<<solve(str)<<endl;
    return 0;

//    cout<<s.isEmpty()<<endl;
//    s.push(5);
//    s.push(7);
//    cout<<s.peek()<<endl;
//    cout<<s.isEmpty()<<endl;
    return 0;
}
