#include <iostream>
#include "Station.h"

int main() {
    // Create a Station object
    Station station;

    // Create some passengers and add them to the station
    Passenger passenger1(4, 1, 0, 1, 5);  // Aged passenger at station 1
    Passenger passenger2(4, 2, 0, 5, 1);  // Aged passenger at station 5
    Passenger passenger3(1, 3 ,4 , 2, 3);  // POD passenger at station 2
    Passenger passenger4(1, 4, 0, 3, 1);  // Normal passenger at station 3
    station.addPassenger2station(&passenger1);
    station.addPassenger2station(&passenger2);
    station.addPassenger2station(&passenger3);
    station.addPassenger2station(&passenger4);

    // Simulate some time passing
    int timestep = 6;
    int maxWaitingTime = 5;

    std::cout << "before promotion";
    std::cout << "SPassengerQueue1: ";
    station.getSPassengerQueue1().displayQueue();
    std::cout << "SPassengerQueue2: ";
    station.getSPassengerQueue2().displayQueue();
    
    // Call the promotePassengers function and get the count of promoted passengers
    int promotedPassengersCount = station.promotePassengers(timestep, maxWaitingTime);

    // Display the result
    std::cout << "Number of passengers promoted: " << promotedPassengersCount << std::endl;

    // Display the updated state of the station queues
    std::cout << "SPassengerQueue1: ";
    station.getSPassengerQueue1().displayQueue();
    std::cout << "SPassengerQueue2: ";
    station.getSPassengerQueue2().displayQueue();
    // std::cout << "NPassengerList1: ";
    // station.getNPassengerList1().displayList();
    // std::cout << "NPassengerList2: ";
    // station.getNPassengerList2().displayList();

    return 0;
}
