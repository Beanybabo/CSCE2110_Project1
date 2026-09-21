#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../include/Resource.h"
#include "../include/Student.h"
#include "../include/WaitingList.h"
#include "../include/CancellationHistory.h"
#include "../include/Reservation.h"
#include "../include/ReservationManager.h"

using namespace std;

int main()
{
    bool running = true;
    int choice = 0;
    vector<Resource> resources;

    ifstream resourceFile("../data/resources.txt");

    if(!resourceFile.is_open()) {
        cout << "Error opening resources.txt" << endl;
        return 1;
    }

    int tempresourceId;
    string tempresourceName;
    string tempresourceType;
    int tempavailability;

    while(resourceFile >> tempresourceId) {
        resourceFile.ignore();
        getline(resourceFile, tempresourceName, '|');
        getline(resourceFile, tempresourceType, '|');
        resourceFile >> tempavailability;

        resources.push_back(Resource(tempresourceId, tempresourceName, tempresourceType, tempavailability));
    }

    resourceFile.close();

    ReservationManager reservationManager;
    WaitingList waitingList;
    CancellationHistory cancellationHistory;

    while(running)
    {
        cout << "Campus Resource Reservation System" << endl;
        cout << "1. View Resources" << endl; // display availability as well
        cout << "2. Create Reservation" << endl; // linked list - into queue?
        cout << "3. Cancel Reservation" << endl; // linked list - into queue and stack?
        cout << "4. View Active Reservations" << endl;
        cout << "5. View Waiting Lists" << endl; // queue
        cout << "6. Undo Cancellation" << endl; // stack
        cout << "7. View Cancellation History" << endl;
        //cout << "6. Search Reservations" << endl; // linked list
        //cout << "7. Sort Resources" << endl; // undefined?
        //cout << "8. Generate Report" << endl; // undefined?
        cout << "8. Exit" << endl;
        cout << "Enter Choice:" << endl;
        if(!(cin >> choice)){
			cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
			continue;
        }
        if(choice == 1){
            if(resources.empty()) {
                cout << "No resources found." << endl;
            }
            else {
                for(int i = 0; i < resources.size(); i++) {
                    resources.at(i).Display();
                    cout << endl;
                }
            }
        }
        else if(choice == 2){
            int reservationId;
            int studentId;
            string studentName;
            int resourceId;
            string date;

            cout << "Reservation ID: ";
            cin >> reservationId;
            cout << "Student ID: ";
            cin >> studentId;
            cin.ignore();

            cout << "Student Name: ";
            getline(cin, studentName);
            cout << "Resource ID: ";
            cin >> resourceId;
            cout << "Reservation Date: ";
            cin >> date;

            bool resourceFound = false;
            bool resourceAvailable = false;

            for(int i = 0; i < resources.size(); i++) {
                if(resources.at(i).GetId() == resourceId) {
                    resourceFound = true;
                    resourceAvailable = resources.at(i).GetAvailable();
                    break;
                }
            }

            if(!resourceFound) {
                cout << "Invalid resource ID." << endl; // doesnt exist
            }
            else if(!resourceAvailable) {
                cout << "Resource is unavailable." << endl; // added to queue

                Student student(studentId, studentName);
                waitingList.AddStudent(student);

                cout << "Added to waiting list." << endl;
            }
            else {
                reservationManager.CreateReservation(reservationId, studentId, studentName, resourceId, date); // works
            }
        }else if(choice == 3){
            int reservationId;

            cout << "Reservation ID: ";
            cin >> reservationId;

            Reservation cancelledReservation;

            if(reservationManager.CancelReservation(reservationId, &cancelledReservation)) {
                cancellationHistory.AddCancellation(cancelledReservation);
                cout << "Added to cancellation history." << endl;
            }
        }else if(choice == 4){
            reservationManager.DisplayReservations(); // thank goodness its a one line function
        }else if(choice == 5){
            waitingList.DisplayWaitingList();
        }else if(choice == 6){
            Reservation restoredReservation; // hold reservation to hand from cancellation to restoration

            if(cancellationHistory.RestoreCancellation(restoredReservation)) { // if it has something to restore
                if(reservationManager.RestoreReservation(restoredReservation)) { // put it into reservations
                    cout << "Reservation restored successfully." << endl;
                }
            }
        }else if(choice == 7){
            cancellationHistory.DisplayHistory();
        }else if(choice == 8){
            running = false;
        }else{
            cout << "Invalid input" << endl;
            continue;
        }

    }


    return 0;
}