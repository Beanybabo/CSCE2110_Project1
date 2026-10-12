#include "CancellationHistory.h"
#include <iostream>

using namespace std;

void CancellationHistory::AddCancellation(Reservation reservation) {
	cancelledReservations.push(reservation);
}

bool CancellationHistory::RestoreCancellation(Reservation& reservation) {
    if(cancelledReservations.empty()) {
        cout << "Cancellation history is empty.\n";
        return false;
    }

    reservation = cancelledReservations.top();
    cancelledReservations.pop();

    return true;
}


void CancellationHistory::DisplayHistory() const {
	if (cancelledReservations.empty()) {
		cout << "Cancellation history is empty.\n";
		return;
	}

	cout << "--- Cancellation History (most recent first) ---\n";
	stack<Reservation> temp = cancelledReservations;

	while (!temp.empty()) {
		temp.top().Display();
		cout << "---------------------\n";
		temp.pop();
	}
}