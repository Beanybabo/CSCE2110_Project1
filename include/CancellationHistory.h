#ifndef CancellationHistory_H
#define CancellationHistory_H

#include <iostream>
#include <stack>
#include "Reservation.h"

using namespace std;

class CancellationHistory {
public:
	void AddCancellation(Reservation reservation);
	Reservation RestoreCancellation();
	void DisplayHistory();

private:
	stack<Reservation> cancelledReservations;



};
#endif
