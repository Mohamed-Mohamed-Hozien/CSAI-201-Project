
#ifndef _Station
#define _Station

#include "PriorityQueue.h"
#include "Passenger.h" 
#include "Bus.h"
#include "Node.h"
#include "Queue.h"
#include "LinkedList.h"

class Station {
    int stationNumber;
    //direction 1 moving from s smaller -> sbigger 
    // direction 2 moving from s bigger -> ssmaller
public:

    LinkedList<Passenger*> NPassengerListForwards;
    LinkedList<Passenger*> NPassengerListBackwards;

    PriorityQueue<Passenger*> SPassengerQueueForwards;
    PriorityQueue<Passenger*> SPassengerQueueBackwards;
    
    Queue<Passenger*> wPassengerQueueForwards;
    Queue<Passenger*> wPassengerQueueBackwards;

    
    Queue<Bus> BusQueueForwards;
    Queue<Bus> BusQueueBackwards;

    Station(int sNumber) {
        stationNumber = sNumber;
    }

    void addPassenger2station(Passenger *p) {
        // Normal = 1 , pregnant = 2, POD = 3, aged = 4 , WP = 5
        if (p->getType() == 5) {
            if (p->getStartStation() < p->getEndStation()) {
                wPassengerQueueForwards.enqueue(p);
            } 
            else if (p->getStartStation() > p->getEndStation()) {
                wPassengerQueueBackwards.enqueue(p);
            }
        }
        else if (p->getType() == 1){
            if (p->getStartStation() < p->getEndStation()){
                NPassengerListForwards.InsertEnd(p);
            }
            else if (p->getStartStation() > p->getEndStation()) {
                NPassengerListBackwards.InsertEnd(p);
            }
        }

        else if (p->getType() >= 2 && p->getType() <= 4){
            if (p->getStartStation() < p->getEndStation()){
                SPassengerQueueForwards.enqueue(p, p->getType());
            }
            else if (p->getStartStation() > p->getEndStation()) {
                SPassengerQueueBackwards.enqueue(p, p->getType());
            }
        }
    }

    void addBus2Station(Bus& bus){
        if (bus.getDirection() == 1){
            BusQueueForwards.enqueue(bus);
        }
        else if (bus.getDirection() == 2){
            BusQueueBackwards.enqueue(bus);
        }
    }

    int promotePassengers(int timeNow, int maxWaitingTime) {
        int promotedPassengersCount = 0;
        for (auto passenger : NPassengerListForwards) {
            if (timeNow - passenger->getArrivalTime() > maxWaitingTime) {
                SPassengerQueueForwards.enqueue(passenger, 4);
                NPassengerListForwards.RemovewithItem(passenger);
                promotedPassengersCount++;
            }
        }

        for (auto passenger : NPassengerListBackwards) {
            if (timeNow - passenger->getArrivalTime() > maxWaitingTime) {
                SPassengerQueueBackwards.enqueue(passenger, 4);
                NPassengerListBackwards.RemovewithItem(passenger);
                promotedPassengersCount++;
            }
        }

    
        return promotedPassengersCount;
    }

    void removePassenger(int id){
        for (auto passenger : NPassengerListForwards) {
            if (passenger->getID() == id) {
                NPassengerListForwards.RemovewithItem(passenger);
                return;
            }
        }

        for (auto passenger : NPassengerListBackwards){
            if (passenger->getID() == id) {
                NPassengerListBackwards.RemovewithItem(passenger);
                return;
            }
        }
        
    }

  // this function adds the passengers whose end stations is this station to the removed passengers list
  // it then takes the input bus and board the passengers from the station queues it will check its type in case of MB it'll onboard
  // the SP first then the NP if it it still not full.
  // in case of WP  it will just add till the bus is either full or the queue is empty
    void boardingBus(Bus bus, LinkedList<Passenger*>& removedPassengers, int time){
        // the passenger removed 
        bus.removePassenger(stationNumber, removedPassengers, time);

        if (bus.getBusType() == 1){
            if (bus.getDirection() == 1){
                while (!SPassengerQueueForwards.isEmpty() && bus.isFull()){
                    Passenger* passenger = SPassengerQueueForwards.dequeueAndReturn();
                    bus.insertPassenger(passenger, time);
                }
                while (!NPassengerListForwards.IsEmpty() && bus.isFull()){
                    Passenger* passenger;
                    NPassengerListForwards.RemoveBegin(passenger);
                    bus.insertPassenger(passenger, time);
                }

            }
            else if (bus.getDirection() == 2){
                while (!SPassengerQueueBackwards.isEmpty() && !bus.isFull()){
                    Passenger* passenger = SPassengerQueueBackwards.dequeueAndReturn();
                    bus.insertPassenger(passenger, time);
                }
                while (!NPassengerListBackwards.IsEmpty() && bus.isFull()){
                    Passenger* passenger;
                    NPassengerListBackwards.RemoveBegin(passenger);
                    bus.insertPassenger(passenger, time);
                }
            }
        }
        else if (bus.getBusType() == 2){
            if (bus.getDirection() == 1){
                while (!wPassengerQueueForwards.isEmpty() && bus.isFull()){
                    Passenger* passenger = wPassengerQueueForwards.dequeueAndReturn();
                    bus.insertPassenger(passenger, time);
                }
            }
            else if (bus.getDirection() == 2){
                while (!wPassengerQueueBackwards.isEmpty() && bus.isFull()){
                    Passenger* passenger = wPassengerQueueBackwards.dequeueAndReturn();
                    bus.insertPassenger(passenger, time);
                }
            }
        }
    }

    //uses the boarding bus function to onboard on the bus at the front of the Forward direction Queue, it adds removed passengers to the removed passengers list
    Bus boardTheBusForward(LinkedList<Passenger*>& removedPassengers, int time){
        Bus bus;
        if (!BusQueueForwards.isEmpty()){
            BusQueueForwards.getFront(bus);
            boardingBus(bus, removedPassengers, time);
            BusQueueForwards.dequeue(bus);
        }
        return bus;
    }
    //uses the boarding bus function to onboard on the bus at the front of the Backwards direction Queue, it adds finished passengers to the removed passengers list
    Bus boardTheBusBackward(LinkedList<Passenger*>& removedPassengers, int time){
        Bus bus;
        if (!BusQueueBackwards.isEmpty()){
            BusQueueBackwards.getFront(bus);
            boardingBus(bus, removedPassengers, time);
            BusQueueBackwards.dequeue(bus);
        }
        return bus;
    }

};
#endif

// Station (object name will be the station number):
// --- linked priority queue 1 -> passengers at the station direction 1
// --- linked priority queue 2 -> passengers at the station direction 2
// --- linked queue 1 -> Mbuses at the station direction 1
// --- linked queue 2 -> Mbuses at the station direction 2
// --- linked queue 3 -> Wbuses at the station direction 1
// --- linked queue 4 -> Wbuses at the station direction 2