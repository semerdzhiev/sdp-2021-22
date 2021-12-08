#include<iostream>
#include "queue.hpp"

const int WAITING_TIME = 2;

struct Customer {
    int timeOffset, checkoutTerminalIndex;

    Customer() {}
    Customer(int timeOffset, int checkoutTerminalIndex) : timeOffset(timeOffset), checkoutTerminalIndex(checkoutTerminalIndex) {}
};

struct CheckoutTerminal {
    Queue<Customer> customerQueue;
    int frontCustomerWaitingTime = 0;
};

void supermarket() {
    Queue<Customer> customerQueue;
    int customersCount, checkoutTerminalsCount;
    cin >> customersCount >> checkoutTerminalsCount;
    int timeOffset, checkoutTerminalIndex;
    for (int customerIndex = 0; customerIndex < customersCount; ++customerIndex) {
        cin >> timeOffset >> checkoutTerminalIndex;
        customerQueue.enqueue(Customer(timeOffset, checkoutTerminalIndex));
    }
    DynamicArray<CheckoutTerminal> checkoutTerminals(checkoutTerminalsCount);
    while (!customerQueue.empty()) {
        Customer currentCustomer = customerQueue.front();
        for (int checkoutTerminalIndex = 0; checkoutTerminalIndex < checkoutTerminalsCount; ++checkoutTerminalIndex) {
            int passingPeople = currentCustomer.timeOffset / WAITING_TIME;
            for (int _ = 0; _ < passingPeople; ++_) {
                checkoutTerminals[checkoutTerminalIndex].customerQueue.dequeue();
            }
            checkoutTerminals[checkoutTerminalIndex].frontCustomerWaitingTime -= currentCustomer.timeOffset % WAITING_TIME;
            if (checkoutTerminals[checkoutTerminalIndex].frontCustomerWaitingTime < 0) {
                checkoutTerminals[checkoutTerminalIndex].customerQueue.dequeue();
                checkoutTerminals[checkoutTerminalIndex].frontCustomerWaitingTime += WAITING_TIME;
            }
        }
        checkoutTerminals[currentCustomer.checkoutTerminalIndex].customerQueue.enqueue(currentCustomer);
    }
}