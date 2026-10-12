#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include <string>
#include <vector>
#include "Reservation.h"
#include "ReservationList.h"

// manages active reservations and checks that booking requests are valid
// n = number of active reservatoins
class ReservationManager{
public:
    ReservationManager();

    // checks the request and addds a resrevation if all requirements are met
    // verbose = false hides messages when loading reservations from a file
    bool CreateReservation(int reser_id, int stude_id, std::string stude_name, int resou_id, std::string date, bool verbose = true);

    // cancels a reservation using its id
    bool CancelReservation(int reser_id, Reservation* cancelledRes = nullptr);

    // displays all active reservations
    void DisplayReservations() const;

    // checks that ids are positive, the date is valid, and the reservation id is unused, and the resource is available on that date
    bool ValidateRequest(int reser_id, int stude_id, int resou_id, const std::string& date, bool verbose = true) const;

    // finds a resrevation by id and returns a pointer to it
    Reservation* SearchReservation(int reser_id) const;

    // checks whether a resource is already booked on the requested date
    bool IsResourceBooked(int resou_id, const std::string& date) const;

    // restores a cancelled reservation if its id is available and the resource has not been booked by someone else in the meantime
    bool RestoreReservation(Reservation reservation);

    // returns the resouce ids for all active reservations
    std::vector<int> GetReservedResourceIds() const;

private:
    // stores and manages the list of active reservations
    ReservationList activeReservations;
};

#endif