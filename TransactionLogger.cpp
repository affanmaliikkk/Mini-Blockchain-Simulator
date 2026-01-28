#include "TransactionLogger.h"
#include <fstream>
#include <iostream>
#include <ctime>

using namespace std;

void TransactionLogger::logTransaction(int id, const string& data) {
    ofstream file("C:\\MiniBlockchainLogs\\transactions.txt", ios::app); // safer: current directory

    if (!file.is_open()) {
        cout << "ERROR: Could not open transactions.txt\n";
        return;
    }

    time_t now = time(0);

    file << id << " | " << data << " | " << ctime(&now);
    file.close();

    cout << "DEBUG: Transaction saved to file\n";
}

void TransactionLogger::readTransactions() {
    ifstream file("C:\\MiniBlockchainLogs\\transactions.txt");
    if (!file.is_open()) {
        cout << "ERROR: Could not open transactions.txt\n";
        return;
    }

    string line;
    cout << "\n--- Transaction Log ---\n";
    while (getline(file, line)) {
        cout << line;
    }
    cout << "---------------------\n";
    file.close();
}
