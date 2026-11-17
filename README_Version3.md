# Version 3 Design Proposal (Project Evaluation 3)

This version introduces advanced simulation, analytics, and search features.

## Advanced Features
- Smart driver ranking using `Score = 0.7D + 2(5 - R)` (Lower is better).
- Configurable fare components (base fare, surcharges, discounts).
- CSV export for reports.
- Driver performance analytics (average rating, cancellation rate).

## State Rules
- A booking cannot start without an assigned driver.
- A driver cannot be assigned to two active rides.
- Payments cannot be marked "Paid" until the ride is Completed.
