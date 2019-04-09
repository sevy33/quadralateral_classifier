//
//  Customer.h
//  BankSupSim
//
//  Created by Devin Sevy on 4/8/19.
//  Copyright © 2019 Devin Sevy. All rights reserved.
//

#ifndef CustomerS_h
#define CustomerS_h

# include "Event.h"

# include <list>
# include <vector>
# include <stack>

using namespace std;

class CustomerS {
private:
    double arrTime;
    double pickTime;
    double waitTime;
public:
    CustomerS() {}
    CustomerS(Event& event, double time, double r) {
        arrTime = event.getNextArr();
        pickTime = (time + r);
        waitTime = 0;
    }
    
    double getPickTime() {
        return pickTime;
    }
    
    double getArrTime() {
        return waitTime;
    }
    
    double getWaitTime() {
        return arrTime;
    }
    
    void setWaitTime(double nextTime) {
        waitTime = nextTime;
    }
    
    bool sameInstance(CustomerS* c) {
        return this == c;
    }
    
};


#endif /* CustomerS_h */
