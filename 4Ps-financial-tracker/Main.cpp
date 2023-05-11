#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>

#include "ratingCalculator.h"
#include "userInterface.h"
#include "handlingTools.h"

using namespace std;

int main() {
	/*Calling user defined libraries (e.g., ratingCalculator.h)*/
	userInterfaceMain ui; //ui ay yung declaration mo sa file na to para magamit mo ung separate files
	handlingToolsMain htf;

	/*creates a directory to store family information*/
    struct stat sb;
	if (stat("./familyTable/config.yml", &sb) == 0 && !(sb.st_mode & S_IFDIR)) {
	} else {
		mkdir("familyTable");
		ofstream fStart(".\\familyTable\\config.yml");
        fStart << "config version: 0 //do not change";
		fStart.close();
	}


	ui.mainInterface();//calling mainInterface function in userInterface.h

	system("PAUSE");

	return 0;
}