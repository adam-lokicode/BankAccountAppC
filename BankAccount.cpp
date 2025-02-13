#include "BankAccount.h"

using namespace std;

BankAccount::BankAccount(string ownerName, double initialBalance, 
int accountNumber) {
    owner = ownerName;
    balance = initialBalance;
    accountNumber = accountNumber;
}

void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        cout << "Deposited $" << amount << " successfully!" << endl;
    } else {
        cout << "Invalid deposit amount!" << endl;
    }
}

void BankAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        cout << "Withdrawn $" << amount << " successfully!" << endl;
    } else {
        cout << "Invalid or insufficient funds!" << endl;
    }
}

void BankAccount::checkBalance() {
    cout << "Account Owner: " << owner << endl;
    cout << "Current Balance: $" << balance << endl;
}
