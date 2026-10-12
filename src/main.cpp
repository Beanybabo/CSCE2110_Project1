#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Resource.h"
#include "Student.h"
#include "WaitingList.h"
#include "CancellationHistory.h"
#include "Reservation.h"
#include "ReservationManager.h"
#include "ReportGenerator.h"
#include "InputHelper.h"

using namespace std;
using namespace InputHelper;

// opens the first path that works
static bool OpenDataFile(ifstream& file, const string& name) {
    const string folders[] = {"../data/", "data/", "../../data/"};
    for (size_t i = 0; i < 3; i++) {
        file.clear();
        file.open((folders[i] + name).c_str());
        if (file.is_open()) return true;
    }
    return false;
}

// finds a resource by id
static Resource* FindResource(vector<Resource>& resources, int id) {
    for (size_t i = 0; i < resources.size(); i++) {
        if (resources[i].GetId() == id) return &resources[i];
    }
    return nullptr;
}

// resources.txt line: R101|Study Room 101|Study Room|Available
static bool LoadResources(vector<Resource>& resources) {
    ifstream file;
    if (!OpenDataFile(file, "resources.txt")) {
        cout << "Error opening resources.txt" << endl;
        return false;
    }

    string line;
    int lineNumber = 0;
    while (getline(file, line)) {
        lineNumber++;
        if (!line.empty() && line[line.size() - 1] == '\r') line.erase(line.size() - 1);
        if (Trim(line).empty()) continue;

        vector<string> parts = Split(line, '|');
        int id = 0;
        string name, type, status;
        bool ok = (parts.size() == 4);
        if (ok) {
            name = Trim(parts[1]);
            type = Trim(parts[2]);
            status = Trim(parts[3]);
            for (size_t i = 0; i < status.size(); i++) status[i] = (char)tolower((unsigned char)status[i]);
            ok = ParseResourceId(parts[0], id) && !name.empty() && !type.empty()
                 && (status == "available" || status == "unavailable" || status == "1" || status == "0");
        }

        if (!ok) {
            cout << "Skipping bad line " << lineNumber << " in resources.txt" << endl;
            continue;
        }
        if (FindResource(resources, id) != nullptr) {
            cout << "Skipping duplicate resource ID on line " << lineNumber << " in resources.txt" << endl;
            continue;
        }

        bool available = (status == "available" || status == "1");
        resources.push_back(Resource(id, name, type, available));
    }
    return true;
}

// reservations.txt line: 301|1001|Alice Smith|R101|09/15/2026
static void LoadReservations(vector<Resource>& resources, ReservationManager& manager) {
    ifstream file;
    if (!OpenDataFile(file, "reservations.txt")) {
        cout << "No reservations.txt found; starting with no reservations." << endl;
        return;
    }

    string line;
    int lineNumber = 0;
    int loaded = 0;
    while (getline(file, line)) {
        lineNumber++;
        if (!line.empty() && line[line.size() - 1] == '\r') line.erase(line.size() - 1);
        if (Trim(line).empty()) continue;

        vector<string> parts = Split(line, '|');
        int reservationId = 0, studentId = 0, resourceId = 0;
        bool ok = (parts.size() == 5)
                  && ParsePositiveInt(parts[0], reservationId)
                  && ParsePositiveInt(parts[1], studentId)
                  && !Trim(parts[2]).empty()
                  && ParseResourceId(parts[3], resourceId)
                  && FindResource(resources, resourceId) != nullptr;

        if (ok && manager.CreateReservation(reservationId, studentId, Trim(parts[2]), resourceId, Trim(parts[4]), false)) {
            loaded++;
        }
        else {
            cout << "Skipping bad line " << lineNumber << " in reservations.txt" << endl;
        }
    }
    cout << "Loaded " << loaded << " existing reservation(s)." << endl;
}

// gives the freed (resource, date) slot to the student at the front of that slot's queue
// students who can no longer be booked are dropped and the next one is tried
static void ServeWaitingStudent(int resourceId, const string& date, ReservationManager& manager, WaitingList& waitingList) {
    if (manager.IsResourceBooked(resourceId, date)) return;

    WaitingEntry entry;
    while (waitingList.ServeNext(resourceId, date, entry)) {
        if (manager.CreateReservation(entry.reservationId, entry.student.GetId(), entry.student.GetName(), resourceId, date, false)) {
            cout << "Waiting list: " << entry.student.GetName() << " (Student ID " << entry.student.GetId()
                 << ") was removed from the waiting list and now has Reservation " << entry.reservationId
                 << " for " << FormatResourceId(resourceId) << " on " << date << "." << endl;
            return;
        }
        cout << "Waiting list: could not book " << entry.student.GetName() << " (Reservation ID "
             << entry.reservationId << " is no longer usable); trying the next student." << endl;
    }
}



static void ViewResources(const vector<Resource>& resources) {
    if (resources.empty()) {
        cout << "No resources found." << endl;
        return;
    }
    for (size_t i = 0; i < resources.size(); i++) {
        resources[i].Display();
        cout << endl;
    }
}

static bool CreateReservationAction(vector<Resource>& resources, ReservationManager& manager, WaitingList& waitingList) {
    int reservationId, studentId, resourceId;
    string studentName, date;

    if (!ReadPositiveInt("Reservation ID: ", reservationId)) return false;
    if (!ReadPositiveInt("Student ID: ", studentId)) return false;
    if (!ReadNonEmptyLine("Student Name: ", studentName)) return false;
    if (!ReadResourceId("Resource ID (e.g. R101): ", resourceId)) return false;
    if (!ReadDate("Reservation Date (MM/DD/YYYY): ", date)) return false;

    Resource* resource = FindResource(resources, resourceId);

    if (resource == nullptr) {
        cout << "Invalid resource ID." << endl;
    }
    else if (manager.SearchReservation(reservationId) != nullptr || waitingList.HasReservationId(reservationId)) {
        cout << "Reservation ID " << reservationId << " is already in use." << endl;
    }
    else if (!resource->GetAvailable()) {
        cout << "Resource is unavailable." << endl;
        waitingList.AddStudent(Student(studentId, studentName), reservationId, resourceId, date);
        cout << "Added to the waiting list for " << FormatResourceId(resourceId) << " on " << date << "." << endl;
    }
    else if (manager.IsResourceBooked(resourceId, date)) {
        cout << FormatResourceId(resourceId) << " is already booked for " << date << "." << endl;
        waitingList.AddStudent(Student(studentId, studentName), reservationId, resourceId, date);
        cout << "Added to the waiting list for " << FormatResourceId(resourceId) << " on " << date << "." << endl;
    }
    else {
        manager.CreateReservation(reservationId, studentId, studentName, resourceId, date);
    }
    return true;
}

static bool CancelReservationAction(vector<Resource>& resources, ReservationManager& manager,
                                    WaitingList& waitingList, CancellationHistory& history) {
    int reservationId;
    if (!ReadPositiveInt("Reservation ID: ", reservationId)) return false;

    Reservation cancelled;
    if (manager.CancelReservation(reservationId, &cancelled)) {
        history.AddCancellation(cancelled);
        cout << "Added to cancellation history." << endl;

        Resource* resource = FindResource(resources, cancelled.GetResoId());
        if (resource != nullptr && resource->GetAvailable()) {
            ServeWaitingStudent(cancelled.GetResoId(), cancelled.GetDate(), manager, waitingList);
        }
    }
    return true;
}

static void UndoCancellationAction(ReservationManager& manager, CancellationHistory& history) {
    Reservation restored; // hand the reservation from the cancellation stack back to the active list

    if (history.RestoreCancellation(restored)) {
        if (manager.RestoreReservation(restored)) {
            cout << "Reservation restored successfully." << endl;
        }
        else {
            history.AddCancellation(restored);   // could not restore, keep it in the history
            cout << "Reservation stays in the cancellation history." << endl;
        }
    }
}

static bool SearchReservationAction(const ReservationManager& manager) {
    int reservationId;
    if (!ReadPositiveInt("Reservation ID: ", reservationId)) return false;

    Reservation* found = manager.SearchReservation(reservationId);
    if (found != nullptr) {
        found->Display();
    }
    else {
        cout << "Reservation not found." << endl;
    }
    return true;
}

static bool SearchResourceAction(vector<Resource>& resources) {
    int resourceId;
    if (!ReadResourceId("Resource ID (e.g. R101): ", resourceId)) return false;

    Resource* found = FindResource(resources, resourceId);
    if (found != nullptr) {
        found->Display();
    }
    else {
        cout << "Invalid Resource ID" << endl;
    }
    return true;
}

// flips resource between available/unavailable. When it becomes available, students waiting for it are served
static bool ToggleAvailabilityAction(vector<Resource>& resources, ReservationManager& manager, WaitingList& waitingList) {
    int resourceId;
    if (!ReadResourceId("Resource ID (e.g. R101): ", resourceId)) return false;

    Resource* resource = FindResource(resources, resourceId);
    if (resource == nullptr) {
        cout << "Invalid Resource ID" << endl;
        return true;
    }

    resource->SetAvailability(!resource->GetAvailable());
    cout << resource->GetName() << " is now " << (resource->GetAvailable() ? "available." : "unavailable.") << endl;

    if (resource->GetAvailable()) {
        vector<string> dates = waitingList.GetWaitingDates(resourceId);
        for (size_t i = 0; i < dates.size(); i++) {
            ServeWaitingStudent(resourceId, dates[i], manager, waitingList);
        }
    }
    return true;
}


// MAIN PROGRAM
int main()
{
    vector<Resource> resources;
    if (!LoadResources(resources)) {
        return 1;
    }

    ReservationManager reservationManager;
    WaitingList waitingList;
    CancellationHistory cancellationHistory;
    ReportGenerator reportGenerator;

    LoadReservations(resources, reservationManager);

    bool running = true;
    while(running)
    {
        cout << endl;
        cout << "Campus Resource Reservation System" << endl;
        cout << "1. View Resources" << endl;
        cout << "2. Create Reservation" << endl;
        cout << "3. Cancel Reservation" << endl;
        cout << "4. View Active Reservations" << endl;
        cout << "5. View Waiting Lists" << endl;
        cout << "6. Undo Cancellation" << endl;
        cout << "7. View Cancellation History" << endl;
        cout << "8. Search Reservations" << endl;
        cout << "9. Search Resources" << endl;
        cout << "10. Generate Reports" << endl;
        cout << "11. Change Resource Availability" << endl;
        cout << "12. Exit" << endl;

        string line;
        int choice = 0;
        if (!ReadLine("Enter Choice: ", line)) {
            break;   // input ended
        }
        if (!ParsePositiveInt(line, choice)) {
            cout << "Invalid input. Please enter a number from 1 to 12." << endl;
            continue;
        }

        switch (choice) {
            case 1:  ViewResources(resources); break;
            case 2:  running = CreateReservationAction(resources, reservationManager, waitingList); break;
            case 3:  running = CancelReservationAction(resources, reservationManager, waitingList, cancellationHistory); break;
            case 4:  reservationManager.DisplayReservations(); break;
            case 5:  waitingList.DisplayWaitingList(); break;
            case 6:  UndoCancellationAction(reservationManager, cancellationHistory); break;
            case 7:  cancellationHistory.DisplayHistory(); break;
            case 8:  running = SearchReservationAction(reservationManager); break;
            case 9:  running = SearchResourceAction(resources); break;
            case 10: reportGenerator.GenerateAllReports(resources, reservationManager, waitingList); break;
            case 11: running = ToggleAvailabilityAction(resources, reservationManager, waitingList); break;
            case 12: running = false; break;
            default: cout << "Invalid input. Please enter a number from 1 to 12." << endl; break;
        }
    }

    return 0;
}
