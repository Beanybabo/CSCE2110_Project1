#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include "Student.h"
using namespace std;

// stores a students request while they wait for a resource
struct WaitingEntry {
    Student student;
    int reservationId;  // id of the reservation the student requested
    int resourceId;     // id of the resource the student wants to use
    string date;        // date the student wants to reserve the resource

    // creates an entry with default ids set to 0
    WaitingEntry() : reservationId(0), resourceId(0) {}
    // creates an entry using the students information and request details
    WaitingEntry(Student s, int reserId, int resoId, string d)
        : student(s), reservationId(reserId), resourceId(resoId), date(d) {}
};

// manages waiting queues for each resource and date
// each queue uses FIFO: the first student to join is served first
// s = number of resource/date slots with waiting students
// w = total number of students waiting
class WaitingList {
public:
    // adds a student to the back of the queue for a specific resource and date
    void AddStudent(Student student, int reservationId, int resourceId, const string& date);

    // removes the first student from the queue for the given resource and date
    // returns false if no students are waiting for that slot
    bool ServeNext(int resourceId, const string& date, WaitingEntry& served);

    // checks whether a reservation id is already being used by a waiting student
    bool HasReservationId(int reservationId) const;

    // returns the dates when students are waiting for a specific resource
    vector<string> GetWaitingDates(int resourceId) const;

    // displays the students currently waiting for resources
    void DisplayWaitingList() const; 

    // returns the resource ids students are waiting for
    // each waiting student contributes one entry
    // returns the total number of students waiting across al queues
    vector<int> GetResourceIds() const;
    int GetSize() const;

private:
    // indentifies a waiting queue using a resource id and date
    typedef pair<int, string> Slot;
    // stores a separate fifo queue for reach resource and date
    map<Slot, queue<WaitingEntry> > queues;
    // tracks rservation ids already used by students on the waiting list
    set<int> waitingReservationIds;
    // keeps track of the total number of students waiting across all queues
    int totalWaiting = 0;
};

#endif