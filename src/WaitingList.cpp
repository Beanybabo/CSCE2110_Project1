#include "WaitingList.h"
#include <iostream>
using namespace std;

void WaitingList::AddStudent(Student student) {
	waitingStudents.push(student);
}

void WaitingList::RemoveStudent() {
	if (!waitingStudents.empty()) {
		waitingStudents.pop();
	}
}

void WaitingList::DisplayWaitingList() {
	queue<Student> temp = waitingStudents;

	while (!temp.empty()) {
		temp.front().Display();
		temp.pop();

	
	}
}