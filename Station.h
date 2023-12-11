
#ifndef _Station
#define _Station

#include "PriorityQueue.h"
#include "Passenger.h" 
#include "Bus.h"
#include "Node.h"
#include "Queue.h"
#include "LinkedList.h"
class Station {
private: 
    //direction 1 moving from s smaller -> sbigger 
    // direction 2 moving from s bigger -> ssmaller
    LinkedList<Passenger*> NPassengerList1;
    LinkedList<Passenger*> NPassengerList2;

    PriorityQueue<Passenger*> SPassengerQueue1;
    PriorityQueue<Passenger*> SPassengerQueue2;
    
    Queue<Passenger*> wPassengerQueue1;
    Queue<Passenger*> wPassengerQueue2;

    
    Queue<Bus> mBusQueue1;
    Queue<Bus> mBusQueue2;

    Queue<Bus> wBusQueue1;
    Queue<Bus> wBusQueue2;

public:

    void addPassenger2station(Passenger *p) {
        // Normal = 1 , pregnant = 2, POD = 3, aged = 4 , WP = 5
        if (p->getType() == 5) {
            if (p->getStartStation() < p->getEndStation()) {
                wPassengerQueue1.enqueue(p);
            } 
            else if (p->getStartStation() > p->getEndStation()) {
                wPassengerQueue2.enqueue(p);
            }
        }
        else if (p->getType() == 1){
            if (p->getStartStation() < p->getEndStation()){
                NPassengerList1.InsertEnd(p);
            }
            else if (p->getStartStation() > p->getEndStation()) {
                NPassengerList2.InsertEnd(p);
            }
        }

        else if (p->getType() >= 2 && p->getType() <= 4){
            if (p->getStartStation() < p->getEndStation()){
                SPassengerQueue1.enqueue(p, p->getType());
            }
            else if (p->getStartStation() > p->getEndStation()) {
                SPassengerQueue2.enqueue(p, p->getType());
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


    int promotePassengers(int timestep, int maxWaitingTime) {
        int promotedPassengersCount = 0;
        for (auto passenger : NPassengerList1) {
            if (timestep - passenger->getArrivalTime() > maxWaitingTime) {
                SPassengerQueue1.enqueue(passenger, 4);
                NPassengerList1.RemovewithItem(passenger);
                promotedPassengersCount++;
            }
        }

        for (auto passenger : NPassengerList2) {
            if (timestep - passenger->getArrivalTime() > maxWaitingTime) {
                SPassengerQueue2.enqueue(passenger, 4);
                NPassengerList2.RemovewithItem(passenger);
                promotedPassengersCount++;
            }
        }

    
        return promotedPassengersCount;
    }




    void removePassenger(int id){
        Node <Passenger*> *temp = SPassengerQueue2.getFrontPtr();
        while (temp != nullptr){
            Passenger* p = temp->getItem(); 
            if (p->getID() == id){
                SPassengerQueue2.dequeue(p);
                return;
            }
            temp = temp->getNext();
        }
    }


    Passenger* dequeueMPassenger1(){
    if (!SPassengerQueue1.isEmpty()) {
        Passenger* temp = new Passenger;
        SPassengerQueue1.dequeue(temp);
        return temp;
    } else {
        return nullptr;
    }
}

Passenger* dequeueMPassenger2(){
    if (!SPassengerQueue2.isEmpty()) {
        Passenger* temp = new Passenger;
        SPassengerQueue2.dequeue(temp);
        return temp;
    } else {
        return nullptr;
    }
}

Passenger* dequeueWPassenger1(){
    if (!wPassengerQueue1.isEmpty()) {
        Passenger* temp = new Passenger;
        wPassengerQueue1.dequeue(temp);
        return temp;
    } else {
        return nullptr;
    }
}

Passenger* dequeueWPassenger2(){
    if (!wPassengerQueue2.isEmpty()) {
        Passenger* temp = new Passenger;
        wPassengerQueue2.dequeue(temp);
        return temp;
    } else {
        return nullptr;
    }
}


//FOR TSTING
PriorityQueue<Passenger*> getSPassengerQueue1(){
    return SPassengerQueue1;
}

PriorityQueue<Passenger*> getSPassengerQueue2(){
    return SPassengerQueue2;
}

Queue<Passenger*> getWPassengerQueue1(){
    return wPassengerQueue1;
}

Queue<Passenger*> getWPassengerQueue2(){
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

LinkedList<Passenger*> getNPassengerList1(){
    return NPassengerList1;
}

LinkedList<Passenger*> getNPassengerList2(){
    return NPassengerList2;}
    



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
