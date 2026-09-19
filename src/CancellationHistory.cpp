#include "CancellationHistory.h"
#include <iostream>

using namespace std;

void CancellationHistory::AddCancelation(Reservation reservation) {
	cancelledReservations.push(reservation); 
}
Reservation CancellationHistory::RestoreCancellation() {
	if (!cancelledReservations.empty()) {
		Reservation reservation = cancelledReservations.top();
		cancelledReservations.pop();
		return reservation;
	}
		
	return Reservation();	
}


void CancellationHistory::DisplayHistory() {
	stack<Reservation> temp = cancelledReservations;

	while (!temp.empty()) {
			temp.top().Display();
			temp.pop();
	}
}
