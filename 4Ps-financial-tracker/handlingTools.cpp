#include "handlingTools.h"

#define MAX_LINES 1000

//Directory finder - just in case na di gumana pre declared directories
void handlingToolsMain::findDir() {
    char *retptr = _getcwd(NULL, 1024);
    if (retptr == NULL)
    {
    printf("Get current working directory failed.\n");
    if (errno == ERANGE)
      printf("Path exceeds max buffer length.\n");
    else if (errno == ENOMEM)
      printf("Memory cannot be allocated for path.\n");
    }
  
    printf("Current working directory: \n\n%s\n", retptr);
    free(retptr);
}

//File encoder - encodes a string array into a file for non volatile storing
void handlingToolsMain::fEncode(string fileName, string arrToEncode[], int arraySize) {

	ofstream myfile(".\\familyTable\\" + fileName + ".txt");

	if (myfile.is_open())
	{
    for(int count = 0; count < arraySize; count ++){
        myfile << arrToEncode[count] << endl ;
    }
    myfile.close();
  }
  else cout << "Unable to open file";
}

//File decoder - decodes a file storing each given line into an array index 
void handlingToolsMain::fDecode(string fileName, string arrToDecode[]) {

	//test[6] = arrToDecode[6];

	ifstream file;
	string array[MAX_LINES];
	
	file.open(".\\familyTable\\" + fileName + ".txt");

	if (file.fail())
  {
    cout << "File failed to open." << endl;
  }

	int lines = 0;
	while (!file.eof()) {
		getline(file, array[lines]);
		lines++;
	}
	file.close();

	for (int i = 0; i < lines; i++) {
     cout << array[i] << endl;
	 
	}
}
