#include <iostream>
using namespace std;
#include <string>

#ifndef RESOURCE_H
#define RESOURCE_H

class Resource{
    public:
        // info about the object or something
        Resource();
        Resource(int identification, string resource_name, string resource_type, bool resource_availability);
        void Display() const;
        void SetAvailability(bool new_available);
        int GetId() const;
        string GetName() const;
        string GetType() const;
        bool GetAvailable() const;

    private:
        // something to change availability status of resource
        int id;
        string name;
        string type;
        bool available;
};


#endif