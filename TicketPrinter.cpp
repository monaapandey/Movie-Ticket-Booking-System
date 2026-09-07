#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

class Booking;
class Customer;
class Show;
class Movie;
class Screen;
class ShowSeat;
class Seat;

class TicketPrinter {
public:
    void printTicket(const Booking& booking) const{
        Show* show = booking.getShow();
        Movie* movie = show->getMovie();
        Screen* screen = show->getScreen();

        cout << "\n==================== TICKET ====================\n";
        cout << "Booking ID : BK" << booking.getBookingId() << "\n";
        cout << "Movie      : " << movie->getTitle() << "\n";
        cout << "Screen     : Screen-" << screen->getScreenNumber()
            << "   " << show->getStartTime() << "\n";
        cout << "Seats      : ";
        for (size_t i = 0; i < booking.getSeats().size(); ++i) {
            if (i) cout << ", ";
            cout << booking.getSeats()[i]->getSeat()->getSeatNumber();
        }
        cout << "\nAmount     : Rs." << fixed << setprecision(0) << booking.getTotalAmount();
        cout << "       Status: " << booking.getStatusName() << "\n";
        cout << "=================================================\n";
    }
};
