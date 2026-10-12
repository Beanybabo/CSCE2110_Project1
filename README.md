# CSCE2110_Project1

# Campus Resource Reservation System

# About the Project
This is a C++ program that helps students manage campus resources and reservations.

# Features
- View and search resources
- Create and cancel reservatoins
- Per-resource waiting lists that are served automatically when a slot is freed
- Undo most recent cancellation
- Change a resource's availability
- Search information
- Generate reports

# How the Waiting List Works
- A student joints the waiting list when the resource is unavailable, or when it is already booked on the requested date.
- There is one FIFO queue per (resource, date), so students waiting for one resource never affect another resource.
- When a reservation is cancelled, the student at the front of that resource/date queue is removed from the queue and given the reservation.
- If a resource is switched back to available, the first waiting student for each of its dates is served.
- Undo cancellation refuses to restore a reservation whose slot was already given to a waiting student.

# Data Structures
- Vector - stores resources
- Linked list - stores active reservations
- Queue - manages waiting lists
- Stack - stores cancellation history
- Set - tracks reservation IDs that are waiting

# Main Classes
- Resource - Stores resource information
- Student - Stores student information
- Reservations - Stores reservation information
- ReservationManager - Manages reservations
- WaitingList - Manages waiting lists
- CancellationHistory - Manages cancelled reservations
- ReportGenerator - Builds the reports
- InputHelper - Input parsing and validation (IDs, dates)

# Team Members
- Davion Green
- Benjamin Pickett
- Sakeena Gordon