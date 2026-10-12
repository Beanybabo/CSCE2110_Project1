#ifndef RESERVATIONLIST_H
#define RESERVATIONLIST_H

#include <string>
#include <vector>
#include "Reservation.h"

// each node stores a reservatoin and a pointer to the next node
struct Node{
    Reservation data;
    Node* next;

    Node(Reservation res) : data(res), next(nullptr) {}
};

class ReservationList {
public:
    // sets up an empty reservation list
    ReservationList();
    // frees memory
    ~ReservationList();

    // prevents copying because two lists could try to delete the same node
    ReservationList(const ReservationList&) = delete;
    ReservationList& operator=(const ReservationList&) = delete;

    // adds a resrevation to the end of the list in O(1) time
    void Insert(Reservation res);
    // removes a reservation by id. returns true if it was found and removed
    bool Remove(int reser_id, Reservation* removedRes = nullptr);
    // displays every reservation in the list. takes O(n) time
    void Display() const;
    // checks whether a reservation id already exists
    bool Exists(int reser_id) const;
    // checks whether a resource is already booked on a specific date
    bool IsResourceBooked(int resou_id, const std::string& date) const;
    //s finds a reservation by id and returns a pointer to it
    Reservation* Find(int reser_id) const;

    // resource ids of all active reservations (one entry per reservation)
    std::vector<int> GetResourceIds() const;

    bool isEmpty() const;
    int GetCount() const;

private:
    Node* head;
    Node* tail;
    int count;
};

#endif