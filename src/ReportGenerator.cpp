#include "ReportGenerator.h"
#include "InputHelper.h"


// Merge Sort
// Used by MostRequestedReport to rank resources by popularity
namespace {

struct ResourceRank {
    string name;
    int id;
    int total;   // active reservations and students waiting
};

// returns true if a should come before b:
bool RanksBefore(const ResourceRank& a, const ResourceRank& b) {
    if (a.total != b.total) {
        return a.total > b.total;
    }
    return a.name <= b.name;
}

// merges the two sorted halves [left..mid] and [mid+1..right]
void Merge(vector<ResourceRank>& items, int left, int mid, int right) {
    vector<ResourceRank> temp;
    temp.reserve(right - left + 1);

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right) {
        if (RanksBefore(items[i], items[j])) {
            temp.push_back(items[i++]);
        }
        else {
            temp.push_back(items[j++]);
        }
    }
    while (i <= mid) {
        temp.push_back(items[i++]);
    }
    while (j <= right) {
        temp.push_back(items[j++]);
    }

    for (size_t k = 0; k < temp.size(); k++) {
        items[left + k] = temp[k];
    }
}

// splits the range in half, sorts each half, then merges them
void MergeSort(vector<ResourceRank>& items, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    MergeSort(items, left, mid);
    MergeSort(items, mid + 1, right);
    Merge(items, left, mid, right);
}

}

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

    // total requests = active reservations + students waiting for the resource
    vector<ResourceRank> ranked;
    for (size_t i = 0; i < resources.size(); i++) {
        ResourceRank entry;
        entry.id = resources[i].GetId();
        entry.name = resources[i].GetName();
        entry.total = CountFor(reserved, entry.id) + CountFor(waiting, entry.id);
        ranked.push_back(entry);
    }

    // sort resources by popularity (most requested first) using merge sort
    if (!ranked.empty()) {
        MergeSort(ranked, 0, (int)ranked.size() - 1);
    }

    for (size_t i = 0; i < ranked.size(); i++) {
        cout << (i + 1) << ". " << ranked[i].name << " (ID " << InputHelper::FormatResourceId(ranked[i].id) << "): " << ranked[i].total << " request(s)\n";
    }

    if (ranked.empty() || ranked[0].total == 0) {
        cout << "No requests yet.\n";
    }
    else {
        cout << "\nMost requested: " << ranked[0].name << " (" << ranked[0].total << " requests)\n";
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