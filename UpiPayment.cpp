class UpiPayment : public Payment {
public:
    bool pay(double amount) override {
        int result;

        cout << "\nUPI Payment Amount: Rs." << amount << endl;
        cout << "Enter 1 for SUCCESS or 0 to simulate FAILURE: ";
        cin >> result;

        return result == 1;
    }
};