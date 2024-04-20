#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H

#include "Computer.h"

#include <vector>
#include <fstream>
#include "json.hpp"
#include <C:/Users/Alison/Desktop/json-3.4.0/include/nlohmann/json.hpp>

class Administration
{
public:
	vector<Computer> computers;

	void loadFromFile(string filename);
	void writeToFile(string filename);

	void addComputer(Computer computer);
	void updateComputer(Computer computer);
	void removeComputer(string inventoryNumber);

	Computer* findComputer(string inventoryNumber);
};

#endif