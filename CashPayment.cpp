#include<iostream>
using namespace std;
class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        int result;

        cout << "\nCash Amount Due: Rs." << amount << endl;
        cout << "Enter 1 if cash received, otherwise 0: ";
        cin >> result;

        return result == 1;
    }
};