#include "UserInteraction.h"
#include <sstream>
#include <iomanip>

UserInteraction::UserInteraction(Administration* administration) {
    this->administration = administration;
}

void UserInteraction::loadFromFile() {
    string path;
    cout << "\n������� ���� � �����: ";
    cin >> path;

    try {
        administration->loadFromFile(path);
        cout << "������ ������� ��������� �� �����" << endl;
    }
    catch (const invalid_argument& error) {
        cout << "������: " << error.what() << endl;
    }
}

void UserInteraction::writeToFile() {
    string path;
    cout << "\n������� ���������� ���� � �����, ������� ����������: ";
    cout << "\n(���� ���� �� ����������, �� ��������� �������������)\n";
    cin >> path;

    try {
        administration->writeToFile(path);
        cout << "������ ������� �������� � ����" << endl;
    }
    catch (const invalid_argument& error) {
        cout << "������: " << error.what() << endl;
    }
}

void UserInteraction::addComputer() {
    string type, inventoryNumber, macAddress, operatingSystem, commissioningDate, decommissioningDate;
    cout << "\n������� ��� ����������: ";
    cin >> type;

    cout << "������� ����������� ����� ����������: ";
    cin >> inventoryNumber;
    bool validInNum = false;
    while (!validInNum) {
        try {
            if (int(inventoryNumber.length()) != 6 || !all_of(inventoryNumber.begin(), inventoryNumber.end(), isdigit)) {
                throw invalid_argument("����������� ����� ������ �������� �� 6 ����");
            }
            validInNum = true;
        }
        catch (const invalid_argument& error) {
            cout << "������: " << error.what() << endl;
            cout << "������� ����������� ����� �����: ";
            getline(cin >> ws, inventoryNumber);
        }
    }

    cout << "������� MAC-����� ����������: ";
    cin >> macAddress;
    cout << "������� ������������ ������� ����������: ";
    cin >> operatingSystem;
    cout << "������� ���� ����� ���������� � ������������ (��-��-����): ";
    cin >> commissioningDate;
    cout << "������� ���� ������ ���������� �� ������������ (��-��-����): ";
    cin >> decommissioningDate;

    administration->addComputer(Computer(type, inventoryNumber, macAddress, operatingSystem, commissioningDate, decommissioningDate));
}

void UserInteraction::removeComputer() {
    string inventoryNumber;
    cout << "\n������� ����������� ����� ���������� ��� ��������: ";
    cin >> inventoryNumber;

    administration->removeComputer(inventoryNumber);
}

void UserInteraction::updateComputer() {
    string inventoryNumber, type, macAddress, operatingSystem, commissioningDate, decommissioningDate;
    cout << "\n������� ����������� ����� ���������� ��� ����������: ";
    cin >> inventoryNumber;

    Computer* computer = administration->findComputer(inventoryNumber);
    bool validNum = false;
    while (!validNum) {
        try {
            if (computer == nullptr) {
                throw invalid_argument("��������� � ����������� ������� " + inventoryNumber + " �� ������");
            }
            validNum = true;
        }
        catch (const invalid_argument& error) {
            cout << "������: " << error.what() << endl;
            cout << "������� ����������� ����� �����: ";
            getline(cin >> ws, inventoryNumber);
            computer = administration->findComputer(inventoryNumber);
        }
    }

    // ������ ��������� ������� ��� ����������
    vector<string> properties = { "���", "MAC-�����", "������������ �������", "���� ����� � ������������", "���� ������ �� ������������" };

    // ����� �������� ��� ����������
    cout << "\n�������� ��������, ������� ������ ��������:\n";
    for (int i = 0; i < properties.size(); i++) {
        cout << i + 1 << ". " << properties[i] << endl;
    }
    cout << "������� ����� ��������: ";
    int choice;
    cin >> choice;

    if (choice < 1 || choice > properties.size()) {
        cout << "\n�������� �����. �������� �������� �� ������" << endl;
        return;
    }

    string propertyToUpdate = properties[choice - 1];
    string newValue;
    cout << "������� ����� �������� ��� �������� " << propertyToUpdate << ": ";
    getline(cin >> ws, newValue);

    // ���� �������� ���������� ��������
    if (propertyToUpdate == "���") {

        // �������� ���������� ���� ����������
        bool validType = false;
        while (!validType) {
            try {
                if (!newValue.empty() && newValue != "������������" && newValue != "�������" && newValue != "��������") {
                    throw invalid_argument("�������� ��� ����������. ���������� ��������: ������������, �������, ��������");
                }
                validType = true;
            }
            catch (const invalid_argument& error) {
                cout << "������: " << error.what() << endl;
                cout << "������� ��� ���������� �����: ";
                getline(cin >> ws, newValue);
            }
        }

        computer->type = newValue;
        cout << "�������� ������� ���������";
    }
    else if (propertyToUpdate == "MAC-�����") {
        computer->macAddress = newValue;
        cout << "�������� ������� ���������";
    }
    else if (propertyToUpdate == "������������ �������") {
        computer->operatingSystem = newValue;
        cout << "�������� ������� ���������";
    }
    else if (propertyToUpdate == "���� ����� � ������������") {
        computer->commissioningDate = newValue;
        cout << "�������� ������� ���������";
    }
    else if (propertyToUpdate == "���� ������ �� ������������") {
        computer->decommissioningDate = newValue;
        cout << "�������� ������� ���������";
    }
}

void UserInteraction::findComputer() {
    string inventoryNumber;
    cout << "\n������� ����������� ����� ���������� ��� ������ ������ � ���: ";
    cin >> inventoryNumber;

    Computer* computer = administration->findComputer(inventoryNumber);
    if (computer == nullptr) {
        cout << "\n��������� �� ������" << endl;
    }
    else {
        cout << left << setw(20) << "���" << setw(25) << "����������� �����" << setw(25) << "MAC-�����" << setw(25) << "������������ �������" << setw(20) << "���� ����� � ����." << setw(20) << "���� ������ �� ����." << endl;
        cout << left <<  setw(20) << computer->type << setw(25) << computer->inventoryNumber << setw(25) << computer->macAddress << setw(25) << computer->operatingSystem << setw(20) << computer->commissioningDate << setw(20) << computer->decommissioningDate << endl;
    }
}

void UserInteraction::printComputers() {
    cout << "\n������ �����������:\n";
    cout << left << setw(20) << "���" << setw(25) << "����������� �����" << setw(25) << "MAC-�����" << setw(25) << "������������ �������" << setw(20) << "���� ����� � ����." << setw(20) << "���� ������ �� ����." << endl;
    int i = 1;
    for (auto& computer : administration->computers) {
        cout << left << setw(4) << i++ << setw(20) << computer.type << setw(25) << computer.inventoryNumber << setw(25) << computer.macAddress << setw(25) << computer.operatingSystem << setw(20) << computer.commissioningDate << setw(20) << computer.decommissioningDate << endl;
    }
}

void UserInteraction::start() {
    int choice;
    do {
        cout << "\n\n1. �������������� ������ �� �����" << endl;
        cout << "2. �������� ���������" << endl;
        cout << "3. �������� ���������" << endl;
        cout << "4. ������� ���������" << endl;
        cout << "5. ����� ���������" << endl;
        cout << "6. �������� ������ ������ �����������" << endl;
        cout << "7. ������������� ������ � ����" << endl;
        cout << "8. ��������� � �����" << endl;
        cout << "������� ���� �����: ";

        while (!(cin >> choice)) {
            cout << "������: ���� ������ ���� ������" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "�������� ���� ����� �����: ";
        }

        switch (choice) {
        case 1:
            loadFromFile();
            break;
        case 2:
            addComputer();
            break;
        case 3:
            updateComputer();
            break;
        case 4:
            removeComputer();
            break;
        case 5:
            findComputer();
            break;
        case 6:
            printComputers();
            break;
        case 7:
            writeToFile();
            break;
        }
    } while (choice != 8);
}