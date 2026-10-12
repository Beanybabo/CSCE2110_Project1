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

// creates reports about reservations, resources, and waiting lists
// n = active reservations, w = waiting students, r = total resources
class ReportGenerator {
public:
    // displays all active reservations
    void ActiveReservationsReport(const ReservationManager& manager) const; 
    // shows how often resources are being used
    void ResourceUtilizationReport(const vector<Resource>& resources, const ReservationManager& manager) const;
    // shows which resources are requested the most, including waiting list requests
    void MostRequestedReport(const vector<Resource>& resources, const ReservationManager& manager, const WaitingList& waitingList) const;
    // displays statistics about students waiting for resources
    void WaitingListStatisticsReport(const vector<Resource>& resources, const WaitingList& waitingList) const;
    // runs all available reports in one call
    void GenerateAllReports(const vector<Resource>& resources, const ReservationManager& manager, const WaitingList& waitingList) const;

private:
    // counts how many times a resource id appears in a list
    int CountFor(const vector<int>& ids, int resourceId) const;
    // collects the resource ids from all active reservations
    vector<int> ReservedResourceIds(const ReservationManager& manager) const;
    // finds a resource's name using its id and returns an unkown resource lable if the id is not found
    string NameFor(const vector<Resource>& resources, int resourceId) const;
    // prints the heading for a report
    void PrintHeader(const string& title) const;
};

#endif