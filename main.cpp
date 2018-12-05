//
// Created by gabriel on 12/4/18.
//

#include <cstdlib>
#include <iostream>
#include <queue>
#include <tuple>
#include <fstream>
#include <string>

typedef std::tuple<int, int, char> event;

using std::priority_queue;
using std::queue;
using std::vector;
using std::greater;
using std::get;
using std::make_tuple;
using std::cout;
using std::endl;
using std::string;

void simulate(const string &);

int main() {
    simulate("../bankData.txt");
    return EXIT_SUCCESS;
}

void simulate(const string & fileName) {
    priority_queue<event, vector<event>, greater<event>> eventQueue;
    queue<event> bankLine;

    bool tellerAvailable{true};
    int totalWaitTime{0};
    int customersProcessed{0};

    //Creating the initial eventQueue
    string line;
    std::ifstream myFile (fileName);
    while(getline(myFile, line)) {
        int comma = line.find_first_of(",");
        string time = line.substr(0, comma);
        string leng = line.substr(comma + 1);
        event newArrivalEvent = make_tuple(std::stoi(time), std::stoi(leng), 'A');
        eventQueue.push(newArrivalEvent);
        customersProcessed++;
    }
    myFile.close();

    //Simulation Begins
    cout << "Simulation Begins" << endl;

    while (!eventQueue.empty()) {
        event newEvent = eventQueue.top();
        eventQueue.pop();

        int currentTime = get<0>(newEvent);

        //if newEvent is an Arrival
        if (get<2>(newEvent) == 'A') {
            cout << "Processing an arrival event at time: " << currentTime << endl;
            if (bankLine.empty() && tellerAvailable) {
                int departureTime = currentTime + get<1>(newEvent);
                event newDeptEvent = make_tuple(departureTime, 0, 'D');
                eventQueue.push(newDeptEvent);
                tellerAvailable = false;
            } else {
                bankLine.push(newEvent);
            }
        }

        //if newEvent is a Departure
        if (get<2>(newEvent) == 'D') {
            cout << "Processing a departure event at time: " << currentTime << endl;
            if (!bankLine.empty()) {
                event customer = bankLine.front();
                bankLine.pop();
                int departureTime = currentTime + get<1>(customer);
                event newDeptEvent = make_tuple(departureTime, 0, 'D');
                eventQueue.push(newDeptEvent);
                totalWaitTime += currentTime - get<0>(customer);
            } else {
                tellerAvailable = true;
            }
        }
    }

    //Final Stats
    double average = static_cast<double>(totalWaitTime) / customersProcessed;
    cout << "Simulation Ends\n" << endl;
    cout << "Final Statistics:" << endl;
    cout << "\t Total number of people processed: " <<  customersProcessed << endl;
    cout << "\t Average amount of time spent waiting: " << average << endl;
}

