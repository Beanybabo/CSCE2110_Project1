#include "ReservationManager.h"
#include "InputHelper.h"
#include <iostream>

using namespace std;

ReservationManager::ReservationManager(){}

bool ReservationManager::ValidateRequest(int reser_id, int stude_id, int resou_id, const string& date, bool verbose) const {
    if (reser_id <= 0 || stude_id <= 0 || resou_id <= 0) {
        if (verbose) cout << "All IDs must be positive.\n";
        return false;
    }

    if (!InputHelper::IsValidDate(date)) {
        if (verbose) cout << "Invalid date \"" << date << "\". Use MM/DD/YYYY with a real calendar date.\n";
        return false;
    }

    if (activeReservations.Exists(reser_id)) {
        if (verbose) cout << "Reservation ID " << reser_id << " already exists.\n";
        return false;
    }

    if (activeReservations.IsResourceBooked(resou_id, date)) {
        if (verbose) cout << "Resource " << InputHelper::FormatResourceId(resou_id) << " is already booked for " << date << ".\n";
        return false;
    }
    return true;
}

bool ReservationManager::CreateReservation(int reser_id, int stude_id, string stude_name, int resou_id, string date, bool verbose) {
    if (!ValidateRequest(reser_id, stude_id, resou_id, date, verbose)) {
        if (verbose) cout << "Failed to create reservation.\n";
        return false;
    }

    Reservation new_reservation(reser_id, stude_id, stude_name, resou_id, date);
    activeReservations.Insert(new_reservation);
    if (verbose) cout << "Reservation " << reser_id << " successfully created.\n";
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

bool ReservationManager::IsResourceBooked(int resou_id, const string& date) const {
    return activeReservations.IsResourceBooked(resou_id, date);
}

bool ReservationManager::RestoreReservation(Reservation reservation) {
    if(activeReservations.Exists(reservation.GetReseId())) {
        cout << "Reservation ID " << reservation.GetReseId() << " already exists.\n";
        return false;
    }

    if(activeReservations.IsResourceBooked(reservation.GetResoId(), reservation.GetDate())) {
        cout << "Cannot restore: " << InputHelper::FormatResourceId(reservation.GetResoId())
             << " is already booked for " << reservation.GetDate() << ".\n";
        return false;
    }

    activeReservations.Insert(reservation);
    return true;
}

vector<int> ReservationManager::GetReservedResourceIds() const {
    return activeReservations.GetResourceIds();
}
