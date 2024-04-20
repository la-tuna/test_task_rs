#include "UserInteraction.h"
#include <sstream>
#include <iomanip>

UserInteraction::UserInteraction(Administration* administration) {
    this->administration = administration;
}

void UserInteraction::loadFromFile() {
    string path;
    cout << "\nВведите путь к файлу: ";
    cin >> path;

    try {
        administration->loadFromFile(path);
        cout << "Данные успешно загружены из файла" << endl;
    }
    catch (const invalid_argument& error) {
        cout << "Ошибка: " << error.what() << endl;
    }
}

void UserInteraction::writeToFile() {
    string path;
    cout << "\nВведите абсолютный путь к файлу, включая расширение: ";
    cout << "\n(если файл не существует, он создастся автоматически)\n";
    cin >> path;

    try {
        administration->writeToFile(path);
        cout << "Данные успешно записаны в файл" << endl;
    }
    catch (const invalid_argument& error) {
        cout << "Ошибка: " << error.what() << endl;
    }
}

void UserInteraction::addComputer() {
    string type, inventoryNumber, macAddress, operatingSystem, commissioningDate, decommissioningDate;
    cout << "\nВведите тип компьютера: ";
    cin >> type;

    cout << "Введите инвентарный номер компьютера: ";
    cin >> inventoryNumber;
    bool validInNum = false;
    while (!validInNum) {
        try {
            if (int(inventoryNumber.length()) != 6 || !all_of(inventoryNumber.begin(), inventoryNumber.end(), isdigit)) {
                throw invalid_argument("Инвентарный номер должен состоять из 6 цифр");
            }
            validInNum = true;
        }
        catch (const invalid_argument& error) {
            cout << "Ошибка: " << error.what() << endl;
            cout << "Введите инвентарный номер снова: ";
            getline(cin >> ws, inventoryNumber);
        }
    }

    cout << "Введите MAC-адрес компьютера: ";
    cin >> macAddress;
    cout << "Введите операционную систему компьютера: ";
    cin >> operatingSystem;
    cout << "Введите дату ввода компьютера в эксплуатацию (ДД-ММ-ГГГГ): ";
    cin >> commissioningDate;
    cout << "Введите дату вывода компьютера из эксплуатации (ДД-ММ-ГГГГ): ";
    cin >> decommissioningDate;

    administration->addComputer(Computer(type, inventoryNumber, macAddress, operatingSystem, commissioningDate, decommissioningDate));
}

void UserInteraction::removeComputer() {
    string inventoryNumber;
    cout << "\nВведите инвентарный номер компьютера для удаления: ";
    cin >> inventoryNumber;

    administration->removeComputer(inventoryNumber);
}

void UserInteraction::updateComputer() {
    string inventoryNumber, type, macAddress, operatingSystem, commissioningDate, decommissioningDate;
    cout << "\nВведите инвентарный номер компьютера для обновления: ";
    cin >> inventoryNumber;

    Computer* computer = administration->findComputer(inventoryNumber);
    bool validNum = false;
    while (!validNum) {
        try {
            if (computer == nullptr) {
                throw invalid_argument("Компьютер с инвентарным номером " + inventoryNumber + " не найден");
            }
            validNum = true;
        }
        catch (const invalid_argument& error) {
            cout << "Ошибка: " << error.what() << endl;
            cout << "Введите инвентарный номер снова: ";
            getline(cin >> ws, inventoryNumber);
            computer = administration->findComputer(inventoryNumber);
        }
    }

    // список доступных свойств для обновления
    vector<string> properties = { "Тип", "MAC-адрес", "Операционная система", "Дата ввода в эксплуатацию", "Дата вывода из эксплуатации" };

    // выбор свойства для обновления
    cout << "\nВыберите свойство, которое хотите обновить:\n";
    for (int i = 0; i < properties.size(); i++) {
        cout << i + 1 << ". " << properties[i] << endl;
    }
    cout << "Введите номер свойства: ";
    int choice;
    cin >> choice;

    if (choice < 1 || choice > properties.size()) {
        cout << "\nНеверный выбор. Выберите свойство из списка" << endl;
        return;
    }

    string propertyToUpdate = properties[choice - 1];
    string newValue;
    cout << "Введите новое значение для свойства " << propertyToUpdate << ": ";
    getline(cin >> ws, newValue);

    // ввод значения выбранного свойства
    if (propertyToUpdate == "Тип") {

        // проверка введенного типа компьютера
        bool validType = false;
        while (!validType) {
            try {
                if (!newValue.empty() && newValue != "стационарный" && newValue != "ноутбук" && newValue != "моноблок") {
                    throw invalid_argument("Неверный тип компьютера. Допустимые значения: стационарный, ноутбук, моноблок");
                }
                validType = true;
            }
            catch (const invalid_argument& error) {
                cout << "Ошибка: " << error.what() << endl;
                cout << "Введите тип компьютера снова: ";
                getline(cin >> ws, newValue);
            }
        }

        computer->type = newValue;
        cout << "Свойство успешно обновлено";
    }
    else if (propertyToUpdate == "MAC-адрес") {
        computer->macAddress = newValue;
        cout << "Свойство успешно обновлено";
    }
    else if (propertyToUpdate == "Операционная система") {
        computer->operatingSystem = newValue;
        cout << "Свойство успешно обновлено";
    }
    else if (propertyToUpdate == "Дата ввода в эксплуатацию") {
        computer->commissioningDate = newValue;
        cout << "Свойство успешно обновлено";
    }
    else if (propertyToUpdate == "Дата вывода из эксплуатации") {
        computer->decommissioningDate = newValue;
        cout << "Свойство успешно обновлено";
    }
}

void UserInteraction::findComputer() {
    string inventoryNumber;
    cout << "\nВведите инвентарный номер компьютера для вывода данных о нем: ";
    cin >> inventoryNumber;

    Computer* computer = administration->findComputer(inventoryNumber);
    if (computer == nullptr) {
        cout << "\nКомпьютер не найден" << endl;
    }
    else {
        cout << left << setw(20) << "Тип" << setw(25) << "Инвентарный номер" << setw(25) << "MAC-адрес" << setw(25) << "Операционная система" << setw(20) << "Дата ввода в эксп." << setw(20) << "Дата вывода из эксп." << endl;
        cout << left <<  setw(20) << computer->type << setw(25) << computer->inventoryNumber << setw(25) << computer->macAddress << setw(25) << computer->operatingSystem << setw(20) << computer->commissioningDate << setw(20) << computer->decommissioningDate << endl;
    }
}

void UserInteraction::printComputers() {
    cout << "\nСписок компьютеров:\n";
    cout << left << setw(20) << "Тип" << setw(25) << "Инвентарный номер" << setw(25) << "MAC-адрес" << setw(25) << "Операционная система" << setw(20) << "Дата ввода в эксп." << setw(20) << "Дата вывода из эксп." << endl;
    int i = 1;
    for (auto& computer : administration->computers) {
        cout << left << setw(4) << i++ << setw(20) << computer.type << setw(25) << computer.inventoryNumber << setw(25) << computer.macAddress << setw(25) << computer.operatingSystem << setw(20) << computer.commissioningDate << setw(20) << computer.decommissioningDate << endl;
    }
}

void UserInteraction::start() {
    int choice;
    do {
        cout << "\n\n1. Экспортировать данные из файла" << endl;
        cout << "2. Добавить компьютер" << endl;
        cout << "3. Обновить компьютер" << endl;
        cout << "4. Удалить компьютер" << endl;
        cout << "5. Найти компьютер" << endl;
        cout << "6. Получить полный список компьютеров" << endl;
        cout << "7. Импортировать данные в файл" << endl;
        cout << "8. Завершить и выйти" << endl;
        cout << "Введите свой выбор: ";

        while (!(cin >> choice)) {
            cout << "Ошибка: ввод должен быть числом" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Сделайте свой выбор снова: ";
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