#include "resource.h"
#include <iostream>
#include <string>
using namespace std;

Resource::Resource() {
    id = 0;
    name = "";
    type = "";
    available = false;
}

Resource::Resource(int identification, string resource_name, string resource_type, bool resource_availability) {
    id = identification;
    name = resource_name;
    type = resource_type;
    available = resource_availability;
}

void Resource::Display() {
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

void Resource::SetAvailability(bool new_available) {
    available = new_available;
}

int Resource::GetId() {
    return id;
}
string Resource::GetName() {
    return name;
}
string Resource::GetType() {
    return type;
}
bool Resource::GetAvailable() {
    return available;
}