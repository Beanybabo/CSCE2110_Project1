#include "Reservation.h"
#include <iostream>
#include <string>
#include "InputHelper.h"
using namespace std;

Reservation::Reservation() {
    reservation_id = 0;
    student_id = 0;
    student_name = "";
    resource_id = 0;
    date = "";
}
Reservation::Reservation(int reser_id, int stude_id, string stude_name, int resou_id, string dat) {
    reservation_id = reser_id;
    student_id = stude_id;
    student_name = stude_name;
    resource_id = resou_id;
    date = dat;
}
void Reservation::Display() const {
    cout << "Reservation ID: " << reservation_id << endl;
    cout << "Student ID: " << student_id << endl;
    cout << "Student Name: " << student_name << endl;
    cout << "Resource ID: " << InputHelper::FormatResourceId(resource_id) << endl;
    cout << "Reservation Date: " << date << endl;
}

int Reservation::GetReseId() const {
    return reservation_id;
}
int Reservation::GetStuId() const {
    return student_id;
}
string Reservation::GetStuNam() const {
    return student_name;
}
int Reservation::GetResoId() const {
    return resource_id;
}
string Reservation::GetDate() const {
    return date;
}