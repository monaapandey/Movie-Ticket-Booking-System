class Show {
private:
    Movie* movie;
    Screen* screen;
    string startTime;

    // Composition: Show owns its ShowSeat objects
    vector<ShowSeat> showSeats;

public:
    Show(Movie* movie, Screen* screen, string startTime) {
        this->movie = movie;
        this->screen = screen;
        this->startTime = startTime;

        createShowSeats();
    }

    void createShowSeats() {
        for (Seat& seat : screen->getSeats()) {
            showSeats.push_back(ShowSeat(&seat));
        }
    }

    Movie* getMovie() const {
        return movie;
    }

    Screen* getScreen() const {
        return screen;
    }

    string getStartTime() const {
        return startTime;
    }

    vector<ShowSeat>& getShowSeats() {
        return showSeats;
    }

    ShowSeat* findSeat(int seatNumber) {
        for (ShowSeat& showSeat : showSeats) {
            if (showSeat.getSeat()->getSeatNumber() == seatNumber)
                return &showSeat;
        }

        return nullptr;
    }

    void displaySeats() {
        cout << "\n------ SEAT LAYOUT ------\n";

        for (ShowSeat& showSeat : showSeats) {
            Seat* seat = showSeat.getSeat();

            cout << "Seat " << seat->getSeatNumber()
                 << " [" << seat->getTypeName() << "] "
                 << (showSeat.isAvailable() ? "AVAILABLE" : "BOOKED")
                 << "\n";
        }
    }
};