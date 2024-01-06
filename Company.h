#pragma once
#include "LeaveEvent.h"
#include "ArrivalEvent.h"
#include "Station.h"
#include "UI.h"
#include <string>
#include <fstream>
#include <cstdlib>
#include "LinkedList.h"
// #include "UI.h"
using namespace std;
class Company
{
	Station* stations;
	Queue<Event*> events;
	Queue<Passenger*> finishedPassengers;
	UI ui;
	int maxWaitingTime;
	int promotedPassengers;
	Event* createArrivalEvent(ifstream& file) {
		string passengerType;
		int hour, minute, id, startStation, endStation, type = -1;
		char colon;
		file >> passengerType >> hour >> colon >> minute >> id >> startStation >> endStation;
		if (passengerType == "SP") {
			string specialType;
			file >> specialType;
			if (specialType == "aged")
				type = 4;
			else if (specialType == "POD")
				type = 3;
			else
				type = 2;
		}
        else if (passengerType == "NP") {
            type = 1;
        }
        else if (passengerType == "WP") {
            type = 5;
        }
		int timestep = hour * 60 + minute;
		return new ArrivalEvent(timestep, id, type, startStation, endStation);
	}
	Event* createLeaveEvent(ifstream& file) {
		int hour, minute, id;
		char colon;
		file >> hour >> colon >> minute >> id;
		int timestep = hour * 60 + minute;
		return new LeaveEvent(timestep, id);
		
	}
	
	void randomAssigning(int timestep)
	{
		for (auto station : stations) {
			int randomNumber = rand() % 100 + 1;
			Passenger* passenger = nullptr;
			if (randomNumber < 21) {
				passenger = station->removeTopForwardSpecialPassenger();
				if (!passenger) {
					passenger = station->removeTopBackwardSpecialPassenger();
				}
			}
			else if (randomNumber < 31) {
				passenger = station->removeTopForwardWheelPassenger();
				if (!passenger) {
					passenger = station->removeTopBackwardWheelPassenger();
				}
			}
			else if (randomNumber < 61) {
				passenger = station->removeTopForwardNormalPassenger();
				if (!passenger) {
					passenger = station->removeTopBackwardNormalPassenger();
				}
			}
			if (passenger) {
				passenger->setFinishTime(timestep);
				passenger->setMovingTime(timestep);
				finishedPassengers.enqueue(passenger);
			}
		}
	}
	
	bool isAllListsEmpty() {
		for (auto station : stations) {
			if (!station->hasWaitingPassengers())
				return false;
		}
		return events.IsEmpty();
	}

	void generateOutputFile()
	{
		ofstream file("output.txt");
		file << "FT\t\t\tID\t\t\tAT\t\t\tWT\n";
		int npCount = 0,
			spCount = 0,
			wpCount = 0;
		int totalWaitingTime = 0;
		while (!finishedPassengers.IsEmpty()) {
			Passenger* passenger = finishedPassengers.Pop();

			file << timestepToHHMM(passenger->getFinishTime()) << "\t\t\t" << passenger->getID() << "\t\t\t";
			file << timestepToHHMM(passenger->getArrivalTime()) << "\t\t\t" << timestepToHHMM(passenger->get()) << '\n';

			totalWaitingTime += passenger->getWaitingTime();

			string type = passenger->getType();
			if (type == "NP")
				npCount++;
			else if (type == "SP")
				spCount++;
			else
				wpCount++;
		}
		float totalPAssengersCount = npCount + spCount + wpCount;
		file << "Passengers: " << totalPAssengersCount << "   [NP: " << npCount << ", SP: " << spCount << ", WP: " << wpCount << "]\n";
		file << "passenger Avg Wait time= " << timestepToHHMM(totalWaitingTime / totalPAssengersCount) << "\n";
		file << "Auto-promoted passengers: " << (float)promotedPassengers / totalPAssengersCount * 100.0 << "%\n";
	}

	string timestepToHHMM(int timestep) {
		string hour = to_string(timestep / 60);
		string minute = to_string(timestep % 60);
		return hour + ":" + minute;
	}
public:
	Company() {
		maxWaitingTime = -1;
		promotedPassengers = 0;
	}
	void readInputFile(string fileName) {
		ifstream file(fileName);
		//read number of stations
		int numberOfStations;
		file >> numberOfStations;
		numberOfStations++;
		while (numberOfStations--) {
			stations.InsertEnd(new Station());
		}
		//read max waiting time
		file >> maxWaitingTime;
		//read events
		int numberOfEvents;
		file >> numberOfEvents;
		while (numberOfEvents--) {
			char eventType;
			file >> eventType;
			Event* tempEvent = eventType == 'A'? createArrivalEvent(file) : createLeaveEvent(file);
			events.Push(tempEvent);
		}
		file.close();
	}

	void startSimulation() {
		ui.getMode();
		int timestep = 0;
		while (!isAllListsEmpty() && timestep < 1439) {
			while (!events.IsEmpty() && events.Peek()->getTimestep() == timestep) {
				events.Pop()->execute(stations);
			}

			for (auto station : stations) {
				promotedPassengers += station->promotePassengers(timestep, maxWaitingTime);
			}

			randomAssigning(timestep);
			
			timestep++;
			ui.printSimulationInfo(timestep, stations, finishedPassengers);
		}
		generateOutputFile();
		ui.displayEndMessage();
	}
};

