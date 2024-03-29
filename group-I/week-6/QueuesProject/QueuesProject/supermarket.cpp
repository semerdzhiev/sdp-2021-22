#include<iostream>
#include <string>
#include "queue.hpp"

using namespace std;

const int WAITING_TIME = 2;

struct Customer {
    string name;
    int timeOffset, checkoutTerminalIndex;

    Customer() {}
    Customer(string name, int timeOffset, int checkoutTerminalIndex) : name(name), timeOffset(timeOffset), checkoutTerminalIndex(checkoutTerminalIndex) {}
};

struct CheckoutTerminal {
    Queue<Customer> customerQueue;
    int frontCustomerWaitingTime = 0;
};

void supermarket() {
    Queue<Customer> customerQueue;
    int customersCount, checkoutTerminalsCount;
    cin >> customersCount >> checkoutTerminalsCount;
    string name;
    int timeOffset, checkoutTerminalIndex;
    for (int customerIndex = 0; customerIndex < customersCount; ++customerIndex) {
        cin >> name >> timeOffset >> checkoutTerminalIndex;
        customerQueue.enqueue(Customer(name, timeOffset, checkoutTerminalIndex));
    }
    DynamicArray<CheckoutTerminal> checkoutTerminals(checkoutTerminalsCount);
    while (!customerQueue.empty()) {
        Customer currentCustomer = customerQueue.front();
        for (int checkoutTerminalIndex = 0; checkoutTerminalIndex < checkoutTerminalsCount; ++checkoutTerminalIndex) {
            int passingPeople = currentCustomer.timeOffset / WAITING_TIME;
            for (int _ = 0; _ < passingPeople; ++_) {
                checkoutTerminals[checkoutTerminalIndex].customerQueue.dequeue();
                cout << checkoutTerminals[checkoutTerminalIndex].customerQueue.front().name << endl;
            }
            checkoutTerminals[checkoutTerminalIndex].frontCustomerWaitingTime -= currentCustomer.timeOffset % WAITING_TIME;
            if (checkoutTerminals[checkoutTerminalIndex].frontCustomerWaitingTime < 0) {
                cout << checkoutTerminals[checkoutTerminalIndex].customerQueue.front().name<< endl;
                checkoutTerminals[checkoutTerminalIndex].customerQueue.dequeue();
                checkoutTerminals[checkoutTerminalIndex].frontCustomerWaitingTime += WAITING_TIME;
            }
        }
        checkoutTerminals[currentCustomer.checkoutTerminalIndex].customerQueue.enqueue(currentCustomer);
    }
    bool unemptyQueue = true;
    while (unemptyQueue) {
        unemptyQueue = false;
        for (int checkoutTerminalIndex = 0; checkoutTerminalIndex < checkoutTerminalsCount; ++checkoutTerminalIndex) {
            if (!checkoutTerminals[checkoutTerminalIndex].customerQueue.empty()) {
                cout << checkoutTerminals[checkoutTerminalIndex].customerQueue.front().name << endl;
                checkoutTerminals[checkoutTerminalIndex].customerQueue.dequeue();
                unemptyQueue = true;
            }
        }
    }
}