# COVID-Testing-Recommendation

_This project was initially implemented for SWE20004 - Technical Software Development unit undertaken in Semester 1 - 2021_

# 1 Project Background #
## 1.0 Introduction ##
The start of the year 2020, marked the first COVID case in Australia, which then turned out to be a worldwide pandemic. As the virus continued to spread, people started confusing COVID symptoms with cold flu symptoms, given that they do share some of the symptoms. Shared symptoms, as declared by the Australian Government include cough and fever. Therefore, we have decided to develop this program to help people decide whether they need a COVID test or not.
## 1.1 Project Description ##
This project is based on analysing patient’s details and generate a test recommendation for them accordingly. First, the patient will be required to register to the program by entering their details which include:
* Patient ID
* Name
* Date of Birth
* Address
* Visited Locations along with the date and time
* Last Overseas Travel
* Symptoms

Some of the above details will be unique to the patient, such as their ID and name. However, some will be chosen from a pre-formulated list. For example, COVID symptoms will be a pre-filled list based on documented cases. Besides, visited locations will be updated automatically if new cases happen to be found at these locations.
After the patient has successfully entered their details, the program will process the information and inform the patient of whether it is recommended for them to take the COVID test. Lastly, COVID test details and the status of each patient will be updated in the system.
To simplify the functionality of the program, the user will have a set of 6 options to choose from by typing the number of the option (see table 1), for example, typing ‘2’ will display a list of high-risk locations where patients with positive COVID test have been to.

User Entry    | Program Output
------------- | -------------
1             | Patient details for COVID test recommendation
2             | High-Risk Locations
3             | COVID Symptoms
4             | COVID Positive Patients Detail
5             | Update details
6             | Quit
## 1.2 Problem Statement ##
To build a program that predicts the need for a COVID test, display COVID symptoms classified by severity, and show COVID high-risk locations based on locally stored data.
