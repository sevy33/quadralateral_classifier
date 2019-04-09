//
//  main.cpp
//  SupSim
//
//  Created by Devin Sevy on 4/2/19.
//  Copyright © 2019 Devin Sevy. All rights reserved.
//

#include "Customer.h"
#include "Event.h"
#include "RandDouble.h"
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

static int numTellers = 6;
static double numMinutes = 720;
static RandDouble randomizer;

typedef struct {
    double numDept;
    double totWait;
    double totServ;
} stat;

bool compare(Customer& c1, Customer& c2) {
    return (c1.getPickTime() < c2.getPickTime());
}

void runSimulation(double numMinutes, queue<Customer> q, vector<Customer> l, double maxServTime, unsigned int seed, double avgArrivalRt, stat &s) {
    bool isList, isQueue;
    Event event(numMinutes);
    vector<Customer>::iterator list;
    double time = 0;
    while (time <= numMinutes) {
        isList = (!l.empty());
        isQueue = (!q.empty());
        time = event.checkEvent(numMinutes, isList, isQueue);
        
        if (event.getNextArr() == time) {
            Customer c(event, time, randomizer.fRand(.1, maxServTime, seed));
            l.push_back(c);
            event.setNextArr(event.getNextArr(), avgArrivalRt);
            list = min_element(l.begin(), l.end(), compare);
            if ((*list).getPickTime() < event.getNextCheckout()) event.setNextCheckout((*list).getPickTime());
        }
        
        if (event.getNextCheckout() == time) {
            list = min_element(l.begin(), l.end(), compare);
            if (q.empty()) event.setNextDept(event.getNextCheckout(), rand() % 6 + 1);
            q.push(*list);
            l.erase(list);
            
            if (!l.empty()) {
                list = min_element(l.begin(), l.end(), compare);
                event.setNextCheckout((*list).getPickTime());
            } else {
                event.setNextCheckout(numMinutes + 1);
            }
        }
        
        if (event.getNextDept() == time) {
            Customer temp = q.front();
            q.pop();
            s.numDept++;
            s.totWait += temp.getWaitTime();
            s.totServ += (event.getNextDept() - (temp.getPickTime() + temp.getWaitTime()));
            if (!q.empty()) {
                q.front().setWaitTime(event.getNextDept() - q.front().getPickTime());
                event.setNextDept(event.getNextDept(), numTellers);
            } else {
                event.setNextDept(numMinutes, 1);
            }
        }
    }
}

int main(int argc, const char * argv[]) {

    // Reading user input 
    double avgArrivalRt = atof(argv[1]);
    double maxServTime = atof(argv[2]);
    unsigned int seed = atoi(argv[3]);

    // Simple input validation
    if (avgArrivalRt <= 0) {
        cout << "Average arrival rate must be greater than 0.\n";
    }
    if (maxServTime <= 0) {
        cout << "Max service time must be greater than 0.\n";
    }
    if (seed <= 0) {
        cout << "Random seed must be greater than 0.\n";
    }

    // Creating data structures
    queue<Customer> q;
    vector<Customer> l;

    // Running simulation
    stat s = {0.0, 0.0, 0.0};
    runSimulation(numMinutes, q, l, maxServTime, seed, avgArrivalRt, s);
    
//    double time = 0;
//    while (time <= numMinutes) {
//        isList = (!l.empty());
//        isQueue = (!q.empty());
//        time = event.checkEvent(numMinutes, isList, isQueue);
//
//        if (event.getNextArr() == time) {
//            Customer c(event, time, randomizer.fRand(.1, maxServTime, seed));
//            l.push_back(c);
//            event.setNextArr(event.getNextArr(), avgArrivalRt);
//            list = min_element(l.begin(), l.end(), compare);
//            if ((*list).getPickTime() < event.getNextCheckout()) event.setNextCheckout((*list).getPickTime());
//        }
//
//        if (event.getNextCheckout() == time) {
//            list = min_element(l.begin(), l.end(), compare);
//            if (q.empty()) event.setNextDept(event.getNextCheckout(), rand() % 6 + 1);
//            q.push(*list);
//            l.erase(list);
//
//            if (!l.empty()) {
//                list = min_element(l.begin(), l.end(), compare);
//                event.setNextCheckout((*list).getPickTime());
//            } else {
//                event.setNextCheckout(numMinutes + 1);
//            }
//        }
//
//        if (event.getNextDept() == time) {
//            Customer temp = q.front();
//            q.pop();
//            s.numDept++;
//            s.totWait += temp.getWaitTime();
//            s.totServ += (event.getNextDept() - (temp.getPickTime() + temp.getWaitTime()));
//            if (!q.empty()) {
//                q.front().setWaitTime(event.getNextDept() - q.front().getPickTime());
//                event.setNextDept(event.getNextDept(), numTellers);
//            } else {
//                event.setNextDept(numMinutes, 1);
//            }
//        }
//    }

    // Print simulation results
    cout << "Average wait time per customer: " << s.totWait / s.numDept << endl;
    cout << "Number of customers: " << s.numDept << endl;
    
    return 0;
}
