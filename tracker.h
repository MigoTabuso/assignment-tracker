#ifndef TRACKER_H
#define TRACKER_H

#include <string>
#include <vector>

// Structure representing a single student assignment
struct Assignment {
    int id;
    std::string title;
    std::string course;
    std::string dueDate;
    std::string status; // e.g., "Pending" or "Completed"
};

// Function prototypes for Menu, Core Logic, and File Storage/Validation
void showMenu();
void addAssignment(std::vector<Assignment>& assignments);
void viewAssignments(const std::vector<Assignment>& assignments);
void searchAssignment(const std::vector<Assignment>& assignments);
void updateAssignment(std::vector<Assignment>& assignments);
void deleteAssignment(std::vector<Assignment>& assignments);

// File I/O and validation prototypes (handled primarily by Member 3)
void saveToFile(const std::vector<Assignment>& assignments, const std::string& filename);
void loadFromFile(std::vector<Assignment>& assignments, const std::string& filename);
int getValidatedIntInput(int min, int max);

#endif