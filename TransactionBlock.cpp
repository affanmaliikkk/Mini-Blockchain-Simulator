#include "TransactionBlock.h"
#include <iostream>
#include <sstream>

using namespace std;

TransactionBlock::TransactionBlock(int idx, const string& snd, const string& recv, int amt, const string& prevHash, const string& curr, const string& sig)
: BaseBlock(idx, prevHash), sender(snd), receiver(recv), amount(amt), currency(curr), signature(sig)
{
    currentHash = calculateHash();
}

void TransactionBlock::tamperData(const string& newData) {
    sender = newData;
    currentHash = calculateHash();
    markTampered();
}

void TransactionBlock::displayBlock() const {
    cout << "\n----------------------------";
    cout << "\nBlock #: " << index;
    cout << "\nType: TRANSACTION";
    cout << "\nSender: " << sender;
    cout << "\nReceiver: " << receiver;
    cout << "\nAmount: " << amount << " " << currency;
    cout << "\nSignature: " << signature;
    cout << "\nPrevious Hash: " << previousHash;
    cout << "\nCurrent Hash: " << currentHash;
    if(tampered) cout << "\n! Block Tampered!";
    cout << "\n----------------------------\n";
}

string TransactionBlock::calculateHash() const {
    stringstream ss;
    ss << index << timestamp << sender << receiver << amount << currency << signature << previousHash;
    unsigned long hash = 0;
    string data = ss.str();
    for(size_t i=0; i<data.length(); i++) hash = hash*31 + data[i];
    return to_string(hash);
}

