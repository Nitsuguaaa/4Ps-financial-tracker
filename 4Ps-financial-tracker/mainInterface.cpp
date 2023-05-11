#include "userInterface.h"

void userInterfaceMain::mainInterface() //may userInterfaceMain:: sya kasi gagamitin nung mainInterface() sa .h file itong function na to
{
	int option;

	cout << "this is the main interface" << endl;
	cout << "choose an option" << endl;
	cin >> option;

	switch(option) {
	case 1:
		userInterfaceMain::familyRegistration();//calling familyRegistration function in userInterface.h
	break;

	case 2:
		userInterfaceMain::familySearch();
	break;
	}
}