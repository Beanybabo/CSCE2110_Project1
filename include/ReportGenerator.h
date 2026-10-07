#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <iostream>
#include <string>
#include <vector>
#include "Resource.h"
#include "Reservation.h"
#include "ReservationManager.h"
#include "WaitingList.h"

using namespace std;

class ReportGenerator {
public:
    void ActiveReservationsReport(const ReservationManager& manager) const;

    void ResourceUtilizationReport(const vector<Resource>& resources, const ReservationManager& manager) const;

    void MostRequestedReport(const vector<Resource>& resources, const ReservationManager& manager, const WaitingList& waitingList) const;

    void WaitingListStatisticsReport(const vector<Resource>& resources, const WaitingList& waitingList) const;

    void GenerateAllReports(const vector<Resource>& resources, const ReservationManager& manager, const WaitingList& waitingList) const;

private:
    // number of entries in ids equal to resourceId
    int CountFor(const vector<int>& ids, int resourceId) const;
    // resource ids of all active reservations
    vector<int> ReservedResourceIds(const ReservationManager& manager) const;
    // name for a resource id, or unknown resource if it insn't in the list
    string NameFor(const vector<Resource>& resources, int resourceId) const;
    void PrintHeader(const string& title) const;
};

#endif