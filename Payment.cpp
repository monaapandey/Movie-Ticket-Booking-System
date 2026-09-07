#include <iostream>
using namespace std;

// Abstraction: Payment defines a common contract.
class Payment {
public:
    virtual bool pay(double amount) = 0; // Pure virtual function.
    virtual ~Payment() = default;
};
