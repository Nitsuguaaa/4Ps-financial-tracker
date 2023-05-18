#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <direct.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sstream>
#include <queue>
#include <Windows.h>
#include <vector>
/*
* NOTES:
*	1. When declaring an array to store .dat info, set size to 9, size 8 crash and burns the program :/
*	
*/

using namespace std;

/*
*	BACK END FUNCTION DECLARATIONS
*/
void readFamily(string fileName, string arr[]);//reads the file and stores it in an array outside the function
void readFamilyPurchases(string fileName);
void writeFamily(int choice, string fileName = "NULL", bool rewriteFamily = false);//writes family information and can be changed to write family purchases or edit family information
string randSeed();
bool fileTester(const string& name);
void monlthyRating();
void familyListWrite(string familyID, string familyName, string oldFamilyName = "NULL");

/*
*	FRONT END FUNCTION DECLARATIONS
*/
void mainInterface();
void familyRegistration();
void familySearch(string fileName = "NULL");
void familyPurchases();
void familyRemove();
void familyPurchasesEditor();

/*
*	MAIN FUNCTION
*/
int main() {

	if (mkdir("familyTable") != -1) {
		cout << "==========================================================" << endl;
		cout << "Running first startup commands: " << endl << endl;
		cout << "Creating 'familyTable' directory" << endl;
		cout << "Creating 'familyCollection' file" << endl;
		cout << "==========================================================" << endl;
        ofstream file(".\\familyTable\\familyCollection.dat");
		file.close();
		cout << "first startup complete!" << endl;
		system("PAUSE");
	}

	mainInterface();
	//writeFamily(3, "FAMILY ID", true); //Line for editing family info
	//writeFamily(0); //Line for creating a new family
	//writeFamily(1, "P-1002272");
	//readFamilyPurchases("P-1002272");

	system("pause");
	return 0;
}

void readFamily(string fileName, string arr[]){
			fstream file;
			file.open(".\\familyTable\\" + fileName + ".dat");
			if (file.fail()) {cout << "\t\t\tFamily not found" << endl; system("PAUSE"); mainInterface();}//file not found
			if (file.is_open()){
				int lines = 0;
				while (!file.eof()) {
					getline(file, arr[lines]);
					lines++;
				}
			file.close();
			}
}

void readFamilyPurchases(string fileName){
			fstream file;
			file.open(".\\familyTable\\" + fileName + ".dat");
			if (file.fail()) {cout << "\t\t\tFamily not found" << endl; system("PAUSE"); mainInterface();}//file not found
			if (file.is_open()){
				int lines = 0;
				string currentLine;
				int jump = 10;
				cout << "\t\t\tCurrent Family Purchases (0 = bad purchase, 1 = neutral purchase, 2 = good purchase):" << endl << endl << "\t\t\t[";
				while (!file.eof()) {
					getline(file, currentLine);
					cout << " " << currentLine << " ";
					lines++;
					if(lines >= jump) {
						cout << endl << "\t\t\t";
						jump += 10;
					}
				}
				cout << " ]" << endl;
			file.close();
			}
}

//
//CREATE A LIST ALL FUNCTION
//
void writeFamily(int choice, string fileName, bool rewriteFamily){ //set rewriteFamily to true if admin will edit an existing family
	if(rewriteFamily == false) {

		if(choice == 0) { //the only lines where the access of UID needs to add "I-" + UID is needed
			string currentRead, UID = randSeed(), PUID = "P-" + UID;
			if(fileTester(".\\familyTable\\I-" + UID + ".dat") == true) { //Tests if the UID already exists, generate new UID
				UID = randSeed();
			} else { //Write information and store
				ofstream file(".\\familyTable\\I-" + UID + ".dat");
				if (file.is_open()) {
					string info[4] = {"Name: ", "Age: ", "Address: ", "Number of Offspring: "}, currentFamily[9];
					cout << "\t\t\t Please Enter your info" << endl;
					for(int i = 0; i < 4; i++) { //name //age //etc etc
						cout << "\t\t\t " << info[i];
						getline(cin, currentRead);
						currentFamily[i] = currentRead;
						file << currentRead << endl;
					}
					file << "I-" << UID << endl;
					file << PUID << endl;
					
					stringstream getOffspring;
					int offSpring;
					getOffspring << currentFamily[3];
					getOffspring >> offSpring;
					if(offSpring > 3) {
						offSpring = 1400;
					} else if(offSpring < 0) {
						offSpring = 500;
					} else {
						offSpring *=300;
						offSpring += 500;					
					}

					file << offSpring << endl;
					file << 3.00 << endl;
					file.close();

				//store UID and family name in a collection
				ofstream file(".\\familyTable\\" + PUID + ".dat");
				file.close();
				string familyInfo[9];
				readFamily("I-" + UID, familyInfo);
				familyListWrite("I-" + UID, familyInfo[0]);
				familySearch("I-" + UID);
				}
			}
		} else if(choice == 1) { //option 2 for writing family purchases

			string familyInfo[9];
			readFamily(fileName, familyInfo);

			ofstream file(".\\familyTable\\" + familyInfo[5] + ".dat");
			if (file.fail()) {cout << "\t\t\tFamily not found" << endl; system("PAUSE"); mainInterface();}
			if(file.is_open()){
				cout << "\t\t\tHow many purchases would you like to add?: ";

				string purchaseNumbers, currentRead;
				getline(cin, purchaseNumbers);
				stringstream getPurchaseNumber;
				int numberOfPurchases;
				getPurchaseNumber << purchaseNumbers;
				getPurchaseNumber >> numberOfPurchases;

				cout << "\t\t\tPurchase Types (0 = bad purchase, 1 = neutral purchase, 2 = good purchase)" << endl;
				for(int i = 1; i <= numberOfPurchases; i++) {
					cout << "\t\t\tEnter purchase type ["<<i<<"]: ";
					getline(cin, currentRead);
					file << currentRead << endl;
				}
				file.close();
			}
		} else { cout << "option 3 is on a different bool" << endl;}

	} else { //if rewriteFamily is true
		string familyInfo[9], currentRead;
		readFamily(fileName, familyInfo);
		string oldFamilyName = familyInfo[0];
		ofstream file(".\\familyTable\\" + fileName + ".dat");
			if (file.fail()) {cout << "\t\t\tFamily not found" << endl; system("PAUSE"); mainInterface();}
			if (file.is_open()) {
				string info[4] = {"Name: ", "Age: ", "Address: ", "Number of Offspring: "};
				cout << "\t\t\t Please Enter your info" << endl;
				for(int i = 0; i < 4; i++) {
					cout << "\t\t\t " << info[i];
					getline(cin, currentRead);
					file << currentRead << endl;
				}
				file << familyInfo[4] << endl;
				file << familyInfo[5] << endl;
				file << familyInfo[6] << endl;
				file << familyInfo[7] << endl;
				file.close();
				readFamily(fileName, familyInfo);
				familyListWrite(fileName, familyInfo[0], oldFamilyName);
				familySearch(fileName);

		}
	}

}

string randSeed() {
		time_t current_time = time(NULL);
		srand((unsigned) time(NULL));
		stringstream temp;
		string result;
		int random = 1000000 + (rand() % 1000001);
		temp << random;
		temp >> result;
		return result;
}

bool fileTester(const string& name) { //boolean return if the file exists or not
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0);
}

void familyListWrite(string familyID, string familyName, string oldFamilyName) {
	queue<string> currentFamilyList;
			string currentLine, editedFamily = familyID + "\t-\t" + oldFamilyName;
			fstream file;
			file.open(".\\familyTable\\familyCollection.dat");
			if (file.fail()) {cout << "familyCollection.dat has been deleted" << endl;}
			if (file.is_open()){
				while (!file.eof()) {
					getline(file, currentLine);
					size_t found = currentLine.find(oldFamilyName);
					if(found != string::npos) {
						//Gumagana naman kahit walang nakalagay kaya wag na lang natin guluhin
					} else { 
						currentFamilyList.push(currentLine);
					}
				}
			file.close();
			ofstream file2(".\\familyTable\\familyCollection.dat");
			while(!currentFamilyList.empty()) {
				file2 << currentFamilyList.front() << endl;
				currentFamilyList.pop();
			}
			file2 << familyID << "\t-\t" << familyName;
			file2.close();
			}
}

void monthlyRating() {
    queue<string> familyList;
    string currentRead, familyID;

    ifstream file;
    file.open(".\\familyTable\\familyCollection.dat");
    if (file.is_open()) {
        int lines = 0;
        while (getline(file, currentRead)) {
            string familyID(currentRead);
            familyList.push(familyID.substr(0, 9));
            lines++;
        }

        file.close();
        familyList.pop();

        while (!familyList.empty()) {
            string familyInfo[9], currentFile = familyList.front();
            familyList.pop();
            readFamily(currentFile, familyInfo);

            ifstream file;
            file.open(".\\familyTable\\" + familyInfo[5] + ".dat");

            double sum = 0, num, lineCount = 0;

            if (file.is_open()) {
                string currentLine;
                while (getline(file, currentLine)) {
                    if (currentLine == "0") {
                        lineCount++;
                    }
                    else if (currentLine == "1") {
                        sum += 1;
                        lineCount++;
                    }
                    else if (currentLine == "2") {
                        sum += 2;
                        lineCount++;
                    }
                }
                file.close();
            }

            double ave, converted;

            ave = sum / lineCount;
            converted = (ave * 5) / 2;

			if(lineCount <= 0) {
				converted = 3.00;
			}

            ifstream inputFile(".\\familyTable\\" + familyInfo[4] + ".dat");
            vector<string> fileContents;
            if (inputFile.is_open()) {
                string line;
                while (getline(inputFile, line)) {
                    fileContents.push_back(line);
                }
                inputFile.close();

				stringstream ss;
				int offSpring;
				ss << fileContents[3];
				ss >> offSpring;

				if(offSpring > 3) {
					offSpring = 1400;
				} else if (offSpring <= 0) {
					offSpring = 0;
				} else {
					offSpring *= 300;
					offSpring += 500;
				}

				ostringstream oss;
				oss << fixed << setprecision(2) << converted;
				string result = oss.str();
				ss << result;
				ss >> converted;

				if(converted <= 2.50) { //low
					offSpring -= 400;
				} else if(converted >= 3.5) { //high
					offSpring += 500;	
				}

				stringstream ss2;
				ss2 << offSpring;

				fileContents[6] = ss2.str();

                if (fileContents.size() >= 8) {
                    stringstream ss;
                    ss << converted;
                    fileContents[7] = ss.str();
                }
            }

            ofstream outputFile(".\\familyTable\\" + familyInfo[4] + ".dat");
            if (outputFile.is_open()) {
                for (size_t i = 0; i < fileContents.size(); i++) {
                    outputFile << fileContents[i];
                    if (i != fileContents.size() - 1) {
                        outputFile << endl;
                    }
                }
                outputFile.close();
            }
        }
    }
}







/*
/
/	FRONT END SECTION
/
*/

void mainInterface()
{
	system("cls");
	stringstream convertStr; //do a string to int because !int input will cause a stack overflow
	int option;
	string convertOption;

	cout<<"\t\t\t____________________________________________________________\n\n\n";
	cout<<"\t\t\t           ******** Batangas State University ********       \n";
	cout<<"\t\t\t           ********  4P's Financial Tracker   ********        \n\n\n";
	cout<<"\t\t\t____________________________________________________________\n\n\n";
	cout<<"                                                                     \n\n";
	cout<<"\t\t\t\t| (1) Registration                      |"<<endl;
	cout<<"\t\t\t\t| (2) Search Family                     |"<<endl;
	cout<<"\t\t\t\t| (3) Search Family Purchases History   |"<<endl;
	cout<<"\t\t\t\t| (4) Edit/Remove a Family              |"<<endl;
	cout<<"\t\t\t\t| (5) Monthly Rating                    |"<<endl;
	cout<<"\t\t\t\t| (6) Enter Family Purchases            |"<<endl;
	cout<<"\t\t\t\t| (7) Exit                              |"<<endl;
	cout<<"\n\t\t\t Please select an option : ";
	getline(cin, convertOption);
	cout<<endl;

	convertStr << convertOption;
	convertStr >> option;

	switch(option) {
		case 1:
			familyRegistration();
			break;
		
		case 2:
			familySearch();
			break;
		
		case 3:
			familyPurchases();
			break;
		
		case 4:
			familyRemove();
			break;
		
		case 5:
			monthlyRating();
			break;
		
		case 6:
			familyPurchasesEditor();
			break;
		
		case 7:
			cout<<"\t\t\t Have a Good Day! \n\n";
			system("PAUSE");
			exit(0);
			break;
			
		default:
		cout<<"\t\t\t Invalid Option" << endl;
		system("PAUSE");
		mainInterface();
		break;
	}
}

void familyRegistration()
{
	system("cls");

	cout<<"\t\t\t____________________________________________________________\n\n\n";
	cout<<"\t\t\t           ******** Batangas State University ********       \n";
	cout<<"\t\t\t           ********  4P's Financial Tracker   ********        \n\n\n";
	cout<<"\t\t\t____________________________________________________________\n\n\n";
	cout<<"                                                                     \n\n";	
	cout<<"\t\t\t ************************************************************* \n";
	cout<<"\t\t\t *                       REGISTRATION                        *   \n";
	cout<<"\t\t\t ************************************************************* \n";
	
	writeFamily(0);
}

void familySearch(string fileName)
{
	system("cls");
	cout<<"\t\t\t____________________________________________________________\n\n\n";
	cout<<"\t\t\t           ******** Batangas State University ********       \n";
	cout<<"\t\t\t           ********  4P's Financial Tracker   ********        \n\n\n";
	cout<<"\t\t\t____________________________________________________________\n\n\n";
	cout<<"                                                                     \n";
	cout<<"\t\t\t ************************************************************* \n";
	cout<<"\t\t\t *                    SEARCH FAMILY                          * \n";
	cout<<"\t\t\t ************************************************************* \n\n";
	
	string choice, familyInfo[9];

		if(fileName == "NULL") {
			int option;

			cout <<"\t\t\t1. Search a family" << endl;
			cout <<"\t\t\t2. Show all families" << endl << "\t\t\t";

			stringstream convertStr;
			getline(cin, choice);
			convertStr << choice;
			convertStr >> option;

			if(option == 1) {
				string familyID;
				cout <<"\t\t\tEnter the family ID you want to search: ";
				getline(cin, familyID);
				readFamily(familyID, familyInfo);

    cout<<"\n\n\t\t\t      4P's Financial Tracker - Registered Family Information        \n";
	cout<<"\t\t\t /////////////////////////////////////////////////////////////// \n";
	cout<<"\t\t\t|                                       |                      \n";
	cout<<"\t\t\t| Serial code:------------------------- |\t"<< familyInfo[4] << endl;
	cout<<"\t\t\t| Name of the Beneficiary:------------- |\t"<< familyInfo[0] << endl;
	cout<<"\t\t\t| Age:--------------------------------- |\t"<< familyInfo[1] << endl;
	cout<<"\t\t\t| Address:----------------------------- |\t"<< familyInfo[2] << endl;
	cout<<"\t\t\t| Number of Offsprings:---------------- |\t"<< familyInfo[3] << endl;
	cout<<"\t\t\t| Current Rating:---------------------- |\t"<< familyInfo[7] << endl;
	cout<<"\t\t\t_________________________________________________________________\n\n";
	cout<<"\t\t\t_________________________________________________________________\n\n";
	cout<<"\t\t\t| Current Budget:--------------------- |\t"<< familyInfo[6] <<endl;
	cout<<"\t\t\t_________________________________________________________________\n";

			} else if(option ==2) {
				cout << "\t\t\tListing all registered families with their ID: " << endl;
				ifstream file(".\\familyTable\\familyCollection.dat");

				if(file.is_open()) {					
					string line;
					while(getline(file, line)) {
						cout << "\t\t\t" << line << endl;
					}
				}

				file.close();
			} else {
				cout << "\t\t\tInvalid Option" << endl;
				system("PAUSE");
				mainInterface();		
			}

		} else {
			readFamily(fileName, familyInfo);

    cout<<"\n\n\t\t\t      4P's Financial Tracker - Registered Family Information        \n";
	cout<<"\t\t\t /////////////////////////////////////////////////////////////// \n";
	cout<<"\t\t\t|                                       |                      \n";
	cout<<"\t\t\t| Serial code:------------------------- |\t"<< familyInfo[4] << endl;
	cout<<"\t\t\t| Name of the Beneficiary:------------- |\t"<< familyInfo[0] << endl;
	cout<<"\t\t\t| Age:--------------------------------- |\t"<< familyInfo[1] << endl;
	cout<<"\t\t\t| Address:----------------------------- |\t"<< familyInfo[2] << endl;
	cout<<"\t\t\t| Number of Offsprings:---------------- |\t"<< familyInfo[3] << endl;
	cout<<"\t\t\t| Current Rating:---------------------- |\t"<< familyInfo[7] << endl;
	cout<<"\t\t\t_________________________________________________________________\n\n";
	cout<<"\t\t\t_________________________________________________________________\n\n";
	cout<<"\t\t\t| Current Budget:--------------------- |\t"<< familyInfo[6] <<endl;
	cout<<"\t\t\t_________________________________________________________________\n";
		}

	
	system("PAUSE");
	mainInterface();
}

void familyPurchases()
{
	system("cls");
	cout<<"\t\t\t____________________________________________________________\n\n\n";
	cout<<"\t\t\t           ******** Batangas State University ********       \n";
	cout<<"\t\t\t           ********  4P's Financial Tracker   ********        \n\n\n";
	cout<<"\t\t\t____________________________________________________________\n\n\n";
	cout<<"                                                                     \n\n";
	cout<<"\t\t\t ************************************************************* \n";
	cout<<"\t\t\t *                    FAMILY PURCHASE HISTORY                * \n";
	cout<<"\t\t\t ************************************************************* \n";

	string familyInfo[9], familyID;
	cout <<"\t\t\tEnter the family ID you want to search: ";
	getline(cin, familyID);
	readFamily(familyID, familyInfo);

	cout<<"\t\t\t_________________________________________________________________\n\n";
	cout<<"\t\t\tName of the family beneficiary: "<< familyInfo[0] <<endl;
	cout<<"\t\t\t_________________________________________________________________\n\n";
	readFamilyPurchases(familyInfo[5]);

system("PAUSE");
mainInterface();
}

void familyRemove()
{
	system("cls");
	cout<<"\t\t\t____________________________________________________________\n\n\n";
	cout<<"\t\t\t           ******** Batangas State University ********       \n";
	cout<<"\t\t\t           ********  4P's Financial Tracker   ********        \n\n\n";
	cout<<"\t\t\t____________________________________________________________\n\n\n";
	cout<<"                                                                     \n\n";
	cout<<"\t\t\t ************************************************************* \n";
	cout<<"\t\t\t *                       EDIT/REMOVE FAMILY                  * \n";
	cout<<"\t\t\t ************************************************************* \n";
	
	string familyInfo[9], familyID, choice;
	int option;
	cout <<"\t\t\tEnter the family ID you want to search: ";
	getline(cin, familyID);
	readFamily(familyID, familyInfo);
	cout<<"\t\t\t_________________________________________________________________\n\n";
	cout<<"\t\t\tName of the family beneficiary: "<< familyInfo[0] <<endl;
	cout<<"\t\t\t_________________________________________________________________\n\n";
	cout <<"\t\t\t1. Edit family information" << endl;
	cout <<"\t\t\t2. Delete family" << endl << "\t\t\t";
	
	stringstream convertStr;
	getline(cin, choice);
	convertStr << choice;
	convertStr >> option;

	switch(option) {
		case 1:
			cout<<"\t\t\tDo you want to edit this family's information? (Y/N): ";
			getline(cin, choice);
			if(choice == "Y" || choice == "y") {
				writeFamily(3,familyID, true);
			}
			break;

		case 2:
			cout<<"\t\t\tDo you want to delete this family? (Y/N): ";
			getline(cin, choice);
			if(choice == "Y" || choice == "y") {
				string familyInfo[9], famID = ".\\familyTable\\" + familyID + ".dat" ;
				readFamily(familyID, familyInfo);
				string famPUID = ".\\familyTable\\" + familyInfo[5] + ".dat";

				const int lengthUID = famID.length();
				const int lengthPUID = famPUID.length();

				char* charUID = new char[lengthUID + 1];
				char* charPUID = new char[lengthPUID + 1];

				strcpy(charUID, famID.c_str());
				strcpy(charPUID, famPUID.c_str());

				remove(charUID);
				remove(charPUID);

				cout << "\t\t\tSuccessfully removed family" << endl;
			}
			break;

		default:
			cout << "\t\t\tInvalid Option" << endl;
			system("PAUSE");
			mainInterface();
			break;
		}

system("PAUSE");
mainInterface();
}

void familyPurchasesEditor()
{
	system("cls");
	cout<<"\t\t\t____________________________________________________________\n\n\n";
	cout<<"\t\t\t           ******** Batangas State University ********       \n";
	cout<<"\t\t\t           ********  4P's Financial Tracker   ********        \n\n\n";
	cout<<"\t\t\t____________________________________________________________\n\n\n";
	cout<<"                                                                     \n\n";
	cout<<"\t\t\t ************************************************************* \n";
	cout<<"\t\t\t *                       FAMILY PURCHASE                     * \n";
	cout<<"\t\t\t ************************************************************* \n";

	string familyInfo[9], familyID, choice;
	cout <<"\t\t\tEnter the family ID you want to search: ";
	getline(cin, familyID);
	readFamily(familyID, familyInfo);
	cout<<"\t\t\t_________________________________________________________________\n\n";
	cout<<"\t\t\tName of the family beneficiary: "<< familyInfo[0] <<endl;
	cout<<"\t\t\t_________________________________________________________________\n\n";
	cout<<"\t\t\tDo you want to edit this family's purchase data? (Y/N): ";
	getline(cin, choice);
	if(choice == "Y" || choice == "y") {
		writeFamily(1, familyID);
	}

system("PAUSE");
mainInterface();
}