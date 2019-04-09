//
//  main.cpp
//  BankSupSim
//
//  Created by Devin Sevy on 4/1/19.
//  Copyright © 2019 Devin Sevy. All rights reserved.
//

#include "Customer.hpp"
#include "RandDouble.hpp"
#include "Teller.hpp"
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

static int numTellers = 6;
static int simulationDuration = 720; // minutes
static RandDouble randomizer;

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
    vector<Teller> teller(numTellers);
    queue<Customer> line;

    // Running simulation
    double totalWait = 0;
    int numCustomer = 0;
    double totalServeTime = 0;
    for (double time = 1; time <= simulationDuration; time++) {
        Customer newCustomer(time, randomizer.fRand(.1, maxServTime, seed));
        line.push(newCustomer);
        for (int i = 0; i < numTellers; i++) {
            time++;
            if (teller[i].isFree() & !line.empty()) {
                double frontRand = randomizer.fRand(.1, maxServTime, seed);
                Customer frontCustomer = line.front();
                numCustomer++;
                totalWait += (time - frontCustomer.getArrival());
                teller[i].addCustomer(frontCustomer);
                teller[i].addTime(frontRand);
                line.pop();
            }
        }
    }
    for (int i = 0; i < teller.size(); i++) {
        totalServeTime += teller[i].getTime();
    }
    cout << "average:" << totalWait / numCustomer << endl;
    cout << "total Cust:" << numCustomer << endl;

    return 0;

}
