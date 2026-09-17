#include "resource.h"
#include <iostream>
using namespace std;

void Resource() {
    id = 0;
    name = "";
    type = "";
    available = false;
}

void Resource(int identification, string resource_name, string resource_type, bool resource_availability) {
    id = identification;
    name = resource_name;
    type = resource_type;
    available = resource_availability;
}

void Display() {
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Type: " << type << endl;
    if(available){
        cout << "Availablility: available" << endl;
    }
    else{
        cout << "Availablility: unavailable" << endl;
    }
    
}

void SetAvailability(bool new_available) {
    available = new_available
}

int GetId() {
    return id;
}
string GetName() {
    return name;
}
string GetType() {
    return type;
}
bool GetAvailable() {
    return available;
}