#include "tracker.h"
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cctype>

namespace {
    std::string toLower(const std::string& input) {
        std::string result = input;
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return result;
    }
}

Assignment AssignmentTracker::addAssignment(const std::string& title,
                                            const std::string& courseName,
                                            const std::string& dueDate,
                                            const std::string& priority,
                                            const std::string& status) {
    Assignment newItem{nextId++, title, courseName, dueDate, priority, status};
    assignments.push_back(newItem);
    return newItem;
}

bool AssignmentTracker::updateAssignment(int id,
                                         const std::string& newTitle,
                                         const std::string& newCourse,
                                         const std::string& newDueDate,
                                         const std::string& newPriority,
                                         const std::string& newStatus) {
    for (auto& item : assignments) {
        if (item.id == id) {
            if (!newTitle.empty()) item.title = newTitle;
            if (!newCourse.empty()) item.courseName = newCourse;
            if (!newDueDate.empty()) item.dueDate = newDueDate;
            if (!newPriority.empty()) item.priority = newPriority;
            if (!newStatus.empty()) item.status = newStatus;
            return true;
        }
    }
    return false;
}

std::vector<Assignment> AssignmentTracker::searchByCourse(const std::string& courseName) const {
    std::vector<Assignment> results;
    std::string query = toLower(courseName);

    for (const auto& item : assignments) {
        if (toLower(item.courseName).find(query) != std::string::npos) {
            results.push_back(item);
        }
    }
    return results;
}

std::vector<Assignment> AssignmentTracker::searchByDueDate(const std::string& dueDate) const {
    std::vector<Assignment> results;
    for (const auto& item : assignments) {
        if (item.dueDate == dueDate) {
            results.push_back(item);
        }
    }
    return results;
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
SummaryStats AssignmentTracker::generateSummary() const {
    SummaryStats stats;
    stats.total = static_cast<int>(assignments.size());

    for (const auto& item : assignments) {
        if (toLower(item.status) == "completed") {
            stats.completed++;
        } else {
            stats.pending++;
        }

        if (toLower(item.priority) == "high") {
            stats.highPriority++;
        }
    }

    if (stats.total > 0) {
        stats.completionRate = (static_cast<double>(stats.completed) / stats.total) * 100.0;
    }

    return stats;
}

const std::vector<Assignment>& AssignmentTracker::getAllAssignments() const {
    return assignments;
}
