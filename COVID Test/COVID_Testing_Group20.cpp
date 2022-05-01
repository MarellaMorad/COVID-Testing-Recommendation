#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <iomanip>
#include <ctime> //required for the time used in srand()
#include <sstream> //used in randID()

using namespace std;

//-------------------------------------PROJECT INFORMATION-----------------------------------------------------------------
/*
    Contributing Authors:
    	David Roberts - 102559025
        Marella Morad - 103076428
        Jake Plumb    - 103057407

    Name of the .cpp file:
        COVID_Testing_Group20.cpp
    
    Purpose of the program:
        This program has been designed to predict the need for a COVID test based on patient input
                                            [such as overseas travel, symptoms and visiting high risk locations] 
                                          display COVID symptoms classified by severity, and 
                                          show COVID high-risk locations based on locally stored data.

    Last editied:
        24/05/2021
*/

//-----------------------------------FUNCTION PROTOTYPES-----------------------------------------------------------------

// read file functions
void readPatients(vector<int> &iDs, vector<string> &firstNames,
                  vector<string> &lastNames, vector<string> &birthDates,
                  vector<string> &addresses, vector<string> &locations,
                  vector<string> &visitTimes, vector<string> &overseasTravel,
                  vector<string> &testResults, vector<string> &healthStatus);
void printPatients(vector<int> &iDs, vector<string> &firstNames,
                   vector<string> &lastNames, vector<string> &birthDates,
                   vector<string> &addresses, vector<string> &locations,
                   vector<string> &visitTimes, vector<string> &overseasTravel,
                   vector<string> &testResults, vector<string> &healthStatus);
void readSymptoms(vector<string> &lowRisk, vector<string> &medRisk,
                  vector<string> &highRisk);
void printSymptoms(vector<string> &lowRisk, vector<string> &medRisk,
                   vector<string> &highRisk);
void readLocations(vector<string> &riskyLocations);
void printLocations(vector<string> &riskyLocations);
void updatePatientResults(int i, vector<int> &iDs, vector<string> &firstNames,
                          vector<string> &lastNames, vector<string> &locations,
                          vector<string> &visitTimes, vector<string> &riskyLocations, 
                          vector<string> &testResults);

// edit patients
int whichPatient(vector<int> &iDs, vector<string> &firstNames,
                  vector<string> &lastNames);
int searchPatient(vector<int> &iDs);
void editPatient(int i, vector<string> &firstNames, vector<string> &lastNames,
                 vector<string> &addresses, vector<string> &healthStatus);
				 
// write to file functions
void writePatients(vector<int> &iDs, vector<string> &firstNames,
                   vector<string> &lastNames, vector<string> &birthDates,
                   vector<string> &addresses, vector<string> &locations,
                   vector<string> &visitTimes, vector<string> &overseasTravel,
				   vector<string> &testResults, vector<string> &healthStatus);
void writeLocations(vector<string> &riskyLocations);

// menu functions
void randID(vector<int> &iDs); //to generate a random ID
int options(); //to display the list of options to the user

void enterDetails(vector<int> &iDs, vector<string> &firstNames,
                  vector<string> &lastNames, vector<string> &birthDates,
                  vector<string> &addresses, vector<string> &locations,
                  vector<string> &visitTimes, vector<string> &overseasTravel,
                  vector<string> &lowRisk, vector<string> &medRisk, 
                  vector<string> &highRisk, vector<string> &riskyLocations,
				  vector<string> &testResults, vector<string> &healthStatus); // Option 1
void posPatients(vector<int> &iDs, vector<string> &firstNames,
                 vector<string> &lastNames, vector<string> &birthDates,
                 vector<string> &addresses, vector<string> &locations,
                 vector<string> &visitTimes, vector<string> &overseasTravel,
                 vector<string> &testResults, vector<string> &healthStatus); //Option 6
					 
// other
void clear();
int getChoice(int low, int high);
bool checkNumber(string line);
void pressEnter();
string existanceCheck(string input);

//------------------------------------MAIN FUNCTION-------------------------------------------------------------------

int main()
{
    clear(); // clear the terminal

    // create vectors to hold patient details
    vector<int> iDs;
    vector<string> firstNames;
    vector<string> lastNames;
    vector<string> birthDates;
    vector<string> addresses;
    vector<string> locations;
    vector<string> visitTimes;
    vector<string> overseasTravel;
    vector<string> testResults;
    vector<string> healthStatus;

    // create vectors to hold covid symptoms
    vector<string> lowRisk;
    vector<string> medRisk;
    vector<string> highRisk;

    // create vector to hold risky locations
    vector<string> riskyLocations;

    //READ STUFF IN
    // read in patient details
    readPatients(iDs, firstNames, lastNames, birthDates,
                 addresses, locations, visitTimes, overseasTravel,
                 testResults, healthStatus);
    // read in covid symptoms
    readSymptoms(lowRisk, medRisk, highRisk);
    // read in high risk locations
    readLocations(riskyLocations);
	
	//Options menu
    int choice = 0;
    bool exit = false;
    int select = -1; //selection of patient to edit
    while (!exit) 
    {
        cout << "Hello and Welcome to our program:\n"
			 << "Please choose one of the options to get you started:\n"
			 << "1- Enter details for COVID-Test Recommendation\n"
             << "2- Submit Your Covid test status & Update the Location database\n"
             << "3- Display the Updated Location (High Risk for COVID)\n"
             << "4- Update COVID Patient Details\n"
             << "5- Display the COVID Positive Patient Detail\n"
             << "6- Quit\n"
			 << "Make your selection: ";

        // get menu choice
        choice = getChoice(1, 6);

        switch (choice) 
		{
            case 1 :
                // enter new patient details
                clear();    //clear terminal
                enterDetails(iDs, firstNames, lastNames, birthDates,
							 addresses, locations, visitTimes, overseasTravel,
                             lowRisk, medRisk, highRisk, riskyLocations, testResults, healthStatus);
                clear();
                break;
            case 2 :
				// submit COVID-test status and Update the location database
                clear();
                select = searchPatient(iDs);
                updatePatientResults(select, iDs, firstNames, lastNames, locations, visitTimes, riskyLocations, testResults);
                break;
            case 3 :
                // display the Updated Location (High Risk for COVID)
                printLocations(riskyLocations);
                break;
            case 4 :
                // update COVID Patient Details
                select = whichPatient(iDs, firstNames, lastNames);
                editPatient(select, firstNames, lastNames, addresses, healthStatus);
                break;
            case 5 :
                // display the COVID Positive Patient Detail
                clear();
                posPatients(iDs, firstNames, lastNames, birthDates,
                            addresses, locations, visitTimes, overseasTravel,
                            testResults, healthStatus);
				break;
            case 6 :
                // quit
                cout << "GoodBye\n";
                // write vector information to file before terminating
                writePatients(iDs, firstNames, lastNames, birthDates,
							  addresses, locations, visitTimes, 
							  overseasTravel, testResults, healthStatus);
                writeLocations(riskyLocations);
                exit = true;
                break;
            default :
                exit = false;
		}
    }
	
    return 0;
}

//---------------------------------GENERAL FUNCTIONS----------------------------------------------------------------

//clear the terminal (by printing 100 new lines)
void clear()
{
    for (int i = 0; i < 20; i++)
        cout << "\n\n\n\n\n";
}

string existanceCheck(string input)
{
    bool done = false;
    while(!done)
    {
        if(input.empty())
        {
            cout<<"Nothing enterd, please try again: ";
            getline(cin, input);
        }
        else
        {
            done = true;
        }
    }

    return input;
}

// get an integer selection from user. if not integer, prompt for another input
// also check if selection is within a range (limits inclusive)
int getChoice(int low, int high) 
{
    string line;
    int choice = 0;
    bool done = false;
    
    while (!done) {
        getline(cin, line);
        if (checkNumber(line)) {
            choice = stoi(line);
            if (choice >= low && choice <= high) {
                done = true;
            } else {
                cout << "\nInvalid choice/input, please try again: ";
            }
        } else {
            cout << "\nInvalid choice/input, please try again: ";
        }
    }
    
    return choice;
}

// return true if string is only integers
bool checkNumber(string line) 
{
   for (int i = 0; i < line.length(); i++)
   {
    if (isdigit(line[i]) == false) 
	{
        return false;
    } 
	else 
	{
        return true;
    }
   }
   return false;
}

// prompts user to press enter to continue
void pressEnter()
{
    string line;
    cout << "Press Enter to Continue: ";
    getline(cin, line);
}

//---------------------------------- NEW PATIENTS -------------------------------------------------------------------

int ID; //global - used in randID and in enterDetails

// Generating Random IDs for Patients
void randID(vector<int> &iDs)
{	
	//initialise the seed for the random number generator function\
	// when the program is rerun, the seed will change and so the random id will change
	srand((unsigned int)time(NULL));
	int arrID[6];	
	
	cout<<"\nThe Patient ID is: ";
	for (int i = 0; i <= 5; i++) //looping 6 times to generate a 6 digit random ID
	{
		arrID[i] = rand() % 9 + 1;
		cout<<arrID[i];
	}
	cout<<endl;
	cout<<"\tMake sure you have a record of your ID!\n\n";
	
	// convert the array into a single integer number to save it in the patient's records
	stringstream ss;
	for (int i : arrID)
	{
		ss << i;
	}
    ss >> ID;

    //checking for duplicate iDs
    for(int i = 0; i<iDs.size(); i++)
    {
        if(ID == iDs[i])
        {
            randID(iDs); //recursive call
        }
        else
        {
            continue;
        }
    }
}

bool emptySymptoms = false;

void enterDetails(vector<int> &iDs, vector<string> &firstNames,
                  vector<string> &lastNames, vector<string> &birthDates,
                  vector<string> &addresses, vector<string> &locations,
                  vector<string> &visitTimes, vector<string> &overseasTravel,
                  vector<string> &lowRisk, vector<string> &medRisk, 
                  vector<string> &highRisk, vector<string> &riskyLocations,
				  vector<string> &testResults, vector<string> &healthStatus)
{
	string input;
    int day, month, year;
	int select = 0;
	//Ask patient for details and save them in the corresponding vectors
	
	//ID
	randID(iDs);
    iDs.push_back(ID);
	//First name
	cout<<"Enter Patient's First Name: ";
	getline(cin, input);
    firstNames.push_back(existanceCheck(input));
	//Last name
	cout<<"Enter Patient's Last Name: ";
	getline(cin, input);
    lastNames.push_back(existanceCheck(input));
	//Date of birth
	cout<<"Enter Patient's Date of Birth:  ";
    cout<<"\n\tDay: ";
	day = getChoice(1, 31);
    if (day >= 1 && day <= 9)
    {
        input = '0' + to_string(day);
    }
    else
    {
        input = to_string(day);
    }
    cout<<"\tMonth: ";
	month = getChoice(1, 12);
    if (month >= 1 && month <= 9)
    {
        input = input + "/0" + to_string(month) + "/";
    }
    else
    {
        input = input + "/"+ to_string(month) + "/";
    }
    cout<<"\tYear: ";
    year = getChoice(1500, 2021);
    input = input + to_string(year);
	birthDates.push_back(input);
	//Address
	cout<<"Enter Patient's address: ";
	getline(cin, input); //input might have spaces
	addresses.push_back(existanceCheck(input));
	//Overseas travel
    bool overseasTravelAns = false;
	cout<<"Has the patient travelled overseas in the last 6 months? \n"
		<<"1. Yes\t\t2. No\n"
		<<"Make your selection: ";
	// get user selection
	select = getChoice(1, 2);
	// saving either yes or no depending on the user choice
	switch (select) 
	{
		case 1: //Yes
		{
			overseasTravel.push_back("Yes");
            overseasTravelAns = true;
			break;
		}
		case 2: //No
		{
			overseasTravel.push_back("No");
            overseasTravelAns = false;
			break;
		}
	}

    // print covid symptoms
    // to decide if the patient needs a test
    bool H_Symptoms = false;
    bool M_Symptoms = false;
    bool L_Symptoms = false;
    bool N_Symptoms = false;
    if(emptySymptoms == false)
    {
        printSymptoms(lowRisk, medRisk, highRisk);

        // selecting symptoms
        cout<<"\nPlease select if you have High, Medium or Low risk symptoms from the above list:"<<endl;

        cout<<"\n"
            <<"1. High\t\t2. Medium\t\t3. Low\t\t4. None\n"
            <<"Make your selection: ";

        select = getChoice(1, 4);
        switch(select)
        {
            case 1: //High
            {
                H_Symptoms = true;
                break;
            }
            case 2: //Medium
            {
                M_Symptoms = true;
                break;
            }
            case 3: //Low
            {
                L_Symptoms = true;
                break;
            }
            case 4: //None
            {
                N_Symptoms = true;
                break;
            }
            default:
            {
                cout<<"invalid choice, please choose again: "<<endl;
            }
        }
    }
    else
    {
        cout<<"\nUnable to recommend COVID Test - required data missing!"<<endl;
        N_Symptoms = true;
        pressEnter();
    }
	
	clear();    //clear terminal
	cout<<"\n-------High Risk Locations-------\n";
	// print risky locations
	int i = 0;
	while(i < riskyLocations.size())
	{
		cout << (i+1) <<".\t"<<riskyLocations[i]<<endl;
		i++;
	}
	
	// selecting high risk locations
	cout<<"\n"
		<<"Have you visited a high-risk location from the list above?\n"
		<<"1. Yes\t\t2. No\n"
		<<"Make your selection: ";
	// get user selection
	select = getChoice(1, 2);
    // saving either yes or no depending on the user choice
	int location_num = 0; //to save which location they have visited
	int high = riskyLocations.size(); //to save how big the vector is (how many risky locations)
	bool visitHighRisk = false; //for test recommendation
    if(select == 1)
    {
        //saving the visited risky location
        cout<<"Enter the number that corresponds to the location you have visited: ";
        location_num = getChoice(1, high) - 1;
        locations.push_back(riskyLocations[location_num]); 

        //asking for the time visited and saving it to its vector
        cout<<"\nWhat time approximatly did you visit this location (24hr format)? ";
        getline(cin, input);
        visitTimes.push_back(existanceCheck(input));
        
        //changing visitHighRisk to true to use it in test recommendations
        visitHighRisk = true;
    }
    else if(select == 2)
    {
        locations.push_back("N/A");
        visitTimes.push_back("N/A");
        visitHighRisk = false;
    }
		
	// test recommendation
    //Patient has not visited a high risk location
	if(visitHighRisk == false) //having no symptoms
	{
        //patient has travelled overseas
        if(overseasTravelAns == true)
        {
            if(H_Symptoms == true)
            {
                cout<<"\nYou are Recommended to take the COVID-Test, then to Quarantine!\n\n";
                testResults.push_back("Pending");
            }
            else if(M_Symptoms == true)
            {
                cout<<"\nYou are Recommended to Quarantine\n\n";
                testResults.push_back("Quarantine");
            }
            else if(L_Symptoms == true)
            {
                cout<<"\nYou are Recommended to Quarantine\n\n";
                testResults.push_back("Quarantine");
            }
            else if(N_Symptoms == true)
            {
                cout<<"\nYou are Recommended to Quarantine\n\n";
                testResults.push_back("Quarantine");
            }
        }
        else if(overseasTravelAns == false)
        {
            if(N_Symptoms == true)
            {
                cout<<"\nYou are NOT Recommended to take the test!\n\n";
                testResults.push_back("No Test Needed");
            }
            else if(L_Symptoms == true) //having low symptoms
            {
                cout<<"\nIsolate yourself at home, no need for the test!\n\n";
                testResults.push_back("No Test Needed");
            }
            else if(M_Symptoms == true) //having medium symptoms
            {
                cout<<"\nIsolate yourself at home, no need for the test!\n\n";
                testResults.push_back("No Test Needed");
            }
            else if(H_Symptoms == true) // having high symptoms
            {
                cout<<"\nYou are Recommended to take the COVID-Test!\n\n";
                testResults.push_back("Pending");
            }
        }
    }

    //Patient has visited a high risk location
    else if(visitHighRisk == true)
    {
        //patient has travelled overseas
        if(overseasTravelAns == true)
        {
            if(H_Symptoms == true)
            {
                cout<<"\nYou are Highly Recommended to take the COVID-Test, then to Quarantine!\n\n";
                testResults.push_back("Pending");
            }
            else if(M_Symptoms == true)
            {
                cout<<"\nYou are Recommended to take the COVID-Test, then to Quarantine!\n\n";
                testResults.push_back("Pending");
            }
            else if(L_Symptoms == true)
            {
                cout<<"\nYou are Recommended to take the COVID-Test, then to Quarantine!\n\n";
                testResults.push_back("Pending");
            }
            else if(N_Symptoms == true)
            {
                cout<<"\nYou are Recommended to Quarantine\n\n";
                testResults.push_back("Quarantine");
            }
        }
        else if(overseasTravelAns == false)
        {
            if(N_Symptoms == true)
            {
                cout<<"\nIsolate yourself at home, no need for the test!\n\n";
                testResults.push_back("No Test Needed");
            }
            else if(L_Symptoms == true) //having low symptoms
            {
                cout<<"\nYou are Recommended to take the COVID-Test!\n\n";
                testResults.push_back("Pending");
            }
            else if(M_Symptoms == true) //having medium symptoms
            {
                cout<<"\nYou are Recommended to take the COVID-Test!\n\n";
                testResults.push_back("Pending");
            }
            else if(H_Symptoms == true) // having high symptoms
            {
                cout<<"\nYou are Highly Recommended to take the COVID-Test!\n\n";
                testResults.push_back("Pending");
            }
        }
    }

	healthStatus.push_back("Alive");
    pressEnter();
}

//---------------------------------- PATIENTS -------------------------------------------------------------------

// read in the patient info from a file and store it in a set of vectors
void readPatients(vector<int> &iDs, vector<string> &firstNames,
                  vector<string> &lastNames, vector<string> &birthDates,
                  vector<string> &addresses, vector<string> &locations,
                  vector<string> &visitTimes, vector<string> &overseasTravel,
                  vector<string> &testResults, vector<string> &healthStatus)
{
    // open file for reading
    fstream patients;
    patients.open("patients.txt", ios::in);

    // check if file opened successfully
    if (!patients.is_open()) {
        cout << "error opening patients file\n";
        return;
    }

    // loop through file and read data into vectors
    string line;
    while (!patients.eof()) {
        // read ID
        std::getline(patients, line);
        //check if input is null. break loop if true
        if (line.empty()) { 
            cout << "\npatient ID is Empty\n";
            break;
        }
        iDs.push_back(stoi(line));
        // read First name
        std::getline(patients, line);
        firstNames.push_back(line);
        // read Last name
        std::getline(patients, line);
        lastNames.push_back(line);
        // read birth date
        std::getline(patients, line);
        if (line.empty()) { 
            cout << "patient " << firstNames.back() << " "
            << lastNames.back() << "'s Birth Date is Empty\n";
            line = "0"; // if brithdate is NULL, set it to zero
        }
        birthDates.push_back(line);
        // read address
        std::getline(patients, line);
        addresses.push_back(line);
        // read location
        std::getline(patients, line);
        locations.push_back(line);
        // read location visit time
        std::getline(patients, line);
        visitTimes.push_back(line);
        // read whether patient has traveled overseas
        std::getline(patients, line);
        overseasTravel.push_back(line);
        // read test result
        std::getline(patients, line);
        testResults.push_back(line);
        // read health status
        std::getline(patients, line);
        healthStatus.push_back(line);
        // read the null line and do nothing with it
        std::getline(patients, line);
    }

    patients.close();
}

// print out all patient details
void printPatients(vector<int> &iDs, vector<string> &firstNames,
                   vector<string> &lastNames, vector<string> &birthDates,
                   vector<string> &addresses, vector<string> &locations,
                   vector<string> &visitTimes, vector<string> &overseasTravel,
                   vector<string> &testResults, vector<string> &healthStatus)
{
    clear();    //clear terminal

    int i = 0;
    while (i < iDs.size())
    {
        cout << iDs[i] << endl;
        cout << firstNames[i] << endl;
        cout << lastNames[i] << endl;
        cout << birthDates[i] << endl;
        cout << addresses[i] << endl;
        cout << locations[i] << endl;
        cout << visitTimes[i] << endl;
        cout << overseasTravel[i] << endl;
        cout << testResults[i] << endl;
        cout << healthStatus[i] << "\n\n";

        i++;
    }
}

//--------------------------------- POSITIVE PATIENTS -----------------------------------------------------------------------
//read patients with posisitve test result and display them
void posPatients(vector<int> &iDs, vector<string> &firstNames,
				 vector<string> &lastNames, vector<string> &birthDates,
                 vector<string> &addresses, vector<string> &locations,
                 vector<string> &visitTimes, vector<string> &overseasTravel,
                 vector<string> &testResults, vector<string> &healthStatus)
{

	cout<<"\n-------Positive Patients List-------\n";
	for(int i = 0; i < iDs.size(); i++)
	{
        if(testResults[i] == "Positive")
        {
            cout << "Patient - " << firstNames[i] << " " << lastNames[i] << ":"<<endl;
            cout << "\tID: " <<iDs[i] << endl;
            //calculate patient's age:
            //equation:
            //   age = current year - patient's year of birth
            string DOB;
            DOB = birthDates[i];
            string yearStr;
            yearStr.assign(DOB,6,4);
            int year;
            year = stoi(yearStr);
            int age;
            age = 2021 - year;
            cout << "\tAge: " << age <<endl;
            cout << "\tAddress: " << addresses[i] << endl;
            cout << "\tVisited Location: " << locations[i] << endl;
            cout << "\tVisit Time: " << visitTimes[i] << endl;
            cout << "\tOverseas Travel: " << overseasTravel[i] << endl;
            cout << "\tTest Result: " << testResults[i] << endl;
            cout << "\tHealth Status: " << healthStatus[i] << "\n\n";
        }		
        else
        {
            cout<<"No Positive Pateints in the database!\n";
        }
	}
    pressEnter();
    clear();
}


//--------------------------------- SYMPTOMS -----------------------------------------------------------------------

// read in Covid symptoms from a file and store them 
// in an array of their respective severity
void readSymptoms(vector<string> &lowRisk, vector<string> &medRisk,
                  vector<string> &highRisk)
{
    // open file for reading
    fstream symptoms;
    symptoms.open("symptoms.txt", ios::in);

    // check if file opened successfully
    if (!symptoms.is_open()) {
        cout << "error opening symptoms file\n";
        return;
    }

    // read in the low risk symptoms
    string line;
    std::getline(symptoms, line);
    do {
        if (symptoms.eof()) //fail safe
        {
            //indicate that the symptoms file is empty
            emptySymptoms = true;
            break;
        }
        lowRisk.push_back(line);
        std::getline(symptoms, line);
    } while (line != ".");

    // read in the medium risk symptoms
    std::getline(symptoms, line);
    do {
        if (symptoms.eof()) //fail safe
        {
            emptySymptoms = true;
            break;
        }
        medRisk.push_back(line);
        std::getline(symptoms, line);
    } while (line != ".");
    
    // read in the high risk symptoms
    std::getline(symptoms, line);
    do {
        if (symptoms.eof()) //fail safe
        {
            emptySymptoms = true;
            break;
        }
        highRisk.push_back(line);
        std::getline(symptoms, line);
    } while (line != ".");

    symptoms.close();
}

// print out all symptoms
void printSymptoms(vector<string> &lowRisk, vector<string> &medRisk,
                  vector<string> &highRisk)
{
    clear();    //clear terminal

    // print low risk symptoms
    cout << "\n-------Low Risk Symptoms-------" << endl;
    int i = 0;
    while (i < lowRisk.size())
    {
        cout << lowRisk[i] << endl;
        i++;
    }

    // print low risk symptoms
    cout << "\n-------Medium Risk Symptoms-------" << endl;
    i = 0;
    while (i < medRisk.size())
    {
        cout << medRisk[i] << endl;
        i++;
    }

    // print low risk symptoms
    cout << "\n-------High Risk Symptoms-------" << endl;
    i = 0;
    while (i < highRisk.size())
    {
        cout << highRisk[i] << endl;
        i++;
    }
}
//--------------------------------- UPDATE PATIENT RESULTS ----------------------------------------------------------
//Update Patient results
void updatePatientResults(int i, vector<int> &iDs, vector<string> &firstNames,
                          vector<string> &lastNames, vector<string> &locations,
                          vector<string> &visitTimes, vector<string> &riskyLocations, 
                          vector<string> &testResults)
{
    bool done = false;
    int result = 0;
    char Loc[30];
    string input;
    string time;
    while (!done) {
        cout << "Please enter your COVID-19 test results "<<firstNames[i]<<": "<< endl;
        cout << "1. Positive"<<endl<< "2. Negative"<<endl<< "Make your selection: ";
        // get user results
        result = getChoice(1, 2);
        bool exist = false;
        // action for selection
        switch (result) {
            case 1: 
            {
                testResults[i] = "Positive";// updates test results
                cout<<"\nPlease enter the most recent public place you visited: ";
                cin.getline(Loc, 30);//Recieve location
                input = existanceCheck(Loc);
                for(int i = 0; i < riskyLocations.size(); i++)
                {
                    if(input == riskyLocations[i])
                    {
                        exist = true;
                    }
                }

                if(exist == false)
                {
                    riskyLocations.push_back(input);//Adds location to the  riskyLocations vector
                }
                
                locations[i] = input;

                cout<<"\nWhat time approximatly did you visit this location (24hr format)? ";
                getline(cin, time);
                visitTimes[i] = existanceCheck(time);
                
            } break;
            case 2:
            {
                testResults[i] = "Negative";// updates test results
                cout<<"Your test result is Negative, please remain COVID Safe."<<endl;
            } 
            break;
        }
        done = true;//ends function
    }
    pressEnter();
    clear();
}

//--------------------------------- LOCATIONS -----------------------------------------------------------------------
// read in highrisk locations from a file
void readLocations(vector<string> &riskyLocations)
{
    // open file for reading
    fstream locations;
    locations.open("riskyLocations.txt", ios::in);

    // check if file opened successfully
    if (!locations.is_open()) {
        cout << "error opening locations file\n";
        return;
    }

    // read in locations from a file
    string line;
    while (!locations.eof()) {
        std::getline(locations, line);
        riskyLocations.push_back(line);
    }

    locations.close();
}

// print high risk locations to terminal
void printLocations(vector<string> &riskyLocations)
{
    clear();    //clear terminal

    // print low risk symptoms
    cout << "\n-------High Risk Locations-------" << endl;
    int i = 0;
    while (i < riskyLocations.size())
    {
        cout << riskyLocations[i] << endl;
        i++;
    }
    cout << endl;
    pressEnter();
    clear();
}

//--------------------------------- EDIT PATIENT ARRAYS----------------------------------------------------------------

//search for patients 
int searchPatient(vector<int> &iDs)
{
    int id;
    bool exist = false;
    while (!exist)
    {
        cout<<"Enter Patient ID: ";
        id = getChoice(99999,999999);
        for (int i = 0; i < iDs.size(); i++)
        {
            if(id == iDs[i])
            {
                exist = true;
                return i;
            }
        }

        if(exist == false)
        {
            cout<<"ID not found! please try again..."<<endl;
        }
    }
    return 0;   //default
}

// ask which patient should be edited. Return an integer which is the index of the selected patient
int whichPatient(vector<int> &iDs, vector<string> &firstNames,
                  vector<string> &lastNames)
{
    clear();    //clear terminal
    const int WIDTH = 15;   // width for output formatting

    // print out patients to choose from
    cout << "Which patient would you like to edit?\n\n";
    int i = 0;
    while(i < iDs.size()) {

        cout << (i + 1) << ".\tName:  "
             << left << setw(WIDTH) << firstNames[i]
             << left << setw(WIDTH) << lastNames[i]
             << right << setw(WIDTH / 2) << "ID: "
             << right << setw(WIDTH / 2) << iDs[i] << endl;

        i++;
    }
    cout << "Make your selection: ";

    // take users choice (an integer)
    int choice = 0;
    int high = i;   // upper limit of choice
    choice = getChoice(1, high);
    choice -= 1;    // covert to array index
    return choice;
} 

// cycle through arrays to edit patient details
void editPatient(int i, vector<string> &firstNames, vector<string> &lastNames,
                 vector<string> &addresses, vector<string> &healthStatus)
{
    const int WIDTH = 20;   // width for output formatting

    // loop through arrays, asking which fields should be edited
    bool done = false;
    string line;
    int select = 0;
    while (!done) {
        clear();
        cout << "Which field would you like to edit of patient: "
             << firstNames[i] << " " << lastNames[i] << endl;
        cout << "1. Health Status\n"
             << "2. Address\n"
             << "3. First Name\n"
             << "4. Last Name\n"
             << "Make your selection: ";
        // get user selection
        select = getChoice(1, 4);
        // respective action for selection
        switch (select) {
            case 1:     // edit health status array
                cout << "\n\nWhat is the Status of the patient?\n"
                     << left << setw(WIDTH) << "1. Alive" 
                     << "2. Dead\n"
                     << "Make your selection: ";
                
                select = getChoice(1, 2);
                if (select == 2) {
                    healthStatus[i] = "Dead";
                } else {
                    healthStatus[i] = "Alive";
                }
                break;
            case 2:     // edit address array
            {
                cout << "\n\nWhat is the new address of the patient?\n"
                     << "Please Enter: ";
                getline(cin, line);
                // make sure there is an input
                if (line.empty()) { 
                    addresses[i] = "Empty";
                } else {
                    addresses[i] = line;
                }

                cout << "\nThe address of "
                     << firstNames[i] << " " << lastNames[i] 
                     << " has been updated to " << addresses[i] << endl;
            }   break;
            case 3 :    // edit first name
            {
                cout << "\n\nWhat is the new First Name of the patient?\n"
                     << "Please Enter: ";
                getline(cin, line);
                
                // make sure there is an input
                if (line.empty()) { 
                    firstNames[i] = "Empty";
                } else {
                    firstNames[i] = line;
                }

                cout << "\nThe Patient's name is now "
                     << firstNames[i] << " " << lastNames[i] << endl;
            }   break;
            case 4 :    // edit last name
            {
                cout << "\n\nWhat is the new Last Name of the patient?\n"
                     << "Please Enter: ";
                getline(cin, line);

                // make sure there is an input
                if (line.empty()) { 
                    lastNames[i] = "Empty";
                } else {
                    lastNames[i] = line;
                }

                cout << "\nThe Patient's name is now "
                     << firstNames[i] << " " << lastNames[i] << endl;
            }   break;
        }

        // check if user would like to continue editing
        cout << "\n\nWould you like to edit another field of this patient?\n"
             << left << setw(WIDTH) << "1. Yes"
             << "2. No\n"
             << "Make your selection: ";

        select = getChoice(1, 2);
        if (select == 2)
		{
            done = true;
		}
    }
    clear();
}

//---------------------------------WRITE TO FILE----------------------------------------------------------------

// write the patient details stored in arrays to a file
void writePatients(vector<int> &iDs, vector<string> &firstNames,
                   vector<string> &lastNames, vector<string> &birthDates,
                   vector<string> &addresses, vector<string> &locations,
                   vector<string> &visitTimes, vector<string> &overseasTravel,
				   vector<string> &testResults, vector<string> &healthStatus)
{
    //open file for writing
    fstream patients;
    patients.open("patients.txt", ios::out);

    // check if file opened successfully
    if (!patients.is_open()) {
        cout << "error opening patients file\n";
        return;
    }

    // write patient details to file
    int i = 0;
    while (i < iDs.size()) {
        patients << iDs[i] << endl
                 << firstNames[i] << endl
                 << lastNames[i] << endl
                 << birthDates[i] << endl
                 << addresses[i] << endl
                 << locations[i] << endl
                 << visitTimes[i] << endl
                 << overseasTravel[i] << endl
                 << testResults[i] << endl
                 << healthStatus[i] << endl;
        // blank line between patients for file readability, except last line
        if (i < iDs.size() - 1)
            patients << endl; 

        i++;
    }
    
    // close file
    patients.close();
}

// write the locations stored in riskyLocations to a file
void writeLocations(vector<string> &riskyLocations)
{
    // open file for writing
    fstream locations;
    locations.open("riskyLocations.txt", ios::out);

    // check if file opened successfully
    if (!locations.is_open()) {
        cout << "error opening locations file\n";
        return;
    }

    // write locations to file
    int i = 0;
    while (i < riskyLocations.size()) {
        locations << riskyLocations[i];
        //ensure file doesn't add a blank line at the end every time it writes
        if (i < riskyLocations.size() - 1)
            locations << endl;
        i++;
    }

    // close file
    locations.close();
}

//----------------------------------------VARIABLES----------------------------------------------------------------------
/*
    Variable Name       |	Type            |	Purpose                                                                         | Input/Output  |	Scope   |	Associated Functions
    -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    iDs                 |	vector<int>     |	stores patients iDs                                                             |	I/O         |	local   |	main, readPatients, printPatients, updatePatientResults, whichPatient, writePatients, enterDetails, posPatients
    firstNames          |	vector<string>  |	stores patients first names                                                     |	I/O         |	local   |	main, readPatients, printPatients, updatePatientResults, whichPatient, editPatient, writePatients, enterDetails, posPatients
    lastNames           |	vector<string>  |	stores patients last names                                                      |	I/O         |	local   |	main, readPatients, printPatients, updatePatientResults, whichPatient, editPatient, writePatients, enterDetails, posPatients
    birthDates          |	vector<string>  |	stores patients birth dates                                                     |	I/O         |	local   |	main, readPatients, printPatients, updatePatientResults, writePatients, enterDetails, posPatients
    addresses           |	vector<string>  |	stores patients addresses                                                       |	I/O         |	local   |	main, readPatients, printPatients, writePatients, enterDetails, posPatients
    locations           |	vector<string>  |	stores patients locations                                                       |	I/O         |	local   |	main, readPatients, printPatients, writePatients, enterDetails, posPatients
    visitTimes          |	vector<string>  |	stores patients visit times (of a risky location)                               |	I/O         |	local   |	main, readPatients, printPatients, writePatients, enterDetails, posPatients
    overseasTravel      |	vector<string>  |	stores patients overseas travel status                                          |	I/O         |	local   |	main, readPatients, printPatients, writePatients, enterDetails, posPatients
    testResults         |   vector<string>  |	stores patients test results                                                    |	I/O         |	local   |	main, readPatients, printPatients, editPatient, writePatients, enterDetails, posPatients
    healthStatus        |	vector<string>  |	stores patients health status                                                   |	I/O         |	local   |	main, readPatients, printPatients, editPatient, writePatients, enterDetails, posPatients
    lowRisk             |   vector<string>  |	stores low risk symptoms                                                        |	I/O         |	local   |	main, readSymptoms, printSymptoms, enterDetails
    medRisk             |	vector<string>  |	stores medium risk symptoms                                                     |	I/O         |	local   |	main, readSymptoms, printSymptoms, enterDetails
    highRisk            |	vector<string>  |	stores high risk symptoms                                                       |	I/O         |	local   |	main, readSymptoms, printSymptoms, enterDetails
    riskyLocations      |	vector<string>  |	stores risky locations                                                          |	I/O         |	local   |	main, readLocations, printLocations, writeLocations, enterDetails, updatePatientResults
    choice              |	int             |	to store the patient's choice from the menu                                     | 	I           |	local   |	main, getChoice, whichPatient          
    exit                |	bool            |	to store true when the patient enters valid input                               |	O           |	local   |	main
    select              |	int             |	to select the number of the patient to edit                                     | 	I           |	local   |	main, updatePatientResults, editPatient (by pass)
    i                   |	int             |	to count cycles of for/while loops                                              | 	I           |	local   |	clear, checkNumber, randID, enterDetails, printPatients, posPatients, printSymptoms, printLocations, whichPatient, writePatients, writeLocations
    line                |	string          |	to validate user's input for integer input exclusive functions                  | 	I           |	local   |	getChoice
    done                |	bool            |	to store true when the patient enters valid input                               | 	O           |	local   |	getChoice, updatePatientResults, editPatient           
    ID                  |	int             |	to store the randomly generated ID                                              |	I           |	global  |	randID, enterDetails
    arrID               |	int array       |	stores individually generated random integers for the random ID                 | 	I           |	local   |	randID
    ss                  |	stringstream    |	to stream the individual values stored in arrID into the integer variable ID    | 	O           |	local   |	randID
    input               |	string          |	stores the patient's input in the enterDetails function                         | 	I           |	local   |	enterDetails
    day                 |	int             |	stores the patient's day of birth (after being converted from string to int)    |	I           |	local   |	enterDetails
    month               |	int             |	stores the patient's month of birth (after being converted from string to int)  |	I           |	local   |	enterDetails
    year                |	int             |	stores the patient's year of birth (after being converted from string to int)   |	I           |	local   |	enterDetails
    select	            |   int             |	to store the output of getChoice function that validates integer inputs         |	I           |	local   |	enterDetails, editPatients
    overseasTravelAns   |	bool            |	to store whether or not the patient has been overseas                           |	I           |	local   |	enterDetails
    H_Symptoms          |	bool            |	to store if the patient has high-risk symptom                                   |	I           |	local   |	enterDetails
    M_Symptoms          |	bool            |	to store if the patient has medium-risk symptom                                 |	I           |	local   |	enterDetails
    L_Symptoms          |	bool            |	to store if the patient has low-risk symptom                                    |	I           |	local   |	enterDetails
    N_Symptoms          |	bool            |	to store if the patient has no symptom                                          |	I           |	local   |	enterDetails
    location_num        |	int             |	to save which location the patient has visited from the list                    |	I           |	local   |	enterDetails
    high                |	int             |	to save upper limit of choice for getChoice function                            |	I           |	local   |	enterDetails, whichPatient
    visitHighRisk       |	bool            |	to store whether or not the patient has visited a high risk area                |	I           |	local   |	enterDetails
    line                |	string          |	to store the information read from patients/symptoms/riskyLocations files       |	I           |	local   |	readPatients, readSymptoms, readLocations
    DOB                 |	string          |	stores the date of birth of positive patients                                   |	O           |	local   |	posPatients
    yearStr             |	string          |	stores the year of birth of positive patients                                   |	O           |	local   |	posPatients
    year                |	int             |	stores the year only of positive patients to caluclate their age                |	O           |	local   |	posPatients
    age                 |	int             |	stores the age of positive patients                                             |	O           |	local   |	posPatients
    result              |	int             |	stores the user choice                                                          |	I           |	local   |	updatePatientResults
    Loc[30]             |	char            |	stores the new risky locatoins (after a patient is positive)                    |	I           |	local   |	updatePatientResults
    exist               |   bool            |	stores true if the new location already exists in the riskylocation file        |	O           |	local   |	updatePatientResults, searchPatient
    WIDTH               |	constant int    |	for display purposes                                                            |	O           |	local   |	whichPatient, editPatient
    emptySymptoms       |	bool            |	stores true if the patinets file is empty                                       |	O           |	global  |	enterDetails, readSymptoms

    Please Note: local variables that appear in more than one funciton are either passed to that function or re-created locally in the new function.
*/

//----------------------------------------TEST DATA----------------------------------------------------------------------
/*
    1. Validation - try several inputs in the options menu
        Type check:
            Input	:	A, @
            Outout	:	Invalid choice/input, please try again:
        Range check [1 , 6]:
            Input 	:	8, 0
            Outout	:	Invalid choice/input, please try again:
        Existance checl:
            Input	:	" "
            Output	:	Invalid choice/input, please try again:
            
            Input   :   1
                Validation Passed!

    2. Menu Functions:
        Option 1:
            The Patient ID is: 998634
                    Make sure you have a record of your ID!

            Enter Patient's First Name: Anthony
            Enter Patient's Last Name: Melville
            Enter Patient's Date of Birth:  
                    Day: 22
                    Month: 5
                    Year: 1995
            Enter Patient's address: 82 Marion St
            Has the patient travelled overseas in the last 6 months? 
            1. Yes          2. No
            Make your selection: 2

            Please select if you have High, Medium or Low risk symptoms from the above list:

            1. High         2. Medium               3. Low          4. None
            Make your selection: 4

            Have you visited a high-risk location from the list above?
            1. Yes          2. No
            Make your selection: 1
            Enter the number that corresponds to the location you have visited: 6

            What time approximatly did you visit this location (24hr format)? 15:30

            Isolate yourself at home, no need for the test!

        Option 2:
            Enter Patient ID: 165944 //non-exisiting ID
            ID not found! please try again...
            Enter Patient ID: 6395 //out of range Id (less than 6 digits)

            Invalid choice/input, please try again: 123456 //existing ID
            Please enter your COVID-19 test results David : 
            1. Positive
            2. Negative
            Make your selection: 2
            Your test result is Negative, please remain COVID Safe.

        Option 3:
            -------High Risk Locations-------
            Federation Square
            Melbourne Cricket Ground
            Arts Centre Melbourne
            Kmart Footscary
            Melbourne Central
            Royal Hospital
            Queen Victoria Market
            Parliament House
            National Gallery of Victoria
            Immigration Museum
            Macdonalds CBD

        Option 4:
            Which patient would you like to edit?

            1.      Name:  David          Roberts           ID:  123456
            2.      Name:  James          Taka              ID:  654321
            3.      Name:  Sam            Wellington        ID:  649756
            4.      Name:  Marella        Morad             ID:  792258
            5.      Name:  Geroge         Smith             ID:  762259
            6.      Name:  Sarah          Mint              ID:  617447
            7.      Name:  Chris          John              ID:  316627
            8.      Name:  Joey           Tom               ID:  999175
            9.      Name:  Monica         Geller            ID:  273724
            10.     Name:  Robert         Hatcher           ID:  984849
            11.     Name:  Alma           Mitchell          ID:  243945
            12.     Name:  Anthony        Melville          ID:  998634
            Make your selection: 12

            Which field would you like to edit of patient: Anthony Melville
            1. Health Status
            2. Address
            3. First Name
            4. Last Name
            Make your selection: 2


            What is the new address of the patient?
            Please Enter: 81 Marion St

            The address of Anthony Melville has been updated to 81 Marion St


            Would you like to edit another field of this patient?
            1. Yes              2. No
            Make your selection: 2

        Option 5:
            -------Positive Patients List-------
            Patient - James Taka :
                    ID: 654321
                    Age: 29
                    Address: 42 Loft Ave
                    Visited Location: Macdonalds CBD
                    Visit Time: 16
                    Overseas Travel: Yes
                    Test Result: Positive
                    Health Status: Alive

            Patient - Sam Wellington:
                    ID: 649756
                    Age: 17
                    Address: 52 Nice Street
                    Visited Location: Melbourne Cricket Ground
                    Visit Time: 8:30
                    Overseas Travel: No
                    Test Result: Positive
                    Health Status: Alive    

        Option 6:
            GoodBye
*/