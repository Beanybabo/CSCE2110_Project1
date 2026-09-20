#ifndef RESERVATOINMANAGER_H
#define RESERVATIONMANAGER_H

#include <vector>
#include <string>
#include "Reservation.h"

class ReservationManager{
public:
    ReservationManager();

    // validates availability & adds new reservation if valid
    bool CreateReservation(int reser_id, int stude_id, std::string stude_name, int resou_id, std::string date);

    // cancels a reservation by its reservation id
    bool CancelReservation(int reser_id);

    // prints current reservations
    void DisplayReservations() const;

    // checks if a resource is free on the requested data and inputs are positive
    bool ValidateRequest(int reser_id, int stude_id, int resou_id, const std::string& date) const;

    int FindReservationIndex(int reser_id) const;

private:
    std::vector<Reservation> reservations;
};

#endif