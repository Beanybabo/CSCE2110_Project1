#include "CancellationHistory.h"
#include <iostream>

using namespace std;

void CancellationHistory::AddCancelation(Reservation reservation) {
	cancelledReservations.push(reservation); 
}
void CancelltionHistory::RestoreCancellation() {
	if (! canceledReservations.empty()) {
		cancelledReservations.pop();
}
	void CancellationHistory::DisplayHistory() {
		stack<Reservation> temp = cancelledReservations;

		while (!temp.empty()) {
			temp.top().Display();
			temp.pop();
		}
}














}