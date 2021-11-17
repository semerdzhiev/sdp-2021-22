#include <iostream>
#include <vector>
using namespace std;
// Data List = EMPTY | Data List (KEY, List)
template <class T>
struct Node {
    T value;
    Node<T>* next; // why not only Node<T>? we know the size.
    Node () {
        next = NULL;
    }
    Node (T key) {
        value = key;
        next = NULL;
    }
    Node(T key, Node<T>* next) {
        this->value = key;
        this->next = next;
    }
};

template <class T>
class LinkedList {
    Node<T>* begin;
public:
    LinkedList() { // + big 4
        begin = NULL;
    }

    ~LinkedList() {
        Node<T>* temp;
        while(begin != NULL) {
            temp = begin;
            begin = begin->next;
            delete temp;
        }
        // begin = NULL;
    }

    void addAtBeginning(T key) {
        begin = new Node<T>(key, begin); // + validation for new
    }

    bool contains(T key) {
        Node<T>* temp = begin;
        while(temp != NULL) {
            if (temp->value == key) return true;
            temp = temp->next;
        }
        return false;
    }
    bool remove(T key) {
        Node<T>* temp = begin;
        Node<T>* prev;

        if (temp -> value == key) {
            begin = begin->next;
            delete temp;
            return true;
        }

        while(temp != NULL) {
            cout<< temp-> value <<" ..."<<endl;
            if (temp->value == key)  {
                prev->next = temp->next;
                delete temp;
                return true;
            }
            prev = temp;
            temp = temp->next;
        }
        return false;

    }
};

int main() {
    LinkedList<int> LL;
    LL.addAtBeginning(1);
    LL.addAtBeginning(5);
    LL.addAtBeginning(14);
    cout<<LL.contains(5)<<" ";
    cout<<LL.contains(19)<<endl;
    cout<<LL.remove(1)<<endl;
    cout<<LL.remove(14)<<endl;

    cout<<LL.remove(44)<<endl;
    return 0;
}
