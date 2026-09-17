#include <iostream>
using namespace std;
#include <string>

#ifndef STUDENT_H
#define STUDENT_H

class Student{
    public:
        // info about the object or something
        Student();
        Student(int stu_id, string stu_name);
        void Display();
        int GetId();
        string GetName();

    private:
        // something to change availability status of resource
        int id;
        string name;
};


#endif