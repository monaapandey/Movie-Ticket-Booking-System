#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Customer;
class Show;
class ShowSeat;

enum class BookingStatus { PENDING, CONFIRMED, CANCELLED };

class Booking {
private:
    static int nextBookingId;       // Static member: unique booking ID generation.
    int bookingId;
    Customer* customer;
    Show* show;
    vector<ShowSeat*> seats;         // Aggregation: references existing ShowSeats.
    double totalAmount;
    BookingStatus status;

public:
    Booking(Customer* customer, Show* show,
            const vector<ShowSeat*>& seats, double totalAmount) {
        this->bookingId = nextBookingId++;
        this->customer = customer;
        this->show = show;
        this->seats = seats;
        this->totalAmount = totalAmount;
        this->status = BookingStatus::PENDING;
    }

    void confirm() { status = BookingStatus::CONFIRMED; }
    void cancel() { status = BookingStatus::CANCELLED; }

    int getBookingId() const { return bookingId; }
    Customer* getCustomer() const { return customer; }
    Show* getShow() const { return show; }
    const vector<ShowSeat*>& getSeats() const { return seats; }
    double getTotalAmount() const { return totalAmount; }
    BookingStatus getStatus() const { return status; }

    string getStatusName() const {
        if (status == BookingStatus::CONFIRMED) return "CONFIRMED";
        if (status == BookingStatus::CANCELLED) return "CANCELLED";
        return "PENDING";
    }
};

int Booking::nextBookingId = 1001;
