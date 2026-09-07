#include <vector>
using namespace std;

class ShowSeat;
class Seat;

class PriceCalculator {
public:
    double calculateTotal(const vector<ShowSeat*>& seats) const {
        double total = 0;
        for (ShowSeat* seat : seats) {
            total += seat->getSeat()->getPrice();
        }
        return total;
    }

};
