#include <fstream>
#include <iostream>
#include "resource.h"
#include "reservation.h"
#include "reservationmanager.h"


using namespace std;

int main()
{
    bool running = true;
    int choice = 0;

    while(running)
    {
        cout << "Campus Resource Reservation System" << endl;
        cout << "1. View Resources" << endl;
        cout << "2. Create Reservation" << endl;
        cout << "3. Cancel Reservation" << endl;
        cout << "4. View Waiting Lists" << endl;
        cout << "5. Undo Cancellation" << endl;
        cout << "6. Search Reservations" << endl;
        cout << "7. Sort Resources" << endl;
        cout << "8. Generate Report" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter Choice:" << endl;
        try{
            cin >> choice;
        }
        except{
            cout << "Invalid input" << endl;
            continue;
        }
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