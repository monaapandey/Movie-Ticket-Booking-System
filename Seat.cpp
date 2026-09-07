#include <iostream>
#include <string>
using namespace std;

enum class SeatType { SILVER, GOLD, PLATINUM };

class Seat {
private:
    string seatNumber;
    SeatType type;

    static constexpr double SILVER_PRICE = 150.0;
    static constexpr double GOLD_PRICE = 250.0;
    static constexpr double PLATINUM_PRICE = 400.0;

public:
    Seat(string seatNumber, SeatType type) {
        this->seatNumber = seatNumber;   // this keyword
        this->type = type;
    }

    string getSeatNumber() const { return seatNumber; }
    SeatType getType() const { return type; }

    double getPrice() const {
        if (type == SeatType::SILVER) return SILVER_PRICE;
        if (type == SeatType::GOLD) return GOLD_PRICE;
        return PLATINUM_PRICE;
    }

    string getTypeName() const {
        if (type == SeatType::SILVER) return "SILVER";
        if (type == SeatType::GOLD) return "GOLD";
        return "PLATINUM";
    }
};
