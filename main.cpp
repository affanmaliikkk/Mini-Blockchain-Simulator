#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "Blockchain.h"
#include "TransactionLogger.h"

using namespace std;

int main() {
    Blockchain myChain;
    srand(time(NULL));
    int choice;

    while(true) {
        cout << "\n===== MINI BLOCKCHAIN SIMULATOR =====\n";
        cout << "1. Create Account \n2. Send Transaction\n3. Display Blockchain\n4. Check Validity\n5. Display Balances\n6. Tamper Block\n7. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        if(choice == 1) {
            string name, dob, gmail, currency;
            int balance;
            cout << "Enter Name: "; getline(cin, name);
            cout << "Enter DOB (DD-MM-YYYY): "; getline(cin, dob);
            cout << "Enter Gmail: "; getline(cin, gmail);
            cout << "Enter Initial Balance: "; cin >> balance; cin.ignore();
            cout << "Enter Currency (e.g., COIN, TOKEN): "; getline(cin, currency);
            myChain.addAccount(name, dob, gmail, balance, currency);

        } else if(choice == 2) {
            string sender, receiver, currency;
            int amt;
            cout << "Sender Name: "; getline(cin, sender);
            cout << "Receiver Name: "; getline(cin, receiver);
            cout << "Amount: "; cin >> amt; cin.ignore();
            cout << "Currency (e.g., COIN, TOKEN): "; getline(cin, currency);
            myChain.addTransaction(sender, receiver, amt, currency);

        } else if(choice == 3) {
            myChain.displayChain();
        } else if(choice == 4) {
            cout << (myChain.isChainValid() ? "\n? Blockchain is VALID\n" : "\n? Blockchain is CORRUPTED\n");
        } else if(choice == 5) {
            myChain.displayBalances();
        } else if(choice == 6) {
            int idx; string newData;
            cout << "Block # to tamper: "; cin >> idx; cin.ignore();
            cout << "New Name/Data: "; getline(cin, newData);
            myChain.tamperBlock(idx, newData);
        } else if(choice == 7) {
            break;
        } else {
            cout << "? Invalid choice!\n";
        }
    }

    TransactionLogger::readTransactions();
    return 0;
}

