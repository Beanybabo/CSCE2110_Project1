#include "ReservationManager.h"
#include <iostream>

using namespace std;

ReservationManager::ReservationManager(){
    // empty list of reservations
}

bool ReservationManager::ValidateRequest(int reser_id, int stude_id, int resou_id, const string& date) const {
    // basic id check
    if (reser_id <= 0 || stude_id <= 0 || resou_id <= 0 || date.empty()) {
        cout << "All IDs must be positibe and date cannot be empty.\n";
        return false;
    }

    // prevent duplicate reservation ids
    if (FindReservationIndex(reser_id) != -1) {
        cout << "Reservatoin ID " << reser_id << "already exists.\n";
        return false;
    }

    // prevent same resource on same date
    for (size_t i = 0; i < reservations.size(); ++i) {
        Reservation current = reservations[i];
        if (current.GetResoId() == resou_id && current.GetDate() == date) {
            cout << "Resource " << resou_id << " is already booked for " << date << ".\n";
            return false;
        }
    }
    
    return true;
}

bool ReservationManager::CreateReservation(int reser_id, int stude_id, string stude_name, int resou_id, string date) {
    if (!ValidateRequest(reser_id, stude_id, resou_id, date)) {
        cout << "Failed to create reservation.\n";
        return false;
    }

    Reservation new_reservation(reser_id, stude_id, stude_name, resou_id, date);
    reservations.push_back(new_reservation);
    cout << "Reservation " << reser_id << " successfully created.\n";
    return true;
}

bool ReservationManager::CancelReservation(int reser_id) {
    int index = FindReservationIndex(reser_id);

    if (index == -1) {
        cout << "Reservation ID " << reser_id << " not found.\n";
        return false;
    }

    reservations.erase(reservations.begin() + index);
    cout << "Reservation " << reser_id << " successfuly canceled.\n";
    return true;
}

void ReservationManager::DisplayReservations() const {
    if (reservations.empty()) {
        cout << "No active reservations.\n";
        return;
    }

    cout << "--- Active Reservations (" << reservations.size() << ") ---\n";
    for (size_t i = 0; i < reservations.size(); ++i) {
        Reservation current = reservations[i];
        current.Display();
        cout << "-------------------------\n";
    }
}

int ReservationManager::FindReservationIndex(int reser_id) const {
    for (size_t i = 0; i < reservations.size(); ++i) {
        Reservation current = reservations[i];
        if (current.GetReseId() == reser_id) {
            return static_cast<int>(i);
        }
    }
    return -1;
}