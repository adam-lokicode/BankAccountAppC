#include <iostream>
#include <cstdio>
#include "antithesis_sdk.h"
#include "antithesis_instrumentation.h"

class BankAccount {
private:
    int balance;
    static constexpr int MAX_BALANCE = 700; // Maximum allowable balance

public:
    // Constructor initializes balance
    BankAccount(int initialBalance) : balance(initialBalance) {}

    // Function to deposit money into the account
    void deposit(int amount) {
        if (amount <= 0) { // Prevent zero or negative deposits
            antithesis::send_event("deposit_failed", antithesis::JSON{
                {"amount", amount},
                {"balance", balance},
                {"reason", "Deposit amount must be greater than zero"}
            });
            return;
        }
       
        if (balance + amount > MAX_BALANCE) { // Check for balance overflow
            antithesis::send_event("deposit_failed", antithesis::JSON{
                {"amount", amount},
                {"balance", balance},
                {"reason", "Deposit would exceed maximum balance"}
            });
            return;
        }
        
        balance += amount;
        antithesis::send_event("deposit_successful", antithesis::JSON{
            {"amount", amount},
            {"balance", balance}
        });
        
        ALWAYS(balance <= MAX_BALANCE);
    }

    // Function to withdraw money from the account
    bool withdraw(int amount) {
        if (amount <= 0 || amount > balance) { // Validate withdrawal amount
            SOMETIMES_GREATER_THAN(amount, balance, "Withdrawal amount exceeds balance", {{"amount", amount}});
            antithesis::send_event("withdrawal_failed", antithesis::JSON{
                {"amount", amount},
                {"balance", balance}
            });
            return false;
        }
        
        ALWAYS(amount >= 0);
        ALWAYS(amount <= balance);
        
        int percentage = (balance == 0) ? 0 : (amount * 100) / balance; // Prevent division by zero
        if (percentage < 10) {
            SOMETIMES_LESS_THAN(percentage, 10, "Withdrawal is significantly less than 10% of balance", {{"amount", amount}});
            antithesis::send_event("low_withdrawal", antithesis::JSON{
                {"amount", amount},
                {"balance", balance}
            });
        }
        
        balance -= amount;
        antithesis::send_event("withdrawal_successful", antithesis::JSON{
            {"amount", amount},
            {"balance", balance}
        });
        
        return true;
    }

    // Function to get the current balance
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
    });
    
    int num = antithesis::randomInt(0, 1);
    int finalTransactionAttempts = (num == 0) ? 0 : 10000;
    
    while (i <= finalTransactionAttempts) {
        i++;
        
        int transactionType = antithesis::randomInt(0, 1); // 0 for deposit, 1 for withdrawal
        
        if (transactionType == 0) {
            int depositAmount = antithesis::randomInt(1, 200);
            account.deposit(depositAmount);
            std::cout << "Deposit successful! New balance: " << account.getBalance() << std::endl;
        } else {
            int withdrawAmount = antithesis::randomInt(1, 700);
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
    });
    
    return 0;
}