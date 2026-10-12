#include "ReservationList.h"
#include <iostream>

using namespace std;

ReservationList::ReservationList() : head(nullptr), tail(nullptr), count(0) {}

ReservationList::~ReservationList() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

void ReservationList::Insert(Reservation res) {
    Node* newNode = new Node(res);

    if (head == nullptr) {
        head = newNode;
    }
    else {
        tail->next = newNode;
    }
    tail = newNode;
    count++;
}

bool ReservationList::Remove(int reser_id, Reservation* removedRes) {
    if (head == nullptr) {
        return false;
    }

    //check head
    if (head->data.GetReseId() == reser_id) {
        Node* toDelete = head;
        if (removedRes != nullptr) {
            *removedRes = head->data;
        }
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete toDelete;
        count--;
        return true;
    }

    //find matching node
    Node* current = head;
    while (current->next != nullptr && current->next->data.GetReseId() != reser_id) {
        current = current->next;
    }

    if (current->next != nullptr) {
        Node* toDelete = current->next;
        if(removedRes != nullptr) {
            *removedRes = toDelete->data;
        }
        current->next = toDelete->next;
        if (toDelete == tail) {
            tail = current;
        }
        delete toDelete;
        count--;
        return true;
    }
    return false;
}

void ReservationList::Display() const {
    if (head == nullptr) {
        cout << "No active reservations.\n";
        return;
    }

    cout << "--- Active Reservations (" << count << ") ---\n";
    Node* current = head;
    while (current != nullptr) {
        current->data.Display();
        cout << "---------------------\n";
        current = current->next;
    }
}

bool ReservationList::Exists(int reser_id) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.GetReseId() == reser_id) {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool ReservationList::IsResourceBooked(int resou_id, const std::string& date) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.GetResoId() == resou_id && current->data.GetDate() == date) {
            return true;
        }
        current = current->next;
    }
    return false;
}

Reservation* ReservationList::Find(int reser_id) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.GetReseId() == reser_id) {
            return &(current->data);
        }
        current = current->next;
    }
    return nullptr;
}

vector<int> ReservationList::GetResourceIds() const {
    vector<int> ids;
    Node* current = head;
    while (current != nullptr) {
        ids.push_back(current->data.GetResoId());
        current = current->next;
    }
    return ids;
}

bool ReservationList::isEmpty() const {
    return head == nullptr;
}

int ReservationList::GetCount() const {
    return count;
}