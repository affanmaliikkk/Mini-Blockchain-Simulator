#ifndef TRANSACTION_LOGGER_H
#define TRANSACTION_LOGGER_H

#include <string>

class TransactionLogger {
public:
    static void logTransaction(int id, const std::string& data);
    static void readTransactions();   // Optional: read all logged transactions
};

#endif
