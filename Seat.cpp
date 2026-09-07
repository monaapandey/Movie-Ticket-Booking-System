enum SeatType {
    SILVER,
    GOLD,
    PLATINUM
};

class Seat {
private:
    int seatNumber;
    SeatType type;

public:
    Seat(int seatNumber, SeatType type) {
        this->seatNumber = seatNumber;
        this->type = type;
    }

    int getSeatNumber() const {
        return seatNumber;
    }

    SeatType getType() const {
        return type;
    }

    double getPrice() const {
        if (type == SILVER)
            return 150;

        if (type == GOLD)
            return 250;

        return 400;
    }

    string getTypeName() const {
        if (type == SILVER)
            return "SILVER";

        if (type == GOLD)
            return "GOLD";

        return "PLATINUM";
    }
};