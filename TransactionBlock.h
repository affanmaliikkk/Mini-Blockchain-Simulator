#ifndef TRANSACTIONBLOCK_H
#define TRANSACTIONBLOCK_H

#include "BaseBlock.h"
#include <string>

using namespace std;

class TransactionBlock : public BaseBlock {
private:
    string sender;
    string receiver;
    int amount;
    string currency;
    string signature; // digital signature

public:
    TransactionBlock(int idx, const string& snd, const string& recv, int amt, const string& prevHash, const string& curr="COIN", const string& sig="");

    void displayBlock() const override;
    string calculateHash() const override;
    void tamperData(const string& newData);

    string getName() const override { return sender; }
    string getReceiver() const override { return receiver; }
    int getAmount() const override { return amount; }
    string getCurrency() const { return currency; }
    string getSignature() const { return signature; }
    string getBlockType() const override { return "TRANSACTION"; }
};

#endif

