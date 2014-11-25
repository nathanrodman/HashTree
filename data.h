//
//  data.h
//  Lab4.Rodman.260
//
//  Created by Nathan Rodman on 5/30/14.
//  Copyright (c) 2014 nathan.rodman. All rights reserved.
//

#ifndef Lab4_Rodman_260_data_h
#define Lab4_Rodman_260_data_h

#include <iostream>
#include <cstring>
using namespace std;

class data
{
public:
    data();
    data(const data & aData);
    ~data();
    
    void setName(char * aName);
    void setPhone(char * aPhone);
    void setProduct(char * aProduct);
    void setEvents(char * anEvent);
    
    void getName(char * aName) const;
    void getPhone(char * aPhone) const;
    void getProduct(char * aProduct) const;
    void getEvents(char * anEvent) const;
    
    const data& operator= (const data & aData);
    
    
    const void print(void);
    
private:
    char * name;
    char * phone;
    char * product;
    char * events;
    
};

bool operator< (const data& aData1, const data & aData2);

#endif
