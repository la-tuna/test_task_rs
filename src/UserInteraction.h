#ifndef USERINTERACTION_H
#define USERINTERACTION_H

#include "Administration.h"

class UserInteraction
{
public:
    UserInteraction(Administration* administration);

	void loadFromFile();
	void writeToFile();

	void addComputer();
	void updateComputer();
	void removeComputer();

	void findComputer();
	void printComputers();

	void start();

private:
    Administration* administration;
};

#endif