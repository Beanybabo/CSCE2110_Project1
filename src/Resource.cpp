#include "resource.h"
#include <iostream>
using namespace std;

void Resource() {
    id = 0;
    name = "";
    type = "";
    availability = false;
}

void Resource(int identification, string resource_name, string resource_type, bool resource_availability) {
    id = identification;
    name = resource_name;
    type = resource_type;
    availability = resource_availability;
}

void Display() {
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Type: " << type << endl;
    if(availability){
        cout << "Availablility: available" << endl;
    }
    else{
        cout << "Availablility: unavailable" << endl;
    }
    
}