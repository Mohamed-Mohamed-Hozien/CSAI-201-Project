
#ifndef _Station
#define _Station

#include "PriorityQueue.h"
#include "Passenger.h" 
#include "Bus.h"
#include "Node.h"
#include "Queue.h"
class Station {
private: 
    //direction 1 moving from s smaller -> sbigger 
    // direction 2 moving from s bigger -> ssmaller
    PriorityQueue<Passenger> mPassengerQueue1;
    PriorityQueue<Passenger> mPassengerQueue2;
    
    Queue<Passenger> wPassengerQueue1;
    Queue<Passenger> wPassengerQueue2;

    
    Queue<Bus> mBusQueue1;
    Queue<Bus> mBusQueue2;

    Queue<Bus> wBusQueue1;
    Queue<Bus> wBusQueue2;

public:

    void addPassenger2station(Passenger& p) {
        // Normal = 1 , pregnant = 2, POD = 3, aged = 4 , WP = 5
        if (p.getType() == 5) {
            if (p.getStartStation() < p.getEndStation()) {
                wPassengerQueue1.enqueue(p);
            } 
            else if (p.getStartStation() > p.getEndStation()) {
                wPassengerQueue2.enqueue(p);
            }
        }
        else if (p.getType() >= 1 && p.getType() <= 4){
            if (p.getStartStation() < p.getEndStation()){
                mPassengerQueue1.enqueue(p, p.getType());
            }
            else if (p.getStartStation() > p.getEndStation()) {
                mPassengerQueue2.enqueue(p, p.getType());
            }
        }
    }

    void addBus2Station(Bus& bus){
        // Mbus = 1 , Wbus = 2
        if (bus.getBusType() == 1){
            if (bus.getDirection() == 1){
                mBusQueue1.enqueue(bus);
            }
            else if (bus.getDirection() == 2){
                mBusQueue2.enqueue(bus);
            }
        }

        else if (bus.getBusType() == 2){
            if (bus.getDirection() == 1){
                wBusQueue1.enqueue(bus);
            }
            else if (bus.getDirection() == 2){
                wBusQueue2.enqueue(bus);
            }
        }

    }

    int promotePassengers(int time, int maxWaitTime){
        int numOfPromotedPassengers = 0;

        Node <Passenger> *temp = mPassengerQueue1.getFrontPtr();
        Passenger p = temp->getItem();
        while (temp != nullptr){
            if (time - temp->getItem().getArrivalTime() > maxWaitTime){
                mPassengerQueue1.dequeue(p);
                mPassengerQueue1.enqueue(p, 4);
                numOfPromotedPassengers++;
            }
            temp = temp->getNext();
        }

        temp = mPassengerQueue2.getFrontPtr();
        while (temp != nullptr){
            if (time - temp->getItem().getArrivalTime() > maxWaitTime){
                mPassengerQueue2.dequeue(p);
                mPassengerQueue2.enqueue(p, 4);
                numOfPromotedPassengers++;
            }
            temp = temp->getNext();
        }

        return numOfPromotedPassengers;
    }


    void removePassenger(int id){
        Node <Passenger> *temp = mPassengerQueue2.getFrontPtr();
        while (temp != nullptr){
            Passenger p = temp->getItem(); 
            if (p.getID() == id){
                mPassengerQueue2.dequeue(p);
                return;
            }
            temp = temp->getNext();
        }
    }


    Passenger* dequeueMPassenger1(){
    if (!mPassengerQueue1.isEmpty()) {
        Passenger* temp = new Passenger;
        mPassengerQueue1.dequeue(*temp);
        return temp;
    } else {
        return nullptr;
    }
}

Passenger* dequeueMPassenger2(){
    if (!mPassengerQueue2.isEmpty()) {
        Passenger* temp = new Passenger;
        mPassengerQueue2.dequeue(*temp);
        return temp;
    } else {
        return nullptr;
    }
}

Passenger* dequeueWPassenger1(){
    if (!wPassengerQueue1.isEmpty()) {
        Passenger* temp = new Passenger;
        wPassengerQueue1.dequeue(*temp);
        return temp;
    } else {
        return nullptr;
    }
}

Passenger* dequeueWPassenger2(){
    if (!wPassengerQueue2.isEmpty()) {
        Passenger* temp = new Passenger;
        wPassengerQueue2.dequeue(*temp);
        return temp;
    } else {
        return nullptr;
    }
}


//FOR TSTING
PriorityQueue<Passenger> getMPassengerQueue1(){
    return mPassengerQueue1;
}

PriorityQueue<Passenger> getMPassengerQueue2(){
    return mPassengerQueue2;
}

Queue<Passenger> getWPassengerQueue1(){
    return wPassengerQueue1;
}

Queue<Passenger> getWPassengerQueue2(){
    return wPassengerQueue2;
}

Queue<Bus> getMBusQueue1(){
    return mBusQueue1;
}

Queue<Bus> getMBusQueue2(){
    return mBusQueue2;
}

Queue<Bus> getWBusQueue1(){
    return wBusQueue1;
}

Queue<Bus> getWBusQueue2(){
    return wBusQueue2;
}





};

#endif


//add bus direction to bus lass


// Station (object name will be the station number):
// --- linked priority queue 1 -> passengers at the station direction 1
// --- linked priority queue 2 -> passengers at the station direction 2
// --- linked queue 1 -> Mbuses at the station direction 1
// --- linked queue 2 -> Mbuses at the station direction 2
// --- linked queue 3 -> Wbuses at the station direction 1
// --- linked queue 4 -> Wbuses at the station direction 2