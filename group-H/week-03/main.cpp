#include <iostream>
#define MAX_SIZE 100
using namespace std;

template <typename T>
class Stack {
    T arr[MAX_SIZE];
    unsigned int top;
public:
    void push(T el) { arr[top++] = el; } // Error handling index < MAX_SIZE
    T pop() { return arr[--top]; } // Error handling index > 0
    const T& peek() const { return arr[top-1]; } // Error handling index > 0
    bool isEmpty() { return top == 0;}
    Stack() { top = 0;}
    // Big 4

};

bool solve(char* a){
    Stack<char> stack;
    int ind =0;
    while (a[ind] != '\0') {
        if (a[ind] == '(') stack.push('(');
        else if (stack.isEmpty()) { return false; } // we have closing bracket, but no open one
        else stack.pop();
        ind++;
    }
    //return true; ? '()('
    return stack.isEmpty(); // to make sure that at the end we dont have ( into the stack
}

int main() {

    char a[10] = {"()(\0"};
    cout<<solve(a)<<endl;
    Stack<int> stack;

    return 0;
}
