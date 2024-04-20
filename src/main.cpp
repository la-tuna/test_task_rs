#include <iostream>
#include "UserInteraction.h"

int main() {
    system("chcp 1251");

    Administration* adminitration = new Administration();
    UserInteraction* userInteraction = new UserInteraction(adminitration);

    userInteraction->start();

    delete userInteraction;
    delete adminitration;

    return 0;
}
