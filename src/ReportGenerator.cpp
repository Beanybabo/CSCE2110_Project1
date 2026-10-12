#include "ReportGenerator.h"
#include "InputHelper.h"

int ReportGenerator::CountFor(const vector<int>& ids, int resourceId) const {
    int count = 0;
    for (size_t i = 0; i < ids.size(); i++) {
        if (ids[i] == resourceId) {
            count++;
        }
    }
    return count;
}

vector<int> ReportGenerator::ReservedResourceIds(const ReservationManager& manager) const {
    return manager.GetReservedResourceIds();
}

string ReportGenerator::NameFor(const vector<Resource>& resources, int resourceId) const {
    for (size_t i = 0; i < resources.size(); i++) {
        if (resources[i].GetId() == resourceId) {
            return resources[i].GetName();
        }
    }
    return "Unknown Resource";
}

void ReportGenerator::PrintHeader(const string& title) const {
    cout << "\n====================\n";
    cout << title << "\n";
    cout << "====================\n";
}

void ReportGenerator::ActiveReservationsReport(const ReservationManager& manager) const {
    PrintHeader("Active Reservations Report");
    cout << "Total active reservations: " << ReservedResourceIds(manager).size() << "\n";
    manager.DisplayReservations();
}

void ReportGenerator::ResourceUtilizationReport(const vector<Resource>& resources, const ReservationManager& manager) const {
    PrintHeader("Resource Utilization Report");
    vector<int> reserved = ReservedResourceIds(manager);

    for (size_t i = 0; i < resources.size(); i++) {
        int count = CountFor(reserved, resources[i].GetId());
        cout << resources[i].GetName() << " (ID " << InputHelper::FormatResourceId(resources[i].GetId()) << "): " << count << " active reservation(s)\n";
    }
}

void ReportGenerator::MostRequestedReport(const vector<Resource>& resources, const ReservationManager& manager, const WaitingList& waitingList) const {
    PrintHeader("Most Requested Resource Report");
    vector<int> reserved = ReservedResourceIds(manager);
    vector<int> waiting = waitingList.GetResourceIds();

    int bestId = -1;
    int bestTotal = 0;

    // total requests = active reservations + students waiting for the resource
    for (size_t i = 0; i < resources.size(); i++) {
        int id = resources[i].GetId();
        int total = CountFor(reserved, id) + CountFor(waiting, id);
        cout << resources[i].GetName() << " (ID " << InputHelper::FormatResourceId(id) << "): " << total << " request(s)\n";
        if (total > bestTotal) {
            bestTotal = total;
            bestId = id;
        }
    }

    if (bestId == -1) {
        cout << "No requests yet.\n";
    }
    else {
        cout << "\nMost requested: " << NameFor(resources, bestId) << " (" << bestTotal << " requests)\n";
    }
}

void ReportGenerator::WaitingListStatisticsReport(const vector<Resource>& resources, const WaitingList& waitingList) const {
    PrintHeader("Waiting List Statistics Report");
    vector<int> waiting = waitingList.GetResourceIds();

    cout << "Students waiting: " << waitingList.GetSize() << "\n";

    for (size_t i = 0; i < resources.size(); i++) {
        int count = CountFor(waiting, resources[i].GetId());
        if (count > 0) {
            cout << resources[i].GetName() << ": " << count << " waiting\n";
        }
    }
}

void ReportGenerator::GenerateAllReports(const vector<Resource>& resources, const ReservationManager& manager, const WaitingList& waitingList) const {
    ActiveReservationsReport(manager);
    ResourceUtilizationReport(resources, manager);
    MostRequestedReport(resources, manager, waitingList);
    WaitingListStatisticsReport(resources, waitingList);
}