#include "WaitingList.h"
#include "InputHelper.h"
#include <iostream>
using namespace std;

void WaitingList::AddStudent(Student student, int reservationId, int resourceId, const string& date) {
    queues[Slot(resourceId, date)].push(WaitingEntry(student, reservationId, resourceId, date));
    waitingReservationIds.insert(reservationId);
    totalWaiting++;
}

bool WaitingList::ServeNext(int resourceId, const string& date, WaitingEntry& served) {
    map<Slot, queue<WaitingEntry> >::iterator it = queues.find(Slot(resourceId, date));
    if (it == queues.end() || it->second.empty()) {
        return false;
    }

    served = it->second.front();
    it->second.pop();
    waitingReservationIds.erase(served.reservationId);
    totalWaiting--;

    if (it->second.empty()) {
        queues.erase(it);   // keep the map free of empty queues
    }
    return true;
}

bool WaitingList::HasReservationId(int reservationId) const {
    return waitingReservationIds.count(reservationId) > 0;
}

vector<string> WaitingList::GetWaitingDates(int resourceId) const {
    vector<string> dates;
    map<Slot, queue<WaitingEntry> >::const_iterator it = queues.lower_bound(Slot(resourceId, ""));
    while (it != queues.end() && it->first.first == resourceId) {
        dates.push_back(it->first.second);
        ++it;
    }
    return dates;
}

void WaitingList::DisplayWaitingList() const {
    if (totalWaiting == 0) {
        cout << "Waiting list is empty." << endl;
        return;
    }

    for (map<Slot, queue<WaitingEntry> >::const_iterator it = queues.begin(); it != queues.end(); ++it) {
        cout << "=== Waiting for " << InputHelper::FormatResourceId(it->first.first)
             << " on " << it->first.second << " (" << it->second.size() << " waiting) ===" << endl;

        queue<WaitingEntry> temp = it->second;   // copy so the real queue is untouched
        int position = 1;
        while (!temp.empty()) {
            const WaitingEntry& entry = temp.front();
            cout << position << ". ";
            cout << entry.student.GetName() << " (Student ID: " << entry.student.GetId()
                 << ", requested Reservation ID: " << entry.reservationId << ")" << endl;
            temp.pop();
            position++;
        }
        cout << "---------------------" << endl;
    }
}

vector<int> WaitingList::GetResourceIds() const {
    vector<int> ids;
    for (map<Slot, queue<WaitingEntry> >::const_iterator it = queues.begin(); it != queues.end(); ++it) {
        for (size_t i = 0; i < it->second.size(); i++) {
            ids.push_back(it->first.first);
        }
    }
    return ids;
}

int WaitingList::GetSize() const {
    return totalWaiting;
}
