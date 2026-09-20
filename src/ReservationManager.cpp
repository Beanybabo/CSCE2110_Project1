#include "ReservationManager.h"
#include <iostream>

using namespace std;

ReservationManager::ReservationManager(){}

bool ReservationManager::ValidateRequest(int reser_id, int stude_id, int resou_id, const string& date) const {
    if (reser_id <=0 || stude_id <= 0 || resou_id <= 0 || date.empty()) {
        cout << "All IDs must be positive and date cannot be empty.\n";
        return false;
    }

    if (activeReservations.Exists(reser_id)) {
        cout << "Reservation ID " << reser_id << " already exists.\n";
        return false;
    }

    if (activeReservations.IsResourceBooked(resou_id, date)) {
        cout << "Resource " << resou_id << " is already booked for " << date << "./\n";
        return false;
    }
    return true;
}

bool ReservationManager::CreateReservation(int reser_id, int stude_id, string stude_name, int resou_id, string date) {
    if (!ValidateRequest(reser_id, stude_id, resou_id, date)) {
        cout << "Failed to create reservation.\n";
        return false;
    }

    Reservation new_reservation(reser_id, stude_id, stude_name, resou_id, date);
    activeReservations.Insert(new_reservation);
    cout << "Reservation " << reser_id << " successfully created.\n";
    return true;
}

bool ReservationManager::CancelReservation(int reser_id, Reservation* cancelledRes) {
    if (!activeReservations.Remove(reser_id, cancelledRes)) {
        cout << "Reservation ID " << reser_id << " not found.\n";
        return false;
    }

    cout << "Reservation " << reser_id << " successfully canceled.\n";
    return true;
}

void ReservationManager::DisplayReservations() const {
    activeReservations.Display();
}

Reservation* ReservationManager::SearchReservation(int reser_id) const {
    return activeReservations.Find(reser_id);
}