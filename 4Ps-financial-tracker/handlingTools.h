#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <string>

//THIS IS A HEADING FILE TO STORE FUNCTIONS THAT AFFECT INPUT AND OUTPUT OF DATA INTO FILES

using namespace std;

class handlingToolsMain
{
    public:
		//string test[6];
        void findDir();
		void fEncode(string fileName, string arrToEncode[], int arraySize);
		void fDecode(string fileName, string arrToDecode[]);
};