//
//  data.cpp
//  Lab4.Rodman.260
//
//  Created by Nathan Rodman on 5/31/14.
//  Copyright (c) 2014 nathan.rodman. All rights reserved.
//

#include "data.h"

data::data(): name(nullptr), phone(nullptr), product(nullptr), events(nullptr)
{
    
}

data::data(const data & aData)
{
    char tempName[100];
    char tempPhone[100];
    char tempProduct[100];
    char tempEvents[100];
    
    aData.getName(tempName);
    this->name = new char[strlen(tempName) + 1];
    strcpy(name, tempName);
    
    aData.getPhone(tempPhone);
    this->phone = new char[strlen(tempPhone) + 1];
    strcpy(phone, tempPhone);
    
    aData.getProduct(tempProduct);
    this->product = new char[strlen(tempProduct) + 1];
    strcpy(product, tempProduct);
    
    aData.getEvents(tempEvents);
    this->events = new char [strlen(tempEvents) + 1];
    strcpy(events, tempEvents);
    
    
}

data::~data()
{
    if(name)
        delete [] name;
    if(phone)
        delete [] phone;
    if(product)
        delete [] product;
    if(events)
        delete [] events;
}

void data::setName(char * aName)
{
    if(name)
        delete [] name;
    name = new char [strlen(aName) + 1];
    strcpy(name, aName);
}

void data::setPhone(char * aPhone)
{
    if(phone)
        delete [] phone;
    phone = new char [strlen(aPhone) + 1];
    strcpy(phone, aPhone);
}

void data::setProduct(char *aProduct)
{
    if(product)
        delete [] product;
    product = new char [strlen(aProduct) + 1];
    strcpy(product, aProduct);
}

void data::setEvents(char * anEvent)
{
    if(events)
        delete [] events;
    events = new char [strlen(anEvent) + 1];
    strcpy(events, anEvent);
}

void data::getName(char * aName) const
{
    strcpy(aName, name);
}

void data::getPhone(char * aPhone) const
{
    strcpy(aPhone, phone);
}

void data::getProduct(char *aProduct) const
{

    strcpy(aProduct, product);
}

void data::getEvents(char *anEvent) const
{
    strcpy(anEvent, events);
}

const data& data::operator= (const data & aData)
{
    if(this==&aData)
        return *this;
    else
    {
        char tempName[100];
        char tempPhone[100];
        char tempProduct[100];
        char tempEvents[100];
        
        aData.getName(tempName);
        aData.getPhone(tempPhone);
        aData.getProduct(tempProduct);
        aData.getEvents(tempEvents);
        
        this->setName(tempName);
        this->setPhone(tempPhone);
        this->setProduct(tempProduct);
        this->setEvents(tempEvents);
    }
    return *this;
}

const void data::print()
{
    cout << "Vendor: " << name << endl;
    cout << "\tPhone: " << phone << endl;
    cout << "\tType of product: " << product << endl;
    cout << "\tEvents attended: " << events << endl;
}

bool operator< (const data & aData1, const data & aData2)
{
    char name1[100];
    char name2[100];
    
    aData1.getName(name1);
    aData2.getName(name2);
    
    if (strcmp(name1, name2) == -1)
        return true;
    else
        return false;
}
