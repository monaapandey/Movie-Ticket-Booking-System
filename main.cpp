#include "Movie.cpp"
#include "Seat.cpp"
#include "Screen.cpp"
#include "Cinema.cpp"
#include "ShowSeat.cpp"
#include "Show.cpp"
#include "Customer.cpp"
#include "Booking.cpp"
#include "Payment.cpp"
#include "UpiPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"
#include "PriceCalculator.cpp"
#include "TicketPrinter.cpp"
#include "BookingService.cpp"

int main() {

    // Movies
    Movie movie1("Avengers", "English", 180);
    Movie movie2("3 Idiots", "Hindi", 170);

    // Screen 1
    Screen screen1(1);

    screen1.addSeat(Seat(1, SILVER));
    screen1.addSeat(Seat(2, SILVER));
    screen1.addSeat(Seat(3, SILVER));

    screen1.addSeat(Seat(4, GOLD));
    screen1.addSeat(Seat(5, GOLD));
    screen1.addSeat(Seat(6, GOLD));

    screen1.addSeat(Seat(7, PLATINUM));
    screen1.addSeat(Seat(8, PLATINUM));

    // Screen 2
    Screen screen2(2);

    screen2.addSeat(Seat(1, SILVER));
    screen2.addSeat(Seat(2, SILVER));

    screen2.addSeat(Seat(3, GOLD));
    screen2.addSeat(Seat(4, GOLD));

    screen2.addSeat(Seat(5, PLATINUM));

    // Cinema owns screens
    Cinema cinema("PVR Cinemas");

    cinema.addScreen(screen1);
    cinema.addScreen(screen2);

    Screen* cinemaScreen1 = &cinema.getScreens()[0];
    Screen* cinemaScreen2 = &cinema.getScreens()[1];

    // Shows
    Show show1(&movie1, cinemaScreen1, "10:00 AM");
    Show show2(&movie1, cinemaScreen2, "06:00 PM");
    Show show3(&movie2, cinemaScreen1, "09:00 PM");

    BookingService bookingService;

    bookingService.addShow(&show1);
    bookingService.addShow(&show2);
    bookingService.addShow(&show3);

    string name;
    string phone;

    cout << "Enter customer name: ";
    getline(cin, name);

    cout << "Enter phone number: ";
    getline(cin, phone);

    Customer customer(name, phone);

    int choice;

    do {
        cout << "\n====================================";
        cout << "\n     MOVIE TICKET BOOKING SYSTEM";
        cout << "\n====================================";
        cout << "\n1. List Movies";
        cout << "\n2. Book Ticket";
        cout << "\n3. Cancel Booking";
        cout << "\n4. Exit";
        cout << "\nEnter choice: ";

        cin >> choice;

        switch (choice) {

        case 1:
            bookingService.listMovies();
            break;

        case 2:
            bookingService.bookTicket(&customer);
            break;

        case 3:
            bookingService.cancelBooking();
            break;

        case 4:
            cout << "Thank you!\n";
            break;

        default:
            cout << "Invalid menu choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}