#include <iostream>
#include <cstdio>
#include "antithesis_sdk.h"
#include "antithesis_instrumentation.h"


class BankAccount {
private:
    int balance;
    static constexpr int MAX_BALANCE = 700; //??
public:
    BankAccount(int initialBalance) : balance(initialBalance) {}

    void deposit(int amount) {
        if (amount == 0) {
            antithesis::send_event("deposit_failed", antithesis::JSON{
                {"amount", amount},
                {"balance", balance},
                {"reason", "Deposit amount cannot be zero"}
            });
            return; // Prevent deposit
        }
       
        if (balance + amount > MAX_BALANCE) {
            antithesis::send_event("deposit_failed", antithesis::JSON{
                {"amount", amount},
                {"balance", balance}
            });
            return; // Deposit would exceed maximum balance
        }
        balance += amount;
        antithesis::send_event("deposit_successful", antithesis::JSON{
            {"amount", amount},
            {"balance", balance}
        });
        ALWAYS(balance <= MAX_BALANCE);
    }

    bool withdraw(int amount) {
        
        //SOMETIMES(amount > balance, "Wihdrawal amount is greater than balance", {{"amount", amount}});
        if (amount > balance || amount <= 0) {
            SOMETIMES_GREATER_THAN(amount, balance, "Wihdrawal amount is greater than balance", {{"amount", amount}});
            antithesis::send_event("withdrawal_failed", antithesis::JSON{
                {"amount", amount},
                {"balance", balance}
            });
            return false; // Insufficient funds
        }
        
        ALWAYS(amount >= 0);
        ALWAYS(amount <= balance, "Wihdrawal amount is less than or equal to balance", {{"amount", amount}});
        int percentage = (amount * 100)/balance;
        if (percentage < 10) {
            SOMETIMES_LESS_THAN(percentage, 10, "Wihdrawal amount is signficantly less than 10% of balance", {{"amount", amount}});
            antithesis::send_event("withdrawal_amount is really low", antithesis::JSON{
                {"amount", amount},
                {"balance", balance}
            });
        }
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
     //balance overflow (integer overflow)
   
     BankAccount account(100);
     antithesis::send_event("start", antithesis::JSON{
        {"transaction", "start"},
        {"timestamp", antithesis::getTimestamp()}
    } 
); 
int num = antithesis::randomInt(0, 1);
int finalTransactionAttempts;
if (num == 0) {
    finalTransactionAttempts = 0;
} else {
    finalTransactionAttempts = 10000;
}
     while (i <= finalTransactionAttempts) {
        i++;
    
    
    // Determine random withdrawl or deposit
    int transactionType = antithesis::randomInt(0, 1);  // 0 for deposit, 1 for withdraw
    if (transactionType == 0) {
        int depositAmount = antithesis::randomInt(1, 200);  // This will be made random
        account.deposit(depositAmount);
        std::cout << "Deposit successful! New balance: " << account.getBalance() << std::endl;
    } else {
    int withdrawAmount = antithesis::randomInt(1, 700);  // This will be made random


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