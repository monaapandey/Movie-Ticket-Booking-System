#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
using namespace std;

class Movie;
class Show;
class ShowSeat;
class Booking;
class Customer;
class Payment;
class PriceCalculator;
class TicketPrinter;
class UpiPayment;
class CardPayment;
class CashPayment;

class BookingService {
private:
    vector<Show*> shows;
    vector<Booking*> bookings;
    PriceCalculator* priceCalculator;
    TicketPrinter* ticketPrinter;

public:
    BookingService(PriceCalculator* calculator, TicketPrinter* printer)
        : priceCalculator(calculator), ticketPrinter(printer) {}


    void addShow(Show* show) { shows.push_back(show); }


    void listMovies() const{
        cout << "\n";
        set<string> printed;
        int index = 1;
        for (Show* show : shows) {
            Movie* movie = show->getMovie();
            if (printed.insert(movie->getTitle()).second) {
                cout << "[" << index++ << "] " << left << setw(18) << movie->getTitle()
                    << setw(10) << movie->getLanguage() << movie->getDuration() << " min\n";
            }
        }
    }


Show* selectShow() const {
    if (shows.empty()) {
        cout << "No shows available.\n";
        return nullptr;
    }

    // Create a unique movie list
    vector<Movie*> movies;
    set<string> seen;

    for (Show* show : shows) {
        Movie* movie = show->getMovie();

        if (seen.insert(movie->getTitle()).second) {
            movies.push_back(movie);
        }
    }

    // Display movies before asking for movie choice
    cout << "\nAvailable Movies:\n";

    for (size_t i = 0; i < movies.size(); ++i) {
        cout << "[" << i + 1 << "] "
             << movies[i]->getTitle()
             << "  " << movies[i]->getLanguage()
             << "  " << movies[i]->getDuration()
             << " min\n";
    }

    // Take movie choice
    int movieChoice;

    while (true) {
        cout << "\nChoose movie: ";

        if (!(cin >> movieChoice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Enter a number.\n";
            continue;
        }

        if (movieChoice >= 1 &&
            movieChoice <= static_cast<int>(movies.size())) {
            break;
        }

        cout << "Invalid movie choice. Please try again.\n";
    }

    Movie* selectedMovie = movies[movieChoice - 1];

    // Find shows for selected movie
    vector<Show*> movieShows;

    for (Show* show : shows) {
        if (show->getMovie() == selectedMovie) {
            movieShows.push_back(show);
        }
    }

    // Display shows
    cout << "\nAvailable Shows for "
         << selectedMovie->getTitle() << ":\n";

    for (size_t i = 0; i < movieShows.size(); ++i) {
        cout << "[" << i + 1 << "] "
             << "Screen-" << movieShows[i]->getScreen()->getScreenNumber()
             << "   " << movieShows[i]->getStartTime() << "\n";
    }

    int showChoice;

    while (true) {
        cout << "\nChoose show: ";

        if (!(cin >> showChoice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Enter a number.\n";
            continue;
        }

        if (showChoice >= 1 &&
            showChoice <= static_cast<int>(movieShows.size())) {
            break;
        }

        cout << "Invalid show choice. Please try again.\n";
    }

    return movieShows[showChoice - 1];
}


    vector<ShowSeat*> selectSeats(Show* show) const {
        vector<ShowSeat*> selected;
        int count;
        cout << "\nHow many seats? ";
        cin >> count;

        if (count <= 0) {
            cout << "Invalid number of seats.\n";
            return selected;
        }

        while (static_cast<int>(selected.size()) < count) {
            cout << "Enter seat for seat " << selected.size() + 1 << " (e.g. A1): ";
            string number;
            cin >> number;

            ShowSeat* seat = selectOneSeat(show, number);
            if (!seat) continue;

            if (find(selected.begin(), selected.end(), seat) != selected.end()) {
                cout << "Seat already selected. Choose another seat.\n";
                continue;
            }
            selected.push_back(seat);
        }
        return selected;
    }



    Payment* createPayment(int choice) const {
        if (choice == 1) return new UpiPayment();
        if (choice == 2) return new CardPayment();
        if (choice == 3) return new CashPayment();
        return nullptr;
    }

    bool makePayment(Payment* payment, double amount) const {
        if (!payment) return false;

        // Runtime polymorphism: Payment* calls the correct child pay() at runtime.
        bool success = payment->pay(amount);
        delete payment;
        return success;
    }


    void bookTicket(Customer* customer){
        Show* show = selectShow();
        if (!show) return;

        show->displaySeats();
        cout << "\n( [ ] = available   [X] = booked )\n";

        vector<ShowSeat*> selected = selectSeats(show);
        if (selected.empty()) return;

        double total = priceCalculator->calculateTotal(selected);
        cout << "\n";
        for (ShowSeat* seat : selected) {
            cout << seat->getSeat()->getSeatNumber() << "  "
                << left << setw(8) << seat->getSeat()->getTypeName()
                << "Rs." << fixed << setprecision(0) << seat->getSeat()->getPrice() << "\n";
        }
        cout << "TOTAL             Rs." << total << "\n";

        // Temporarily reserve seats while payment is attempted.
        for (ShowSeat* seat : selected) seat->book();

        cout << "\nPay by: 1.UPI  2.Card  3.Cash > ";
        int choice;
        cin >> choice;
        Payment* payment = createPayment(choice);

        if (!payment || !makePayment(payment, total)) {
            releaseSeats(selected);
            cout << "Booking NOT confirmed. Seats released.\n";
            return;
        }

        Booking* booking = new Booking(customer, show, selected, total);
        booking->confirm();
        bookings.push_back(booking);
        ticketPrinter->printTicket(*booking);
    }


    void cancelBooking() {
        if (bookings.empty()) {
            cout << "No bookings found.\n";
            return;
        }

        cout << "\nEnter Booking ID (e.g. BK1001): ";
        string input;
        cin >> input;

        if (input.rfind("BK", 0) == 0) input = input.substr(2);
        int id;
        try {
            id = stoi(input);
        } catch (...) {
            cout << "Invalid booking ID.\n";
            return;
        }

        Booking* booking = findBooking(id);
        if (!booking) {
            cout << "Booking not found.\n";
            return;
        }
        if (booking->getStatus() == BookingStatus::CANCELLED) {
            cout << "Booking already cancelled.\n";
            return;
        }

        releaseSeats(booking->getSeats());
        booking->cancel();
        cout << "Booking BK" << id << " cancelled successfully.\n";
        cout << "Seats are AVAILABLE again.\n";
    }



    void showMyTickets(Customer* customer) const {
        bool found = false;
        for (Booking* booking : bookings) {
            if (booking->getCustomer() == customer) {
                ticketPrinter->printTicket(*booking);
                found = true;
            }
        }
        if (!found) cout << "No tickets found.\n";
    }


    
    ~BookingService() {
        for (Booking* booking : bookings) delete booking;
    }

private:
    ShowSeat* selectOneSeat(Show* show, const string& seatNumber) const {
        ShowSeat* seat = show->findSeat(seatNumber);
        if (!seat) {
            cout << "Invalid seat number.\n";
            return nullptr;
        }
        if (!seat->isAvailable()) {
            cout << "Seat " << seatNumber << " already BOOKED. Rejected.\n";
            return nullptr;
        }
        return seat;
    }

    Booking* findBooking(int id) const {
        for (Booking* booking : bookings) {
            if (booking->getBookingId() == id) return booking;
        }
        return nullptr;
    }

    void releaseSeats(const vector<ShowSeat*>& seats) const {
        for (ShowSeat* seat : seats) seat->release();
    }
};
