#ifndef RESERVATIONLIST_H
#define RESERVATIONLIST_H

#include <string>
#include <vector>
#include "Reservation.h"

struct Node{
    Reservation data;
    Node* next;

    Node(Reservation res) : data(res), next(nullptr) {}
};

class ReservationList {
public:
    ReservationList();
    ~ReservationList();

    void Insert(Reservation res);
    //remove by reservation id, returns true if removed
    bool Remove(int reser_id, Reservation* removedRes = nullptr);
    //display all records
    void Display() const;
    //checks for duplicate reservation id
    bool Exists(int reser_id) const;
    //checks if a resource is already booked on a given date
    bool IsResourceBooked(int resou_id, const std::string& date) const;
    //search by reservation id
    Reservation* Find(int reser_id) const;

    //resource ids of all active reservations (one entry per reservation)
    std::vector<int> GetResourceIds() const;

    bool isEmpty() const;
    int GetCount() const;

private:
    Node* head;
    int count;
};

#endif