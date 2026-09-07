#include <iostream>
#include <iomanip>
using namespace std;

class Payment;

class CardPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "\n[CARD] Rs." << fixed << setprecision(0) << amount << "\n";
        cout << "Enter 1 for successful payment, 0 for failed payment: ";
        int result;
        cin >> result;
        if (result == 1) {
            cout << "[CARD] Rs." << amount << " paid successfully\n";
            return true;
        }
        cout << "[CARD] Payment failed\n";
        return false;
    }
};
