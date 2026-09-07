#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Movie;
class Screen;
class Seat;
class ShowSeat;

enum class SeatStatus;

class Show {
private:
    Movie* movie;                 // Aggregation: existing Movie is referenced.
    Screen* screen;               // Aggregation: existing Screen is referenced.
    string startTime;
    vector<ShowSeat> showSeats;   // Composition: Show owns show-specific seat states.

    void createShowSeats(){
        for (Seat& seat : screen->getSeats()) {
            showSeats.emplace_back(&seat);
        }
    }


public:
    Show(Movie* movie, Screen* screen, string startTime){
        this->movie = movie;
        this->screen = screen;
        this->startTime = startTime;
        createShowSeats();
    }

    void displaySeats() const{
        cout << "\n" << left << setw(12) << ("SCREEN-" + to_string(screen->getScreenNumber()))
            << setw(10) << startTime << " | " << movie->getTitle() << "\n\n";

        bool printedSilver = false, printedGold = false, printedPlatinum = false;
        for (const ShowSeat& ss : showSeats) {
            string type = ss.getSeat()->getTypeName();
            if (type == "SILVER" && !printedSilver) {
                cout << "SILVER   "; printedSilver = true;
            } else if (type == "GOLD" && !printedGold) {
                cout << "GOLD     "; printedGold = true;
            } else if (type == "PLATINUM" && !printedPlatinum) {
                cout << "PLATINUM "; printedPlatinum = true;
            } else {
                continue;
            }

            for (const ShowSeat& current : showSeats) {
                if (current.getSeat()->getTypeName() == type) {
                    cout << current.getSeat()->getSeatNumber()
                        << (current.isAvailable() ? "[ ] " : "[X] ");
                }
            }
            cout << "\n";
        }
    }


    ShowSeat* findSeat(const string& seatNumber){
        for (ShowSeat& ss : showSeats) {
            if (ss.getSeat()->getSeatNumber() == seatNumber) return &ss;
        }
        return nullptr;
    }

    
    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getStartTime() const { return startTime; }
    vector<ShowSeat>& getShowSeats() { return showSeats; }
};

