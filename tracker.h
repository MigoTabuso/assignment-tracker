#ifndef TRACKER_H
#define TRACKER_H

#include <string>
#include <vector>

struct Assignment {
    int id;
    std::string title;
    std::string courseName;
    std::string dueDate;   // Format: YYYY-MM-DD
    std::string priority;  // "High", "Medium", or "Low"
    std::string status;    // "Pending", "In Progress", or "Completed"
};

struct SummaryStats {
    int total = 0;
    int completed = 0;
    int pending = 0;
    int highPriority = 0;
    double completionRate = 0.0;
};

class AssignmentTracker {
private:
    std::vector<Assignment> assignments;
    int nextId = 1;

public:
    Assignment addAssignment(const std::string& title,
                             const std::string& courseName,
                             const std::string& dueDate,
                             const std::string& priority,
                             const std::string& status = "Pending");

    bool updateAssignment(int id,
                          const std::string& newTitle,
                          const std::string& newCourse,
                          const std::string& newDueDate,
                          const std::string& newPriority,
                          const std::string& newStatus);

    std::vector<Assignment> searchByCourse(const std::string& courseName) const;
    std::vector<Assignment> searchByDueDate(const std::string& dueDate) const;

    SummaryStats generateSummary() const;
    const std::vector<Assignment>& getAllAssignments() const;
};

#endif