#include <iostream>
using namespace std;
#include <string>

#ifndef RESOURCE_H
#define RESOURCE_H

class Resource{
    public:
        // info about the object or something
        void Resource();
        void Resource(int identification, string resource_name, string resource_type, bool resource_availability);
        void Display();

    private:
        // something to change availability status of resource
        int id;
        string name;
        string type;
        bool available;
}


#endif