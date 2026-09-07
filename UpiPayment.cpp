#include <iostream>
#include <iomanip>
using namespace std;

class Payment;

class UpiPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "\n[UPI] Rs." << fixed << setprecision(0) << amount << "\n";
        cout << "Enter 1 for successful payment, 0 for failed payment: ";
        int result;
        cin >> result;
        if (result == 1) {
            cout << "[UPI] Rs." << amount << " paid successfully\n";
            return true;
        }
        cout << "[UPI] Payment failed\n";
        return false;
    }
};
