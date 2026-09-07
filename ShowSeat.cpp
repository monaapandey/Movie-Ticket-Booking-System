enum SeatStatus {
    AVAILABLE,
    BOOKED
};

class ShowSeat {
private:
    Seat* seat;

    // Encapsulation:
    // status cannot be directly modified from outside.
    SeatStatus status;

public:
    ShowSeat(Seat* seat) {
        this->seat = seat;
        status = AVAILABLE;
    }

    bool isAvailable() const {
        return status == AVAILABLE;
    }

    bool book() {
        if (!isAvailable())
            return false;

        status = BOOKED;
        return true;
    }

    void release() {
        status = AVAILABLE;
    }

    Seat* getSeat() const {
        return seat;
    }

    SeatStatus getStatus() const {
        return status;
    }
};