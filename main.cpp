//
// Created by gabriel on 12/4/18.
//

#include <cstdlib>
#include <iostream>
#include <queue>
#include <tuple>

typedef std::tuple<int, int, char> event;

using std::priority_queue;
using std::queue;
using std::vector;
using std::greater;
using std::get;
using std::cout;
using std::endl;

void simulate();

int main() {
    simulate();
    return EXIT_SUCCESS;
}

void simulate() {
    priority_queue<event, vector<event>, greater<event>> eventQueue;
    queue<event> bankLine;

    bool tellerAvailable{true};
    int totalWaitTime{0};

    //while( DATA FILE IS NOT EMPTY)

    while (!eventQueue.empty()) {
        event newEvent = eventQueue.top();
        eventQueue.pop();

        int currentTime = get<0>(newEvent);

        //if newEvent is an Arrival
        if (get<2>(newEvent) == 'A') {
            if (bankLine.empty() && tellerAvailable) {
                int departureTime = currentTime + get<0>(newEvent);
                event newDeptEvent = std::make_tuple(departureTime, 0, 'D');
                eventQueue.push(newDeptEvent);
                tellerAvailable = false;
            } else {
                bankLine.push(newEvent);
            }
        }

        //if newEvent is a Departure
        if (get<2>(newEvent) == 'D') {
            if (!bankLine.empty()) {
                event customer = bankLine.front();
                bankLine.pop();
                int departureTime = currentTime + get<1>(newEvent);
                event newDeptEvent = std::make_tuple(departureTime, 0, 'D');
                eventQueue.push(newDeptEvent);
                totalWaitTime += currentTime - get<1>(bankLine.front());
            } else {
                tellerAvailable = true;
            }
        }
    }
        cout << "Final Statistics:" << endl;
        cout << "\t Total number of people processed: " << endl;
        cout << "\t Average amount of time spent waiting: " << totalWaitTime << endl;

}


