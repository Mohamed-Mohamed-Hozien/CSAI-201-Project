#include <iostream>
#include "companynew.h"
using namespace std;

int main() {
    Company company;
    company.readInputFile("input.txt");
    company.events.displayQueue();
    // Dequeue and print all items in the events queue
    while (!company.events.isEmpty()) {
        Event* event;
        company.events.dequeue(event);
        cout << event->getTime() << endl;
    }

    return 0;
}