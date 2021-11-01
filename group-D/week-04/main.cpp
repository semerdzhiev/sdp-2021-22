#include <iostream>
#include <string>
#define MAX_SIZE 100
using namespace std;

template <class T>
class Queue {
    T arr[MAX_SIZE];
    int begin, end;
    // count elements = end - begin
public:
    Queue() { begin = end = 0; } // + big 4
    void push(T el) {
        if (end < MAX_SIZE) {
            arr[end++] = el;
        } else {
            throw std::out_of_range("array out of range");
        }
    }
    void pop() {
        if (begin == end) {
            // we dont have elements;
            throw std::out_of_range("empty Queue");
        }
        begin++;
    }

    T front() {
        if (begin == end) {
            // we dont have elements;
            throw std::out_of_range("empty Queue");
        }
        return arr[begin];
    }

    T rear() {
        if (begin == end) {
            // we dont have elements;
            throw std::out_of_range("empty Queue");
        }
        return arr[end - 1];
    }

    bool isEmpty() {
        return begin == end;
    }

};

int main() {
  /*  Queue<int> q;
    q.push(5);
    q.push(10);
    q.push(12);
    q.push(34);
    q.push(200);
    q.pop();
    q.pop();
    cout<<q.front()<<endl;
    cout<<q.rear()<<endl;
    */
  int n;
  cin>>n;
  Queue<string> q;
    q.push("0");
    q.push("1");
    // 2^(n+1) - 1
    while(q.isEmpty() == false) {
        string el = q.front();
        q.pop();
        if (el.length() == n) {
            cout<<el<<endl;
            continue;
        } else {
            cout<<"Not ready value -> "<<el<<endl;
        }
        q.push(el+"0");
        q.push(el+"1");

    }
    return 0;
}
/*
0
1
---
01
10
...
----
000
001*/