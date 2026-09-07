#include <iostream>
#include <iomanip>
using namespace std;

class Payment;

class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "\n[CASH] Rs." << fixed << setprecision(0) << amount << " received\n";
        cout << "Enter 1 to confirm cash payment, 0 to cancel: ";
        int result;
        cin >> result;
        if (result == 1) {
            cout << "[CASH] Rs." << amount << " paid successfully\n";
            return true;
        }
        cout << "[CASH] Payment failed\n";
        return false;
    }
};
