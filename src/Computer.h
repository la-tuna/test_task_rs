#ifndef COMPUTER_H
#define COMPUTER_H

using namespace std;
#include <iostream>

class Computer
{
public:
    string type;
    string inventoryNumber;
    string macAddress;
    string operatingSystem;
    string commissioningDate;
    string decommissioningDate;

    Computer(string type, string inventoryNumber, string macAddress, string operatingSystem, string commissioningDate, string decommissioningDate) {
        this->type = type;
        this->inventoryNumber = inventoryNumber;
        this->macAddress = macAddress;
        this->operatingSystem = operatingSystem;
        this->commissioningDate = commissioningDate;
        this->decommissioningDate = decommissioningDate;
    }
};

#endif