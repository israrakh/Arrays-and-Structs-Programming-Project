// Arrays and Structs Programming Project.cpp : This file contains the Marathon Runners with Parallel Arrays and Structs.
//


// Marathon Runners with Structs Program.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int DAYS = 7;  // Number of days
const int MAX_RUNNERS = 100; // Maximum number of runners
// Define a struct to represent a runner
struct Runner {
    string name;               // Runner's name
    double miles[DAYS];        // Miles run each day for 7 days
    double totalMiles;         // Total miles run over 7 days
    double averageMiles;       // Average miles run per day
};
// Function prototypes
void readData(const string& filename, Runner runners[], int& count);
void calculateTotals(Runner runners[], int count);
void displayResults(const Runner runners[], int count);

int main() {
   
    Runner runners[MAX_RUNNERS];  // Array of runners
    int count = 0;

    // Read data from the file
    readData("runners.txt", runners, count);

    // Check if no valid data was read
    if (count == 0) {
        cout << "No valid data found." << endl;

        return 1;  // Exit if no valid runners
    }
    // Calculate totals and averages for each runner
    calculateTotals(runners, count);

    // Display the results
    displayResults(runners, count);

    return 0;

}

// Function to read runner data from the file
void readData(const string& filename, Runner runners[], int& count) {

    ifstream inputFile(filename);

    if (!inputFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    while (inputFile >> runners[count].name) {  // Read runner name

        bool validData = true;

        for (int day = 0; day < DAYS; day++) {
            if (!(inputFile >> runners[count].miles[day]) || runners[count].miles[day] < 0) {
                cerr << "Invalid data for " << runners[count].name << " on day " << (day + 1) << endl;
                validData = false;
                break;  // Skip this runner if invalid data is found
            }
        }
        if (validData) {
            count++;
            if (count >= 100) {
                cerr << "Maximum runner limit reached." << endl;
                break;  // Stop if we reach the maximum number of runners
            }
        }
    }
    inputFile.close();
}

// Function to calculate total and average miles for each runner
void calculateTotals(Runner runners[], int count) {

    for (int i = 0; i < count; i++) {
        runners[i].totalMiles = 0.0;  // Initialize total miles for each runner
        for (int day = 0; day < DAYS; day++) {
            runners[i].totalMiles += runners[i].miles[day];  // Sum the miles for each day
        }
        runners[i].averageMiles = runners[i].totalMiles / DAYS;  // Calculate the average miles per day
    }
}

// Function to display the results in a formatted table
void displayResults(const Runner runners[], int count) {

    cout << fixed << setprecision(2);
    cout << setw(15) << "Runner Name" << setw(10) << "Day 1" << setw(10) << "Day 2" << setw(10) << "Day 3"
        << setw(10) << "Day 4" << setw(10) << "Day 5" << setw(10) << "Day 6" << setw(10) << "Day 7"
        << setw(15) << "Total Miles" << setw(15) << "Avg Miles" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < count; i++) {
        cout << setw(15) << runners[i].name;  // Print runner name
        for (int day = 0; day < DAYS; day++) {
            cout << setw(10) << runners[i].miles[day];  // Print miles for each day
        }
        cout << setw(15) << runners[i].totalMiles;  // Print total miles
        cout << setw(15) << runners[i].averageMiles;  // Print average miles
        cout << endl;  // New line for the next runner

    }

}