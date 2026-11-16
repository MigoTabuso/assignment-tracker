#include <iostream>
#include "tracker.h"
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

void addAssignment(vector<Assignment>& assignments) {
    cout << "[Feature Pending] Add assignment logic goes here.\n";
}

void viewAssignments(const vector<Assignment>& assignments) {
    cout << "[Feature Pending] View assignments logic goes here.\n";
}

void searchAssignment(const vector<Assignment>& assignments) {
    cout << "[Feature Pending] Search assignment logic goes here.\n";
}

void updateAssignment(vector<Assignment>& assignments) {
    cout << "[Feature Pending] Update assignment logic goes here.\n";
}

void deleteAssignment(vector<Assignment>& assignments) {
    cout << "[Feature Pending] Delete assignment logic goes here.\n";
}

void saveToFile(const vector<Assignment>& assignments, const string& filename)
{
    ofstream file(filename);

    if (!file)
    {
        cout << "Error opening file.\n";
        return;
    }

    for (const auto& a : assignments)
    {
        file << a.id << ","
             << a.title << ","
             << a.courseName << ","
             << a.dueDate << ","
             << a.priority << ","
             << a.status << "\n";
    }
}

void loadFromFile(vector<Assignment>& assignments, const string& filename)
{
    ifstream file(filename);
    if (!file)
    {
        return;
    }
    
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        Assignment a;
        string temp;

        getline(ss, temp, ',');
        a.id = stoi(temp);

        getline(ss, a.title, ',');
        getline(ss, a.courseName, ',');
        getline(ss, a.dueDate, ',');
        getline(ss, a.priority, ',');
        getline(ss, a.status);

        assignments.push_back(a);
    }

    file.close();
}

int getValidatedIntInput(int min, int max)
{
    int value;

    while (true)
    {
        if (!(cin >> value))
        {
            cout << "Invalid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (value < min || value > max)
        {
            cout << "Value must be between "
                 << min << " and "
                 << max << ".\n";
            continue;
        }

        return value;
    }
}
