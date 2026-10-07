#include "WaitingList.h"
#include <iostream>
using namespace std;

void WaitingList::AddStudent(Student student, int resourceId) {
    waitingStudents.push(student);
    waitingResourceIds.push(resourceId);
}

void WaitingList::RemoveStudent() {
    if (!waitingStudents.empty()) {
        waitingStudents.pop();
        waitingResourceIds.pop();
    }
}

void WaitingList::DisplayWaitingList() const {
    if (waitingStudents.empty()) {
        cout << "Waiting list is empty." << endl;
        return;
    }

    queue<Student> tempStudents = waitingStudents;
    queue<int> tempIds = waitingResourceIds;

    while (!tempStudents.empty()) {
        tempStudents.front().Display();
        cout << "Waiting for Resource ID: " << tempIds.front() << endl;
        cout << "---------------------" << endl;
        tempStudents.pop();
        tempIds.pop();
    }
}

vector<int> WaitingList::GetResourceIds() const {
    vector<int> ids;
    queue<int> temp = waitingResourceIds;
    while (!temp.empty()) {
        ids.push_back(temp.front());
        temp.pop();
    }
    return ids;
}

int WaitingList::GetSize() const {
    return (int)waitingStudents.size();
}
