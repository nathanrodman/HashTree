//
//  main.cpp
//  Lab4.Rodman.260
//
//  Created by Nathan Rodman on 5/30/14.
//  Copyright (c) 2014 nathan.rodman. All rights reserved.
//

#include "data.h"
#include "hashTree.h"

#include <iostream>
#include <iomanip>
using namespace std;

void displayMenu();
void executeCmd(const char ch, hashTree & aCollection);
void add(data & aData);

int main(int argc, const char * argv[])
{
    char fileName[] = "vendors.txt";
    hashTree collection(fileName);
    
    char decider = 'a';
    
    cout << "\t\t------------------------------" << endl;
    cout << "\t\t|| Portland Vendor Database ||" << endl;
    cout << "\t\t------------------------------\n" << endl;
    
    while(decider != 'q')
    {
        displayMenu();
        cin >> decider;
        executeCmd(decider, collection);
    }
    collection.writeOut(fileName);
    return 0;
}

void displayMenu()
{
    cout << "Please enter one of the following menu options:\n" << endl;
    cout << "(a) Add a vendor" << setw(24) << "(r) Remove a vendor" << endl;
    cout << "(s) Search" << setw(30) << "(d) Display vendors" << endl;
    cout << "(q) Quit the Program" << endl;
    cout << "Enter option: ";
    
}

void executeCmd(const char ch, hashTree & aCollection)
{
    data aData;
    char choice;
    char vendor[100];
    char product[100];
    int index;
    bool tf;
    
    switch (ch) {
        case 'a':
            add(aData);
            aCollection.add(aData);
            break;
            
        case 'r':
            cin.ignore(100, '\n');
            cout << "Which vendor would you like to remove?: " << endl;
            cin.get(vendor, 100, '\n');
            cin.ignore(100, '\n');
            aCollection.remove(vendor);
            break;
            
        case 's':
            cout << "Would you like to search by Vendor or Product?" << endl;
            cout << "(v) for Vendor \t(p) for Product" << endl;
            cin >> choice;
            cin.ignore(100, '\n');
            if (choice == 'v' || choice == 'V')
            {
                cout << "Enter the name of the vendor you'd like to search for: ";
                cin.get(vendor, 100, '\n');
                tf = aCollection.retrieve(vendor, aData);
                if (tf)
                    aData.print();
            }
            if (choice == 'P' || choice == 'p')
            {
                cout << "Enter the product you'd like to search for: ";
                cin.get(product, 100, '\n');
                tf = aCollection.retrieve(product, index);
                if(tf)
                    aCollection.displayProducts(index);
            }
            break;
            
        case 'd':
            cout << "Would you like to display by Vendor or by Product?" << endl;
            cout << "(v) for Vendor \t(p) for Product" << endl;
            cin >> choice;
            if (choice == 'v' || choice =='V')
            {
                aCollection.displayByName();
            }
            if (choice == 'p' || choice == 'P')
            {
                aCollection.displayByType();
            }
            break;
            
            
        default:
            break;
    }
}

void add(data & aData)
{
    char name[100];
    char phone[100];
    char aProduct[100];
    char events[100];
    cin.ignore(100, '\n');
    cout << "Name of vendor: ";
    cin.get(name, 100, '\n');
    cin.ignore(100, '\n');
    cout << "Phone Number (ie. 5032221234): ";
    cin.get(phone, 100, '\n');
    cin.ignore(100, '\n');
    cout << "Enter the type of products(i.e. art, produce): ";
    cin.get(aProduct, 100, '\n');
    cin.ignore(100, '\n');
    cout << "Enter the events the vendor attends: ";
    cin.get(events, 100, '\n');
    cin.ignore(100, '\n');
    
    aData.setName(name);
    aData.setPhone(phone);
    aData.setProduct(aProduct);
    aData.setEvents(events);

}

