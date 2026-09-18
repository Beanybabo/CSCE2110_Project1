
#

#include <iostream>
#include <stack>
#include "reservation.h"

using namespace std;

class CancellationHistory {
public:
	void AddCancellation(Reservation reservation);
	void RestoreCancellation();
	void DisplayHistory();

private:
	stack<Reservation> cancelledReservations;



};
#endif
