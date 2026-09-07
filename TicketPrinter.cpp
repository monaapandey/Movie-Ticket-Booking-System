
class TicketPrinter {
public:
    void printTicket(const Booking& booking) const {
        Show* show = booking.getShow();

        cout << "\n====================================\n";
        cout << "              TICKET\n";
        cout << "====================================\n";

        cout << "Booking ID : " << booking.getBookingId() << endl;
        cout << "Customer   : " << booking.getCustomer()->getName() << endl;
        cout << "Movie      : " << show->getMovie()->getTitle() << endl;
        cout << "Screen     : " << show->getScreen()->getScreenNumber() << endl;
        cout << "Time       : " << show->getStartTime() << endl;

        cout << "Seats      : ";

        for (ShowSeat* seat : booking.getBookedSeats())
            cout << seat->getSeat()->getSeatNumber() << " ";

        cout << "\nTotal      : Rs." << booking.getTotalAmount();
        cout << "\nStatus     : CONFIRMED";

        cout << "\n====================================\n";
    }
};