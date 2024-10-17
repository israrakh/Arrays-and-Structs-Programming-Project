// Arrays and Structs Programming Project.cpp : This file contains the Marathon Runners with Parallel Arrays and Structs.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const int MAX_RUNNERS = 100; // for maximum number of runners
const int DAYS = 7; // Number of Days

void readData(const string& fileName, string names[], double miles[][DAYS], int& count);
void calculateTotalMiles(const double miles[][DAYS], int count, double totalMiles[], double averageMiles[]);
void displayResukts(const string names[], const double miles[][DAYS], int count, double totalMiles[], double averageMiles[]);

int main()
{
    // Declaring variables 
    string names[MAX_RUNNERS];
    double miles[MAX_RUNNERS][DAYS]; // 2D Array for storing miles for 7 days for each runner
    int count = 0;

    // Reading data from the file
    readData("runners.txt", names, miles, count);
    
    if (count == 0) {
        cout << "Not a valid data!" << endl;
        return 1; // exit if there are no valid runners
    }

    // Arrays to store total and average miles for each runner
    double totalMiles[MAX_RUNNERS] = { 0.0 };
    double averageMiles[MAX_RUNNERS] = { 0.0 };

    // Calculating the total and average miles
    calculateTotalMiles(miles, count, totalMiles, averageMiles);

    // Printing the results
    displayResukts(names, miles, count, totalMiles, averageMiles);

    return 0;
}

// Function for reading the data from the file.
void readData(const string& fileName, string names[], double miles[][DAYS], int& count) {
    ifstream inputFile(fileName);
    if (!inputFile) {
        cerr << "Error opening file!" << endl; // cerr is ostream identifier
        return;
    }

    while (inputFile >> names[count]) {
        //Validating the input data
        bool validate = true;
        for (int d = 0; d < DAYS; d++) {
            if (!(inputFile >> miles[count][d]) || miles[count][d] < 0) {
                cerr << "Invalid data for " << names[count] << " on day " << (d + 1) << endl;
                validate = false;
                break; 
            }
        }

        if (validate) {
            count++;
            if (count >= MAX_RUNNERS) {
                cerr << "Maximum runner limit reached!" << endl;
                break; // Stop the loop if we reached the maximum limit
            }
        }
    }
    inputFile.close();
}

// Function for calculating the total miles and average miles for runners
void calculateTotalMiles(const double miles[][DAYS], int count, double totalMiles[], double averageMiles[]) {
    for (int i = 0; i < count; i++) {
        totalMiles[i] = 0.0; // Initialize total for each runner
        for (int d = 0; d < DAYS; d++) {
            totalMiles[i] += miles[i][d]; // Sum of the miles for each day
        }
        averageMiles[i] = totalMiles[i] / DAYS; // Calculate average
    }
}

// Function for printing the results
void displayResukts(const string names[], const double miles[][DAYS], int count, double totalMiles[], double averageMiles[]) {
    cout << fixed << setprecision(2);
    cout << setw(15) << "Runner Name" << setw(10) << "Day 1" << setw(10) << "Day 2" << setw(10) << "Day 3" << setw(10) << "Day 4"
        << setw(10) << "Day 5" << setw(10) << "Day 6" << setw(10) << "Day 7" << setw(15) << "Total Miles"
        << setw(15) << "Average Miles" << endl;
    cout << "___________________________________________________________________________________________________________________" << endl;

    for (int i = 0; i < count; i++) {
        cout << setw(15) << names[i]; // Printing the runners names
        for (int d = 0; d < DAYS; d++) {
            cout << setw(10) << miles[i][d]; // print miles for each day
        }
        cout << setw(15) << totalMiles[i]; // print total miles
        cout << setw(15) << averageMiles[i]; // print average
        cout << endl;
    }
}