#include <iostream>

#include "ratingCalculator.h"
#include "userInterface.h"

using namespace std;

int main() {
	/*Calling user defined libraries (e.g., ratingCalculator.h)*/

	userInterfaceMain ui; //ui ay yung declaration mo sa file na to para magamit mo ung separate files

	ui.mainInterface();//calling mainInterface function in userInterface.h

	system("PAUSE");

	return 0;
}