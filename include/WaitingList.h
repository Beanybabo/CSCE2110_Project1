#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <iostream>
#include <queue>
#include <vector>
#include "Student.h"
using namespace std;

class WaitingList {
public:
    // adds a student to the back of the line, waiting on the given resource
    void AddStudent(Student student, int resourceId);
    // removes the student at the front of the line
    void RemoveStudent();
    void DisplayWaitingList() const;

    // resource ids that students are waiting on (one entry per waiting student)
    vector<int> GetResourceIds() const;
    int GetSize() const;

private:
    queue<Student> waitingStudents;
    // matching queue of resource ids (same order as waitingStudents)
    queue<int> waitingResourceIds;
};

#endif
