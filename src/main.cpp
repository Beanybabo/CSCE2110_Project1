#include <fstream>
#include <iostream>
#include <string>
#include "resource.h"
#include "reservation.h"
#include "reservationmanager.h"
#include "waitinglist.h"
#include "student.h"
#include "cancellationhistory.h"
#include "reportgenerator.h"


using namespace std;

int main()
{
    bool running = true;
    int choice = 0;

    while(running)
    {
        cout << "Campus Resource Reservation System" << endl;
        cout << "1. View Resources" << endl; // display availability as well
        // another to search for resources
        cout << "2. Create Reservation" << endl; // linked list - into queue?
        cout << "3. Cancel Reservation" << endl; // linked list - into queue and stack?
        // another to view active reservations
        cout << "4. View Waiting Lists" << endl; // queue
        cout << "5. Undo Cancellation" << endl; // stack
        // another to display cancellation history
        cout << "6. Search Reservations" << endl; // linked list
        cout << "7. Sort Resources" << endl; // undefined?
        cout << "8. Generate Report" << endl; // undefined?
        cout << "9. Exit" << endl;
        cout << "Enter Choice:" << endl;
        if(!(cin >> choice)){
			cout << "Invalid input" << endl;
			continue;
        if(choice == 1){
            continue; // view resources
        }else if(choice == 2){
            continue; // create reservation
        }else if(choice == 3){
            continue; // cancel reservation
        }else if(choice == 4){
            continue; // view waiting lists
        }else if(choice == 5){
            continue; // undo cancellation
        }else if(choice == 6){
            continue; // search reservations
        }else if(choice == 7){
            continue; // sort resources
        }else if(choice == 8){
            continue; // generate report
        }else if(choice == 9){
            running = false;
        }else{
            cout << "Invalid input" << endl;
            continue;
        }

    }


    return 0;
}