#include <iostream>
#include <vector>
using namespace std;

class Seat;

class Screen {
private:
    int screenNumber;
    vector<Seat> seats; // Composition: Screen owns physical seats.

public:
    Screen(int screenNumber) {
        this->screenNumber = screenNumber; // this keyword
    }

    void addSeat(const Seat& seat) { seats.push_back(seat); }
    int getScreenNumber() const { return screenNumber; }
    vector<Seat>& getSeats() { return seats; }
    const vector<Seat>& getSeats() const { return seats; }
};
