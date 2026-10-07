#include <iostream>
using namespace std;
#include <string>
#include "Student.h"

Student::Student() {
	id = 0;
	name = "";
}
Student::Student(int stu_id, string stu_name) {
	id = stu_id;
	name = stu_name;
}
void Student::Display() const {
	cout << "ID: " << id << endl;
	cout << "Name: " << name << endl;
}
int Student::GetId() const {
	return id;
}
string Student::GetName() const {
	return name;
}