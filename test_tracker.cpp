#include "tracker.h"
#include <cassert>
#include <iostream>

int main() {
    AssignmentTracker tracker;

    // Boundary Case: Summary on an empty tracker (must not divide by zero)
    SummaryStats emptyStats = tracker.generateSummary();
    assert(emptyStats.total == 0);
    assert(emptyStats.completionRate == 0.0);

    // Normal Case: Adding assignments
    Assignment a1 = tracker.addAssignment("Final Project", "CS0053", "2026-11-25", "High", "Pending");
    Assignment a2 = tracker.addAssignment("Problem Set 3", "MATH101", "2026-11-20", "Medium", "Completed");
    assert(a1.id == 1);
    assert(a2.id == 2);
    assert(tracker.getAllAssignments().size() == 2);

    // Normal & Boundary Cases: Searching by course and due date
    assert(tracker.searchByCourse("cs0053").size() == 1);
    assert(tracker.searchByDueDate("2026-11-20").size() == 1);
    assert(tracker.searchByCourse("NONEXISTENT").empty());

    // Normal & Boundary Cases: Updating existing vs. invalid ID
    assert(tracker.updateAssignment(1, "", "", "", "", "Completed") == true);
    assert(tracker.updateAssignment(999, "Ghost", "", "", "", "") == false);

    // Normal Case: Verify updated summary statistics
    SummaryStats stats = tracker.generateSummary();
    assert(stats.total == 2);
    assert(stats.completed == 2);
    assert(stats.pending == 0);
    assert(stats.highPriority == 1);
    assert(stats.completionRate == 100.0);

    std::cout << "All normal and boundary tests passed!\n";
    return 0;
}