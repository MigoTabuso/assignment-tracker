#include <iostream>
#include <vector>
#include "tracker.h"

using namespace std;

int main()
{
    AssignmentTracker tracker;
    string filename = "assignments.txt";

    int choice;
    do
    {
        cout << "\n=========================================\n";
        cout << "       STUDENT ASSIGNMENT TRACKER        \n";
        cout << "=========================================\n";
        cout << "1. Add Assignment\n";
        cout << "2. View All Assignments\n";
        cout << "3. Search Assignment by Course\n";
        cout << "4. Update Assignment Status\n";
        cout << "5. Generate Summary Statistics\n";
        cout << "6. Save and Exit\n";
        cout << "Enter your choice (1-6): ";

        if (!(cin >> choice))
        {
            cout << "Invalid input type. Please enter a number between 1 and 6.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            string title, courseName, dueDate, priority, status;
            cout << "Enter assignment title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter course name (e.g., CS0053): ";
            getline(cin, courseName);
            cout << "Enter due date (YYYY-MM-DD): ";
            getline(cin, dueDate);
            cout << "Enter priority (High/Medium/Low): ";
            getline(cin, priority);

            tracker.addAssignment(title, courseName, dueDate, priority);
            cout << "Assignment added successfully!\n";
            break;
        }
        case 2:
        {
            const vector<Assignment> &list = tracker.getAllAssignments();
            cout << "\n--- ALL ASSIGNMENTS ---\n";
            if (list.empty())
            {
                cout << "No assignments found.\n";
            }
            else
            {
                for (const auto &a : list)
                {
                    cout << "ID: " << a.id << " | Title: " << a.title
                         << " | Course: " << a.courseName << " | Due: " << a.dueDate
                         << " | Priority: " << a.priority << " | Status: " << a.status << "\n";
                }
            }
            break;
        }
        case 3:
        {
            string courseQuery;
            cout << "Enter course name to search: ";
            cin.ignore();
            getline(cin, courseQuery);
            vector<Assignment> results = tracker.searchByCourse(courseQuery);
            cout << "\n--- SEARCH RESULTS ---\n";
            for (const auto &a : results)
            {
                cout << "ID: " << a.id << " | Title: " << a.title << " | Course: " << a.courseName << "\n";
            }
            break;
        }
        case 4:
        {
            int id;
            string newTitle, newCourse, newDate, newPriority, newStatus;
            cout << "Enter Assignment ID to update: ";
            cin >> id;
            cout << "Enter new title (or leave blank to skip): ";
            cin.ignore();
            getline(cin, newTitle);
            cout << "Enter new course: ";
            getline(cin, newCourse);
            cout << "Enter new due date: ";
            getline(cin, newDate);
            cout << "Enter new priority: ";
            getline(cin, newPriority);
            cout << "Enter new status (Pending/Completed): ";
            getline(cin, newStatus);

            if (tracker.updateAssignment(id, newTitle, newCourse, newDate, newPriority, newStatus))
            {
                cout << "Assignment updated successfully!\n";
            }
            else
            {
                cout << "Assignment ID not found.\n";
            }
            break;
        }
        case 5:
        {
            SummaryStats stats = tracker.generateSummary();
            cout << "\n--- SUMMARY STATISTICS ---\n";
            cout << "Total Assignments: " << stats.total << "\n";
            cout << "Completed: " << stats.completed << "\n";
            cout << "Pending: " << stats.pending << "\n";
            cout << "High Priority: " << stats.highPriority << "\n";
            cout << "Completion Rate: " << stats.completionRate << "%\n";
            break;
        }
        case 6:
            // tracker.saveToFile(filename);
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please select an option between 1 and 6.\n";
        }
    } while (choice != 6);

    return 0;
}