#include "Administration.h"
using json = nlohmann::json;

void Administration::loadFromFile(string filename) {
    ifstream file(filename);
    json data;
    file >> data;
    for (auto& computer : data["computers"]) {
        computers.push_back({
            computer["type"].get<string>(),
            computer["inventory_number"].get<string>(),
            computer["mac_address"].get<string>(),
            computer["operating_system"].get<string>(),
            computer["commissioning_date"].get<string>(),
            computer["decommissioning_date"].get<string>()
            });
    }
    file.close();
}

void Administration::writeToFile(string filename) {
    json data;
    for (auto& computer : computers) {
        data["computers"].push_back({
            {"type", computer.type},
            {"inventory_number", computer.inventoryNumber},
            {"mac_address", computer.macAddress},
            {"operating_system", computer.operatingSystem},
            {"commissioning_date", computer.commissioningDate},
            {"decommissioning_date", computer.decommissioningDate}
            });
    }
    ofstream file(filename);
    file << data.dump(4);
    file.close();
}

void Administration::addComputer(Computer computer) {
    computers.push_back(computer);
}

void Administration::updateComputer(Computer computer) {
    for (auto& computer : computers) {
        if (computer.inventoryNumber == computer.inventoryNumber) {
            computer.type = computer.type;
            computer.macAddress = computer.macAddress;
            computer.operatingSystem = computer.operatingSystem;
            computer.commissioningDate = computer.commissioningDate;
            computer.decommissioningDate = computer.decommissioningDate;
            return;
        }
    }
}

void Administration::removeComputer(string inventoryNumber) {
    for (auto it = computers.begin(); it != computers.end(); ++it) {
        if (it->inventoryNumber == inventoryNumber) {
            computers.erase(it);
            return;
        }
    }
}

Computer* Administration::findComputer(string inventoryNumber) {
    for (auto& computer : computers) {
        if (computer.inventoryNumber == inventoryNumber) {
            return &computer;
        }
    }
    return nullptr;
}
