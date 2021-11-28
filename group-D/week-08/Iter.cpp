#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Numbers {
private:
    int number[100];
    int currentEl;
public:
    Numbers() : currentEl(0) {};
    void add(int i) {number[currentEl++] = i;}
    void pop() {currentEl--;}
    struct Iterator { // can this be also class?
        Iterator(): current(NULL){};
        Iterator(int* _current): current(_current){};
        // bool operator=
        friend bool operator==(const Iterator& a, const Iterator& b) {
            return a.current == b.current;
        }
        friend bool operator!=(const Iterator& a, const Iterator& b) {
            return a.current != b.current;
        }
        int& operator*() const { return *current; }
        Iterator& operator++() { current++; return *this;}
        Iterator operator++(int) { Iterator temp = *this; ++(*this); return temp; }

    private:
        int* current;
    };
    Iterator begin() {return Iterator(&number[0]);}
    Iterator end() {return Iterator(&number[currentEl]);}
};

int main() {
    Numbers num;
    num.add(1);
    num.add(2);
    num.add(6);
    num.add(9);
    num.pop();
    for (int item : num) {
        cout<<item<<endl;
    }
//    deque
//    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
//        cout<<*it<<endl;
//    }
//    cout<<num[0];
//    vector<int> v;
//    v.push_back(1);
//    v.push_back(3);
//    v.push_back(2);
//    stack<int> s;
//    s.push(1);
//    for (int i =0;i<v.size();i++) {
//        cout<<v[i]<<endl;
//    }
// for ? operator [], size
// Tree? operator [] (random element)
// Linked List operator [] - O(n)
// Linked List travers will be with O(n^2) in case we use operator []

//    for (int elem : v) {
//        cout<<elem<<endl;
//    }
//    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
//        cout<<*it<<endl;
//    }
// begin, end - data structure
// operator *, ++, -- optional, !=, == , = ?


//    for (int elem : s) { // no defined begin here
//        cout<<elem<<endl;
//    }

    return 0;
}
