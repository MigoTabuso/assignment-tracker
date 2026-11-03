#include <iostream>
#include <vector>
#include "tracker.h"

using namespace std;

int main() {
    vector<Assignment> assignments;
    string filename = "assignments.txt";

    // Load existing records from file upon startup
    loadFromFile(assignments, filename);

    int choice;
    do {
        cout << "\n=========================================\n";
        cout << "       STUDENT ASSIGNMENT TRACKER        \n";
        cout << "=========================================\n";
        cout << "1. Add Assignment\n";
        cout << "2. View All Assignments\n";
        cout << "3. Search Assignment\n";
        cout << "4. Update Assignment Status\n";
        cout << "5. Delete Assignment\n";
        cout << "6. Save and Exit\n";
        cout << "Enter your choice (1-6): ";
        
        // Basic input check to prevent infinite loops on text entry
        if (!(cin >> choice)) {
            cout << "Invalid input type. Please enter a number between 1 and 6.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addAssignment(assignments);
                break;
            case 2:
                viewAssignments(assignments);
                break;
            case 3:
                searchAssignment(assignments);
                break;
            case 4:
                updateAssignment(assignments);
                break;
            case 5:
                deleteAssignment(assignments);
                break;
            case 6:
                saveToFile(assignments, filename);
                cout << "Data saved successfully. Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please select an option between 1 and 6.\n";
        }
    } while (choice != 6);

    return 0;
}