//
//  main.cpp
//  BankSupSim
//
//  Created by Devin Sevy on 4/1/19.
//  Copyright © 2019 Devin Sevy. All rights reserved.
//

#include "Teller.hpp"
#include "Customer.hpp"
#include "RandDouble.hpp"
# include "CustomerS.h"
# include "Event.h"
# include <iostream>
# include <list>
# include <vector>
# include <stack>
# include <string>
# include <queue>

using namespace std;

RandDouble randomizer;

void runBank(double avgArrivalRt, double maxServTime, unsigned int seed) {
    int numTellers = 6;
    int numMinutes = 720;
    double totalWait = 0;
    int numCustomer = 0;
    double totalServeTime = 0;
    vector<Teller> teller(numTellers);
    queue<Customer> line;
    
    
    for(double time = 1;time <= numMinutes;time++) {
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
    for(int i=0;i < teller.size();i++) {
        totalServeTime += teller[i].getTime();
    }
    cout << "average:" << totalWait/numCustomer << endl;
    cout << "total Cust:" << numCustomer << endl;
}

typedef struct {
    double numDept;
    double totWait;
    double totServ;
}stat;

bool compare(CustomerS& c1, CustomerS& c2 )
{
    return (c1.getPickTime() < c2.getPickTime());
}

void runSup(double avgArrivalRt, double maxServTime, unsigned int seed) {
    int numTellers = 6;
    double numMinutes = 720;
    bool isList, isQueue;
    queue<CustomerS> q;
    vector<CustomerS> l;
    vector<CustomerS>::iterator list;
    Event event(numMinutes);
    stat s = {0.0, 0.0, 0.0};
    
    double time = 0;
    while(time <= numMinutes) {
        isList = (!l.empty());
        isQueue = (!q.empty());
        time = event.checkEvent(numMinutes, isList, isQueue);
        
        if(event.getNextArr() == time) {
            CustomerS c(event, time, randomizer.fRand(.1, maxServTime, seed));
            l.push_back(c);
            event.setNextArr(event.getNextArr(), avgArrivalRt);
            list = min_element(l.begin(), l.end(), compare);
            if((*list).getPickTime() < event.getNextCheckout()) event.setNextCheckout((*list).getPickTime());
        }
        
        if(event.getNextCheckout() == time) {
            list = min_element(l.begin(), l.end(), compare);
            if(q.empty()) event.setNextDept(event.getNextCheckout(), rand() % 6 + 1);
            q.push(*list);
            l.erase(list);
            
            if(!l.empty()) {
                list = min_element(l.begin(), l.end(), compare);
                event.setNextCheckout((*list).getPickTime());
            } else {
                event.setNextCheckout(numMinutes +1);
            }
        }
        
        if(event.getNextDept() == time) {
            //cout << "depart" << endl;
            CustomerS temp = q.front();
            q.pop();
            s.numDept++;
            s.totWait += temp.getWaitTime();
            s.totServ += (event.getNextDept() - (temp.getPickTime() + temp.getWaitTime()));
            if(!q.empty()) {
                q.front().setWaitTime(event.getNextDept() - q.front().getPickTime());
                event.setNextDept(event.getNextDept(), numTellers);
            } else {
                event.setNextDept(numMinutes, 1);
            }
        }
    }
    
    double avg_wait = s.totWait / s.numDept;
    double avg_serv = s.totServ / s.numDept;
    
    cout<<"Average Wait time:"<< avg_wait<<endl;
    cout << "Serve time :"<<avg_serv<<endl;
    cout << "Customer :"<<s.numDept<<endl;
}

int main(int argc, const char * argv[]) {
    double avgArrivalRt = atof(argv[1]);
    double maxServTime = atof(argv[2]);
    unsigned int seed = atoi(argv[3]);
    
    runBank(avgArrivalRt, maxServTime, seed);
    runSup(avgArrivalRt, maxServTime, seed);
    
    return 0;
    
    
}
