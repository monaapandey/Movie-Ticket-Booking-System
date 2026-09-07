#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <set>
#include <algorithm>
using namespace std;

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



// ---------- Main menu ----------
int main() {


    //adding moivies
    Movie movie1("3 Idiots", "Hindi", 170);
    Movie movie2("Interstellar", "English", 169);

    //adding seats 
    Screen screen1(1);
    screen1.addSeat(Seat("A1", SeatType::SILVER));
    screen1.addSeat(Seat("A2", SeatType::SILVER));
    screen1.addSeat(Seat("A3", SeatType::SILVER));
    screen1.addSeat(Seat("A4", SeatType::SILVER));
    screen1.addSeat(Seat("B1", SeatType::GOLD));
    screen1.addSeat(Seat("B2", SeatType::GOLD));
    screen1.addSeat(Seat("B3", SeatType::GOLD));
    screen1.addSeat(Seat("C1", SeatType::PLATINUM));

    Screen screen2(2);
    screen2.addSeat(Seat("A1", SeatType::SILVER));
    screen2.addSeat(Seat("A2", SeatType::SILVER));
    screen2.addSeat(Seat("B1", SeatType::GOLD));
    screen2.addSeat(Seat("B2", SeatType::GOLD));
    screen2.addSeat(Seat("C1", SeatType::PLATINUM));

    //creating a new cinema and adding screen to it
    Cinema cinema("PVR Cinemas");
    cinema.addScreen(screen1);
    cinema.addScreen(screen2);

    // Shows reference Movie/Screen objects independently of Show lifetime.
    // Since Cinema stores copies of Screen objects, use the stored Screen addresses.
    Screen* s1 = &cinema.getScreens()[0];
    Screen* s2 = &cinema.getScreens()[1];

    Show show1(&movie1, s1, "06:00 PM");
    Show show2(&movie1, s2, "09:00 PM");
    Show show3(&movie2, s1, "10:00 PM");

    PriceCalculator calculator;
    TicketPrinter printer;
    BookingService service(&calculator, &printer);
    service.addShow(&show1);
    service.addShow(&show2);
    service.addShow(&show3);

    string name, phone;
    cout << "Enter customer name: ";
    getline(cin >> ws, name);
    cout << "Enter phone number: ";
    cin >> phone;
    Customer customer(name, phone);

    int choice = -1;
    while (choice != 0) {
        cout << "\n===== MOVIE TICKET BOOKING =====\n";
        cout << "1. Movies  2. Book  3. Cancel  4. My tickets  0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1:
                service.listMovies();
                break;
            case 2:
                service.bookTicket(&customer);
                break;
            case 3:
                service.cancelBooking();
                break;
            case 4:
                service.showMyTickets(&customer);
                break;
            case 0:
                cout << "Thank you for using Movie Ticket Booking.\n";
                break;
            default:
                cout << "Invalid menu choice. Please try again.\n";
        }
    }
    return 0;
}
