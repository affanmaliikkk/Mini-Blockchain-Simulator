#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "BaseBlock.h"
#include <vector>
#include <string>
#include <map>

using namespace std;

const double TRANSACTION_FEE_PERCENT = 2.0; // 2% fee

class Blockchain {
private:
    vector<BaseBlock*> blockchain;

    // Digital signature helpers
    string generateSignature(const string& data, const string& privateKey);
    bool verifySignature(const string& data, const string& signature, const string& privateKey);

public:
    Blockchain();
    ~Blockchain(); // delete all allocated blocks

    // Add blocks
    void addAccount(const string& name, const string& dob, const string& gmail, int balance, const string& currency="COIN");
    void addTransaction(const string& sender, const string& receiver, int amount, const string& currency="COIN");

    // Display
    void displayChain() const;
    void displayBalances() const;
    void showTransactionReceipt(const string& sender, const string& receiver, int amount, const string& currency="COIN") const;

    // Validation & tampering
    bool isChainValid();
    void tamperBlock(int index, const string& newData);

    // Helper
    int getBalance(const string& name, const string& currency="COIN") const;
};

#endif

