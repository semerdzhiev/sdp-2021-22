#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Numbers {
private:
    int num[100];
    int currentSize;
public:
    Numbers() : currentSize(0) {};
    class Iterator {
    public:
        int* current;
        Iterator() : current(NULL) {};
        Iterator(int* _current): current(_current) {};
        Iterator operator++(int) {Iterator temp = *this; ++(*this); return temp;}
        Iterator& operator++() {current++; return *this;}
        int& operator*() const { return *current; }
        friend bool operator == (const Iterator& a, const Iterator& b) {
            return a.current == b.current;
        }
        friend bool operator != (const Iterator& a, const Iterator& b) {
            return a.current != b.current;
        }

    };
    void add(int el) {num[currentSize++] = el;}
    void removeTop() {currentSize--;}
    Iterator begin() {return Iterator(&num[0]);}
    Iterator end() {return Iterator(&num[currentSize]);} // why not currentSize-1
};
int main() {
//    queue<int> q;
//    q.push(1);
//    q.push(2);
//    for (int item : q) { can we make this one?
//        cout<<item<<endl;
//    }
    Numbers s;
    s.add(3);
    s.add(5);
    s.add(4);
    s.add(3);
    for (int item: s) {
        cout<<item<<" ";
    }
    cout<<endl;
    for (Numbers::Iterator it = s.begin(); it != s.end(); it++) {
        cout<<*it<<" ";
    }
    cout<<endl;

    vector<int> v;
    v.push_back(1);
    v.push_back(4);
    v.push_back(19);
    for (int i = 0 ;i< v.size();i++) {
        cout<<v[i]<<" "; // operator [], size/length
    }
    cout<<endl;
    for (int item : v) {
        cout<<item<<" ";
    }
    cout<<endl;

    for (vector<int>::iterator it = v.begin(); it!=v.end(); it++) {
        cout<<*it<<" ";
    }
    // iterator, operator ++?, operator *, operator !=, operator=, operator--?
    // vector method begin, method end. Both methods return iterator

    cout<<endl;

    return 0;
}
