#ifndef ACCOUNTBLOCK_H
#define ACCOUNTBLOCK_H

#include "BaseBlock.h"
#include <string>
#include <map>
using namespace std;

class AccountBlock : public BaseBlock {
private:
    string name;
    string dob;
    string gmail;
    int accountNumber;
    map<string,int> balances; // multiple currencies
    string privateKey; // digital signature simulation

public:
    AccountBlock(int idx, const string& accName, const string& accDOB, const string& accGmail,
                 int accNum, int bal, const string& prevHash, const string& currency="COIN");

    void displayBlock() const override;
    string calculateHash() const override;
    void tamperData(const string& newData); // override

    string getName() const override { return name; }
    int getAmount() const override { return 0; } // sum of all currencies not needed
    string getReceiver() const override { return ""; }
    string getBlockType() const override { return "ACCOUNT"; }

    int getAccountNumber() const { return accountNumber; }
    int getBalance(const string& currency) const; // single currency
    map<string,int> getAllBalances() const { return balances; }

    string getPrivateKey() const { return privateKey; } // simulate private key
};

#endif

