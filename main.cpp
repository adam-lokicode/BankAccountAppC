#include <iostream>
#include "BankAccount.h"
#include <vector>
#include <map>

using namespace std;

void showMenu() {
    cout << "\nBank Account Management System" << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Check Balance" << endl;
    cout << "5. Exit" << endl;
    cout << "Choose an option: ";
}

int main() {
    std::map<int, BankAccount> accounts;
    int choice;
     int accountNumber;
    //create iterator
    map<int, BankAccount>::iterator it = accounts.begin();

    while (true) {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            string name;
            double initialDeposit;
            cout << "Enter owner name: ";
            cin >> name;
            cout << "Enter initial deposit amount: ";
            cin >> initialDeposit;
             while(true) {
                int accountNumber = rand();
                it = accounts.find(accountNumber);
                if (it == accounts.end()) {
                     accounts.insert(std::make_pair(accountNumber, BankAccount(name, initialDeposit, 
            accountNumber)));
            cout << "Account created successfully!" << endl;;
            break;
                } else {
                    continue;
                }
             }
        } 
        else if (choice == 2) {
            cout << "Enter your account number: ";
            cin >> accountNumber;
            it = accounts.find(accountNumber);
            if (it == accounts.end()) {
                   
            cout << "Make an account first!" << endl;
            break;
                }
            double amount;
           
           
                cout << "Enter deposit amount: ";
                cin >> amount;
                it->second.deposit(amount);
           
        } 
        else if (choice == 3) {
            cout << "Enter your account number: ";
            cin >> accountNumber;
            it = accounts.find(accountNumber);
            if (it == accounts.end()) {
                   
            cout << "Make an account first!" << endl;
            break;
                }
            double amount;
            
     
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                it->second.withdraw(amount);
                
          
        } 
        else if (choice == 4) {
            cout << "Enter your account number: ";
            cin >> accountNumber;
            it = accounts.find(accountNumber);
            if (it == accounts.end()) {
                   
            cout << "Make an account first!" << endl;
            break;
                }
                it->second.checkBalance();
         
        } 
        else if (choice == 5) {
            cout << "Exiting program. Thank you!" << endl;
            break;
        } 
        else {
            cout << "Invalid choice! Please enter a valid option." << endl;
        }
    }

    return 0;
}
