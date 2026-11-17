# Version 2 Design Proposal (Project Evaluation 2)

This version will expand the single-object MVP into a multi-user application using `std::vector`.

## Proposed Classes
- **Passenger**: Stores ID, name, phone, status.
- **Driver**: Stores ID, name, vehicle type, availability, rating.
- **Booking**: Links Passenger ID and Driver ID with route and fare.
- **RideBookingSystem**: Manages vectors of passengers, drivers, and bookings.

## Key Improvements
- Assign available drivers matching the vehicle type.
- Persistent booking IDs (saved to a file).
- Separate payment status from ride status.
- Admin menu for managing drivers and rates.
- Load saved records at startup using `ifstream`.
