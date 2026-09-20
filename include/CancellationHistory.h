#ifndef CancellationHistory_H
#define CancellationHistory_H

#include <iostream>
#include <stack>
#include "Reservation.h"

using namespace std;

class CancellationHistory {
public:
	void AddCancellation(Reservation reservation);
	bool RestoreCancellation(Reservation& reservation);
	void DisplayHistory();

private:
	stack<Reservation> cancelledReservations;



};
#endif
