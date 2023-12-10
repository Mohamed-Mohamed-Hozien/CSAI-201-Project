#include <iostream>
#include "Station.h"

int main() {
    // Create a station
    Station station;

    // Create passengers
    Passenger passenger1(1, 101, 10, 1, 5, 15, 20);
    Passenger passenger2(4, 102, 8, 1, 5, 12, 18);
    Passenger passenger3(2, 103, 5, 1, 5, 10, 25);

    // Add passengers to the station
    station.addPassenger2station(passenger1);
    station.addPassenger2station(passenger2);
    station.addPassenger2station(passenger3);

    // Display passenger queues for testing
    std::cout << "Passenger Queue 1: ";
    station.getMPassengerQueue1().displayQueue();

    std::cout << "Passenger Queue 2: ";
    station.getMPassengerQueue2().displayQueue();

    // Create buses
    Bus bus1(1, 20, 0, 1, 30, 40);
    Bus bus2(2, 25, 0, 2, 35, 45);

    // Add buses to the station
    station.addBus2Station(bus1);
    station.addBus2Station(bus2);
    // Display bus queues for testing
    std::cout << "Bus Queue 1: ";
    station.getMBusQueue1().displayQueue();

    std::cout << "Bus Queue 2: ";
    station.getMBusQueue2().displayQueue();
    // Test passenger promotion
    int promotedPassengers = station.promotePassengers(15, 10);
    std::cout << "Promoted Passengers: " << promotedPassengers << std::endl;

    // Display updated passenger queues after promotion for testing
    std::cout << "Passenger Queue 1: ";
    station.getMPassengerQueue1().displayQueue();

    std::cout << "Passenger Queue 2: ";
    station.getMPassengerQueue2().displayQueue();

    // Dequeue a passenger from each queue for testing
    Passenger* dequeuedPassenger1 = station.dequeueMPassenger1();
    Passenger* dequeuedPassenger2 = station.dequeueMPassenger1();
    Passenger* dequeuedPassenger3 = station.dequeueMPassenger1();

    // Display dequeued passengers for testing
   std::cout << "Dequeued Passenger 1: ";
if (dequeuedPassenger1) {
    std::cout << "ID " << dequeuedPassenger1->getID();
} else {
    std::cout << "None";
}
std::cout << std::endl;

std::cout << "Dequeued Passenger 2: ";
if (dequeuedPassenger2) {
    std::cout << "ID " << dequeuedPassenger2->getID();
} else {
    std::cout << "None";
}
std::cout << std::endl;

std::cout << "Dequeued Passenger 3: ";
if (dequeuedPassenger3) {
    std::cout << "ID " << dequeuedPassenger3->getID();
} else {
    std::cout << "None";
}
std::cout << std::endl;

return 0;
}

