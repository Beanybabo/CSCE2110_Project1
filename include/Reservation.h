#include <iostream>
using namespace std;
#include <string>

#ifndef RESERVATION_H
#define RESERVATION_H

class Reservation{
    public:
        // info about the object or something
        Reservation();
        Reservation(int reser_id, int stude_id, string stude_name, int resou_id, string dat);
        void Display();

        int GetReseId();
        int GetStuId();
        string GetStuNam();
        int GetResoId();
        string GetDate();

    private:
        // something to change availability status of resource
        int reservation_id;
        int student_id;
        string student_name;
        int resource_id;
        string date;
};


#endif