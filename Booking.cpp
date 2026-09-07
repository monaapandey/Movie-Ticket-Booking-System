#include<iostream>
using namespace std;
enum BookingStatus {
    PENDING,
    CONFIRMED,
    CANCELLED
};

class Booking {
private:
    int bookingId;
    Customer* customer;
    Show* show;
    vector<ShowSeat*> bookedSeats;

    // Encapsulation
    double totalAmount;

    BookingStatus status;

    // Static member for unique booking IDs
    static int nextBookingId;

public:
    Booking(Customer* customer,
            Show* show,
            vector<ShowSeat*> seats,
            double amount) {

        bookingId = nextBookingId++;

        this->customer = customer;
        this->show = show;
        this->bookedSeats = seats;
        this->totalAmount = amount;

        status = PENDING;
    }

    void confirm() {
        status = CONFIRMED;
    }

    void cancel() {
        if (status != CONFIRMED)
            return;

        for (ShowSeat* seat : bookedSeats)
            seat->release();

        status = CANCELLED;
    }

    int getBookingId() const {
        return bookingId;
    }

    Customer* getCustomer() const {
        return customer;
    }

    Show* getShow() const {
        return show;
    }

    vector<ShowSeat*> getBookedSeats() const {
        return bookedSeats;
    }

    double getTotalAmount() const {
        return totalAmount;
    }

    BookingStatus getStatus() const {
        return status;
    }
};

int Booking::nextBookingId = 1001;