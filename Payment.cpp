class Payment {
public:
    // Abstraction
    virtual bool pay(double amount) = 0;

    virtual ~Payment() {
    }
};