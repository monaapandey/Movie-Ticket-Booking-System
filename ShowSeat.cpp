#include <iostream>
#include <string>
using namespace std;

class Seat;

enum class SeatStatus { AVAILABLE, BOOKED };

class ShowSeat {
private:
    Seat* seat;
    SeatStatus status;

public:
    ShowSeat(Seat* seat) {
        this->seat = seat; // this keyword
        this->status = SeatStatus::AVAILABLE;
    }

    bool isAvailable() const { return status == SeatStatus::AVAILABLE; }

    // Encapsulation: status is private and changes only through validation methods.
    bool book() {
        if (!isAvailable()) return false;
        status = SeatStatus::BOOKED;
        return true;
    }

    bool release() {
        if (isAvailable()) return false;
        status = SeatStatus::AVAILABLE;
        return true;
    }

    Seat* getSeat() const { return seat; }
    SeatStatus getStatus() const { return status; }
};
