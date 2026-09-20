#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <iostream>
#include <queue>
#include "Student.h"
using namespace std;

class WaitingList {
public:
    // info about the object or something
    void Request(); // have student + resource type
    void AddStudent(Student student);
    void RemoveStudent();
    void DisplayWaitingList();

private:
    // something to change availability status of resource
    //queue of students
    // matching queue of resource types
    queue<Student> waitingStudents;

};

#endif