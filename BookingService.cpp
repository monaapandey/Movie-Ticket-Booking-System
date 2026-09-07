#include<iostream>
using namespace std;
class BookingService {
private:
    vector<Show*> shows;
    vector<Booking*> bookings;

    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;

public:
    void addShow(Show* show) {
        shows.push_back(show);
    }

    void listMovies() const {
        cout << "\n----- MOVIES PLAYING -----\n";

        for (int i = 0; i < shows.size(); i++) {
            cout << i + 1 << ". "
                 << shows[i]->getMovie()->getTitle()
                 << " | "
                 << shows[i]->getMovie()->getLanguage()
                 << endl;
        }
    }

    Show* selectShow() {
        listMovies();

        int choice;
        cout << "Select show: ";
        cin >> choice;

        if (choice < 1 || choice > shows.size()) {
            cout << "Invalid show choice.\n";
            return nullptr;
        }

        return shows[choice - 1];
    }

    vector<ShowSeat*> selectSeats(Show* show) {
        vector<ShowSeat*> selected;

        show->displaySeats();

        int count;
        cout << "\nHow many seats? ";
        cin >> count;

        for (int i = 0; i < count; i++)
            selectOneSeat(show, selected);

        return selected;
    }

    void selectOneSeat(Show* show,
                       vector<ShowSeat*>& selected) {

        int number;

        cout << "Enter seat number: ";
        cin >> number;

        ShowSeat* seat = show->findSeat(number);

        if (seat == nullptr) {
            cout << "Invalid seat number.\n";
            return;
        }

        if (!seat->isAvailable()) {
            cout << "Seat already BOOKED. Rejected.\n";
            return;
        }

        seat->book();
        selected.push_back(seat);
    }

    Payment* createPayment(int choice) {
        if (choice == 1)
            return new UpiPayment();

        if (choice == 2)
            return new CardPayment();

        if (choice == 3)
            return new CashPayment();

        return nullptr;
    }

    bool makePayment(double amount) {
        cout << "\n1. UPI\n2. Card\n3. Cash\n";
        cout << "Choose payment method: ";

        int choice;
        cin >> choice;

        Payment* payment = createPayment(choice);

        if (payment == nullptr) {
            cout << "Invalid payment method.\n";
            return false;
        }

        // Runtime polymorphism
        bool success = payment->pay(amount);

        delete payment;

        return success;
    }

    void releaseSeats(vector<ShowSeat*>& seats) {
        for (ShowSeat* seat : seats)
            seat->release();
    }

    void bookTicket(Customer* customer) {
        Show* show = selectShow();

        if (show == nullptr)
            return;

        vector<ShowSeat*> seats = selectSeats(show);

        if (seats.empty()) {
            cout << "No valid seats selected.\n";
            return;
        }

        double total = priceCalculator.calculateTotal(seats);

        Booking* booking =
            new Booking(customer, show, seats, total);

        bool paid = makePayment(total);

        if (!paid) {
            releaseSeats(seats);
            delete booking;

            cout << "\nPayment FAILED.";
            cout << "\nBooking NOT confirmed.";
            cout << "\nSelected seats released.\n";
            return;
        }

        booking->confirm();
        bookings.push_back(booking);

        cout << "\nBooking confirmed successfully!\n";

        ticketPrinter.printTicket(*booking);
    }

    void cancelBooking() {
        int bookingId;

        cout << "Enter Booking ID: ";
        cin >> bookingId;

        Booking* booking = findBooking(bookingId);

        if (booking == nullptr) {
            cout << "Booking not found.\n";
            return;
        }

        if (booking->getStatus() == CANCELLED) {
            cout << "Booking already cancelled.\n";
            return;
        }

        booking->cancel();

        cout << "Booking cancelled successfully.\n";
        cout << "Seats are AVAILABLE again.\n";
    }

    Booking* findBooking(int bookingId) {
        for (Booking* booking : bookings) {
            if (booking->getBookingId() == bookingId)
                return booking;
        }

        return nullptr;
    }

    ~BookingService() {
        for (Booking* booking : bookings)
            delete booking;
    }
};