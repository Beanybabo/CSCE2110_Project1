#ifndef CancellationHistory_H
#define CancellationHistory_H

#include <iostream>
#include <stack>
#include "Reservation.h"

using namespace std;

// stores cancelled reservations using a stack (LIFO)
// the most recently cancelled reservation is the first one restored
class CancellationHistory {
public:
	// adds a cancelled reservation to the history stack
	void AddCancellation(Reservation reservation);
	// restores the most recently cancelled reservatoin
	// returns true if a reservatoin was restored, or false if the stack is empty
	bool RestoreCancellation(Reservation& reservation);
	// displays the list of cancelled reservations
	void DisplayHistory() const;

private:
	// holds cancelled reservations until they are restored
	stack<Reservation> cancelledReservations;

};
#endif