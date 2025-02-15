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
        antithesis::send_event("deposit_successful", antithesis::JSON{
            {"amount", amount},
            {"balance", balance}
        });
    }

    bool withdraw(int amount) {
        
        SOMETIMES(amount > balance, "Wihdrawal amount is greater than balance", {{"amount", amount}});
        if (amount > balance) {
            antithesis::send_event("withdrawal_failed", antithesis::JSON{
                {"amount", amount},
                {"balance", balance}
            });
            return false; // Insufficient funds
        }
      
        ALWAYS(amount >= 0);
        ALWAYS(amount <= balance, "Wihdrawal amount is less than or equal to balance", {{"amount", amount}});
        
        balance -= amount;
        antithesis::send_event("withdrawal_successful", antithesis::JSON{
            {"amount", amount},
            {"balance", balance}
        } 
    );
        return true;
    }

    int getBalance() {
        return balance;
    }
};

int main() {

     int i = 1;
     BankAccount account(100);
     antithesis::send_event("start", antithesis::JSON{
        {"transaction", "start"},
        {"timestamp", antithesis::getTimestamp()}
    } 
); 
     while (i <= 10000) {
        i++;
    
    

    
    // Determine random withdrawl or deposit
    int transactionType = antithesis::randomInt(0, 1);  // 0 for deposit, 1 for withdraw
    if (transactionType == 0) {
        int depositAmount = antithesis::randomInt(1, 200);  // This will be made random
        account.deposit(depositAmount);
        std::cout << "Deposit successful! New balance: " << account.getBalance() << std::endl;
    } else {
    int withdrawAmount = antithesis::randomInt(1, 200);  // This will be made random
    ALWAYS(withdrawAmount >= 0);

    if (account.withdraw(withdrawAmount)) {
        std::cout << "Withdrawal successful! New balance: " << account.getBalance() << std::endl;
    } else {
        std::cout << "Withdrawal failed due to insufficient funds!" << std::endl;
    }

    
       
    

    
                            }
                        }
                        antithesis::send_event("end", antithesis::JSON{
                            {"transaction", "end"},
                            {"timestamp", antithesis::getTimestamp()}
                        } 
                    ); 
                    return 0;
}