#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <iostream>
#include <string>

class BankAccount {
private:
    std::string owner;
    double balance;
    int accountNumber;

public:
    BankAccount(std::string ownerName, double initialBalance, int accountNumber);
    void deposit(double amount);
    void withdraw(double amount);
    void checkBalance();
    int getAccountNumber();
};

#endif
