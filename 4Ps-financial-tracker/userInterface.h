#pragma once //WHEN CREATING A LIBRARY (.h file extension) MAKE SURE TO STATE pragma once TO AVOID THE PROGRAM GO BOOM

#include <iostream>

using namespace std;

class userInterfaceMain 
{
	public:
		void mainInterface();//pointing to the mainInterface function in the mainInterface.cpp
		void familyRegistration();//pointing to the familyRegistration function in the familyRegistration.cpp
		void familySearch();//like mentioned above and so on...

};