#include "tracker.h"
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