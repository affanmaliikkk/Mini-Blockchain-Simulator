#include "Blockchain.h"
#include <iostream>
#include <cstdlib>
#include "AccountBlock.h"
#include "TransactionBlock.h"
#include "TransactionLogger.h"
#include <sstream>

using namespace std;

Blockchain::Blockchain() {
    blockchain.push_back(
        new AccountBlock(0, "SYSTEM", "01-01-2000", "system@system.com", 0, 0, "0", "COIN")
    );
}

Blockchain::~Blockchain() {
    for (size_t i = 0; i < blockchain.size(); i++)
        delete blockchain[i];
}

// Digital signature helpers
string Blockchain::generateSignature(const string& data, const string& privateKey) {
    string combined = data + privateKey;
    unsigned long hash = 0;
    for(size_t i=0; i<combined.length(); i++) hash = hash*31 + combined[i];
    stringstream ss; ss << hash; return ss.str();
}

bool Blockchain::verifySignature(const string& data, const string& signature, const string& privateKey) {
    return generateSignature(data, privateKey) == signature;
}

void Blockchain::addAccount(const string& name, const string& dob, const string& gmail, int balance, const string& currency) {
    int accNum = rand() % 90000 + 10000;
    blockchain.push_back(
        new AccountBlock(blockchain.size(), name, dob, gmail, accNum, balance, blockchain.back()->getCurrentHash(), currency)
    );
}

void Blockchain::addTransaction(const string& sender, const string& receiver, int amount, const string& currency) {
    // Find sender account
    AccountBlock* senderAcc = NULL;
    for(size_t i=0; i<blockchain.size(); i++) {
        if(blockchain[i]->getBlockType() == "ACCOUNT" && blockchain[i]->getName() == sender) {
            senderAcc = dynamic_cast<AccountBlock*>(blockchain[i]);
            break;
        }
    }
    if(!senderAcc) { cout << "\n? Sender account not found!\n"; return; }

    int fee = (int)(amount * TRANSACTION_FEE_PERCENT / 100.0);
    int totalAmount = amount + fee;

    int bal = getBalance(sender, currency);
    if(bal < totalAmount) {
        cout << "\n? Insufficient balance to cover transaction + fee!\n";
        return;
    }

    // Generate & verify digital signature
    stringstream txData;
    txData << sender << receiver << amount << currency;
    string data = txData.str();
    string signature = generateSignature(data, senderAcc->getPrivateKey());
    if(!verifySignature(data, signature, senderAcc->getPrivateKey())) {
        cout << "\n? Digital signature invalid! Transaction rejected.\n";
        return;
    }

    static int transactionId = 0;
    stringstream ss;
    ss << sender << " -> " << receiver << " : " << amount << " (" << currency << ")";
    string logData = ss.str();
    TransactionLogger::logTransaction(++transactionId, logData);

    // Add transaction block
    blockchain.push_back(
        new TransactionBlock(blockchain.size(), sender, receiver, amount, blockchain.back()->getCurrentHash(), currency, signature)
    );

    // Fee to SYSTEM
    stringstream feeData; feeData << sender << "SYSTEM" << fee << currency;
    blockchain.push_back(
        new TransactionBlock(blockchain.size(), sender, "SYSTEM", fee, blockchain.back()->getCurrentHash(), currency,
                             generateSignature(feeData.str(), senderAcc->getPrivateKey()))
    );

    cout << "? Transaction recorded. Fee: " << fee << " " << currency << "\n";
    showTransactionReceipt(sender, receiver, amount, currency);
}

int Blockchain::getBalance(const string& name, const string& currency) const {
    int balance = 0;
    for(size_t i=0; i<blockchain.size(); i++) {
        BaseBlock* b = blockchain[i];
        if(b->getBlockType() == "ACCOUNT") {
            AccountBlock* a = dynamic_cast<AccountBlock*>(b);
            if(a && a->getName() == name) balance += a->getBalance(currency);
        } else if(b->getBlockType() == "TRANSACTION") {
            TransactionBlock* t = dynamic_cast<TransactionBlock*>(b);
            if(t && t->getCurrency() == currency) {
                if(t->getName() == name) balance -= t->getAmount();
                if(t->getReceiver() == name) balance += t->getAmount();
            }
        }
    }
    return balance;
}

void Blockchain::displayBalances() const {
    cout << "\n--- Account Balances ---\n";
    for(size_t i=0; i<blockchain.size(); i++) {
        BaseBlock* b = blockchain[i];
        if(b->getBlockType() == "ACCOUNT") {
            AccountBlock* a = dynamic_cast<AccountBlock*>(b);
            if(a) {
                map<string,int> balances = a->getAllBalances();
                for(map<string,int>::iterator it = balances.begin(); it != balances.end(); ++it)
                    cout << a->getName() << " (Acct#: " << a->getAccountNumber() << "): " << it->second << " " << it->first << "\n";
            }
        }
    }
}

void Blockchain::displayChain() const {
    for(size_t i=0; i<blockchain.size(); i++)
        blockchain[i]->displayBlock();
}

bool Blockchain::isChainValid() {
    bool valid = true;
    for(size_t i=1; i<blockchain.size(); i++) {
        if(blockchain[i]->getPreviousHash() != blockchain[i-1]->getCurrentHash())
            valid = false;
    }
    return valid;
}

void Blockchain::tamperBlock(int index, const string& newData) {
    if(index > 0 && index < (int)blockchain.size()) {
        blockchain[index]->tamperData(newData);
        cout << "\n? Block #" << index << " tampered!\n";
    } else {
        cout << "\n? Invalid block number!\n";
    }
}

void Blockchain::showTransactionReceipt(const string& sender, const string& receiver, int amount, const string& currency) const {
    for(size_t i=0; i<blockchain.size(); i++) {
        BaseBlock* b = blockchain[i];
        if(b->getBlockType() == "TRANSACTION") {
            TransactionBlock* t = dynamic_cast<TransactionBlock*>(b);
            if(t && t->getName() == sender && t->getReceiver() == receiver && t->getAmount() == amount && t->getCurrency() == currency) {
                cout << "\n--- Transaction Receipt ---\n";
                cout << "Sender: " << sender
                     << "\nReceiver: " << receiver
                     << "\nAmount: " << amount << " " << currency
                     << "\nSignature: " << t->getSignature()
                     << "\nTimestamp: " << t->getTimestamp()
                     << "\n---------------------------\n";
                return;
            }
        }
    }
}

