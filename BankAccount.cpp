#include <iostream>
#include <cstdio>
#include "antithesis_sdk.h"
#include "antithesis_instrumentation.h"


class BankAccount {
private:
    int balance;
public:
    BankAccount(int initialBalance) : balance(initialBalance) {}

    void deposit(int amount) {
        balance += amount;
    }

    bool withdraw(int amount) {
        if (amount > balance) {
            return false; // Insufficient funds
        }
        balance -= amount;
        return true;
    }

    int getBalance() {
        return balance;
    }
};

int main() {

     
        antithesis::send_event("start", antithesis::JSON{
                                        {"transaction", "start"},
                                        {"timestamp", antithesis::getTimestamp()}
                                    } 
                                ); 
    

    BankAccount account(100);
    
    int withdrawAmount = antithesis::randomInt(0, 100);  // This will be made random
    ALWAYS(withdrawAmount >= 0);

    if (account.withdraw(withdrawAmount)) {
        std::cout << "Withdrawal successful! New balance: " << account.getBalance() << std::endl;
    } else {
        std::cout << "Withdrawal failed due to insufficient funds!" << std::endl;
    }

    
        antithesis::send_event("end", antithesis::JSON{
                                        {"transaction", "end"},
                                        {"timestamp", antithesis::getTimestamp()}
                                    } 
                                ); 
    

    return 0;
}