#pragma once
#include "LeaveEvent.h"
#include "ArrivalEvent.h"
#include "Station.h"
#include <string>
#include <fstream>
#include <cstdlib>
#include "LinkedList.h"
// #include "UI.h"
using namespace std;
class Company
{
    Station *stationsArray;
    int timeBetStations;
    LinkedList<Passenger *> finishedPassengers;
    LinkedList<Bus *> inCheckUpbuses;
    LinkedList<Bus *> MovingBusesForwards;
    LinkedList<Bus *> MovingBusesBackwards;
    int NPassengerCount;
    int SPassengerCount;
    int WPassengerCount;
    int numPromotedPassengers;
    int WbusCapacity;
    int MbusCapacity;
    int maxJourneys;
    int WcheckUpTime;
    int McheckUpTime;
    int maxWaiting;
    int BoradingDuration;
    int MbusNum;
    int WbusNum;
    int numberOfStations;
    int numberOfEvents;

public:
    Queue<Event *> events;

    Event *createArrivalEvent(ifstream &file)
    {
        string passengerType;
        int hour, minute, id, startStation, endStation, type = -1;
        char _;
        file >> passengerType >> hour >> _ >> minute >> id >> startStation >> endStation;
        if (passengerType == "SP")
        {
            string specialType;
            file >> specialType;
            if (specialType == "aged")
                type = 4;
            else if (specialType == "POD")
                type = 3;
            else
                type = 2;
        }
        else if (passengerType == "NP")
        {
            type = 1;
        }
        else if (passengerType == "WP")
        {
            type = 5;
        }
        int time = hour * 60 + minute;
        return new ArrivalEvent(time, id, type, startStation, endStation);
    }

    Event *createLeaveEvent(ifstream &file)
    {
        int hour, minute, id;
        char _;
        file >> hour >> _ >> minute >> id;
        int time = hour * 60 + minute;
        return new LeaveEvent(time, id);
    }

    void readInputFile(string fileName)
    {
        ifstream file(fileName);
        if (!file.is_open())
        {
            cout << "Error opening the file " << fileName << endl;
            return;
        }
        file >> numberOfStations;

        numberOfStations++;
        stationsArray = new Station[numberOfStations];
        int i = 0;
        while (i < numberOfStations)
        {
            stationsArray[i] = Station(i);
            i++;
        }
        // read max waiting time
        file >> timeBetStations;
        file >> WbusNum;
        file >> MbusNum;
        file >> WbusCapacity;
        file >> MbusCapacity;
        file >> maxJourneys;
        file >> WcheckUpTime;
        file >> McheckUpTime;
        file >> maxWaiting;
        file >> BoradingDuration;

        // read events
        file >> numberOfEvents;
        while (numberOfEvents--)
        {
            char eventType;
            file >> eventType;

            Event *tempEvent;
            if (eventType == 'A')
            {
                tempEvent = createArrivalEvent(file);
            }
            else if (eventType == 'L')
            {
                tempEvent = createLeaveEvent(file);
            }
            events.enqueue(tempEvent);
        }
        file.close();
    }

    // adds all the busses to the first Station
    void addBussesToFirstStation()
    {
        int maxBusNum = max(MbusNum, WbusNum);
        for (int i = 0; i < maxBusNum; i++)
        {
            if (i < MbusNum)
            {
                Bus *bus = new Bus(1, MbusCapacity, 0, 0, 0, 0);
                stationsArray[0].addBus2Station(bus);
            }
            if (i < WbusNum)
            {
                Bus *bus = new Bus(2, WbusCapacity, 0, 0, 0, 0);
                stationsArray[0].addBus2Station(bus);
            }
        }
    }

    // check if the last bus out from the station 0 was in 15 mins or more and dequeue from station 0 and add to moving busses in that case
    void releaseBussesFromFirstStation(int &lastBusOuttime)
    {
        if (lastBusOuttime >= 15)
        {
            Bus *bus;
            bus = stationsArray[0].BusQueueForwards.dequeueAndReturn();
            MovingBusesForwards.InsertEnd(bus);
            lastBusOuttime = 0;
        }
        else
            lastBusOuttime++;
    }

    // loop over the checkup list and if any of their checkuptime exceeded the time set for their type then they queued released into station 0
    void releaseBussesFromCheckUpList()
    {
        for (auto bus : inCheckUpbuses)
        {
            if (bus->getBusType() == 1)
            {
                if (bus->getCheckupTime() >= McheckUpTime)
                {
                    bus->setCheckupTime(0);
                    stationsArray[0].BusQueueForwards.enqueue(bus);
                    inCheckUpbuses.RemovewithItem(bus);
                }
                else
                {
                    bus->setCheckupTime(bus->getCheckupTime() + 1);
                }
            }
        }
    }

    // loop over the moving busses and if they reached their next station (Ttheir move time is = to the time between stations) then they dequeued from the moving busses and queued into the station they reached
    void boardingBussesInStations()
    {
        for (auto bus : MovingBusesForwards)
        {
            if (bus->getMoveTimeLastStation() >= timeBetStations)
            {
                MovingBusesForwards.RemoveBegin(bus);
                stationsArray[bus->getNextStation()].addBus2Station(bus);
                bus->setMoveTimeLastStation(0);
                if (bus->getNextStation() != numberOfStations)
                {
                    bus->setNextStation(bus->getNextStation() + 1);
                }
                else if (bus->getNextStation() == numberOfStations)
                {
                    bus->setNextStation(numberOfStations - 1);
                    bus->setCurrentJourney(bus->getCurrentJourney() + 1);
                    bus->setDirection(2);
                }
            }
            else
                bus->setMoveTimeLastStation(bus->getMoveTimeLastStation() + 1);
        }
        for (auto bus : MovingBusesBackwards)
        {
            if (bus->getMoveTimeLastStation() >= timeBetStations)
            {
                MovingBusesBackwards.RemoveBegin(bus);
                stationsArray[bus->getNextStation()].addBus2Station(bus);
                bus->setMoveTimeLastStation(0);
                if (bus->getNextStation() != 0)
                {
                    bus->setNextStation(bus->getNextStation() - 1);
                }
                else if (bus->getNextStation() == 0)
                {
                    bus->setNextStation(1);
                    bus->setCurrentJourney(bus->getCurrentJourney() + 1);
                    bus->setDirection(1);
                }
            }
            else
                bus->setMoveTimeLastStation(bus->getMoveTimeLastStation() + 1);
        }
    }

    void handleEventsInStations(int stationnum, int timeNow)
    {
        if (!events.isEmpty())
        {
            Event *event;
            events.getFront(event);
            int id = event->getId();
            if (event->getTime() == timeNow)
            {
                if (event->getType() == "Leave")
                {
                    finishedPassengers.InsertEnd(stationsArray[stationnum].removePassenger(id));
                    event->execute(stationsArray, numberOfStations);
                    events.dequeue(event);
                }
                else if (event->getType() == "Arrival")
                {
                    event->execute(stationsArray, numberOfStations);
                    events.dequeue(event);
                }
            }
        }
    }

    void simulate()
    {
        readInputFile("random_file.txt");
        int time = 0;
        int lastBusOuttime = 15; // time since last bus release from station 0, innitialized with 15 to release the first bus immediately
        addBussesToFirstStation();
        while (time < 24 * 60)
        {
            releaseBussesFromFirstStation(lastBusOuttime);
            releaseBussesFromCheckUpList();
            boardingBussesInStations();
            for (int i = 0; i < numberOfStations; i++)
            {
                stationsArray[i].promotePassengers(time, maxWaiting);
                handleEventsInStations(i, time);
            }
        }
    }
};
