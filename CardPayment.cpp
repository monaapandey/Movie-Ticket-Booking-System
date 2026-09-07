#include<iostream>
using namespace std;
class CardPayment : public Payment {
public:
    bool pay(double amount) override {
        int result;

        cout << "\nCard Payment Amount: Rs." << amount << endl;
        cout << "Enter 1 for SUCCESS or 0 to simulate FAILURE: ";
        cin >> result;

        return result == 1;
    }
};