#include "AccountBlock.h"
#include <iostream>
#include <sstream>

using namespace std;

AccountBlock::AccountBlock(int idx, const string& accName, const string& accDOB, const string& accGmail,
                           int accNum, int bal, const string& prevHash, const string& currency)
: BaseBlock(idx, prevHash), name(accName), dob(accDOB), gmail(accGmail), accountNumber(accNum)
{
    balances[currency] = bal;
    // simple simulation: privateKey = name reversed + accountNumber
    stringstream ss; ss << accName << accNum; privateKey = ss.str();
    currentHash = calculateHash();
}

int AccountBlock::getBalance(const string& currency) const {
    map<string,int>::const_iterator it = balances.find(currency);
    if(it != balances.end()) return it->second;
    return 0;
}

void AccountBlock::tamperData(const string& newData) {
    name = newData;
    currentHash = calculateHash();
    markTampered();
}

void AccountBlock::displayBlock() const {
    cout << "\n----------------------------";
    cout << "\nBlock #: " << index;
    cout << "\nType: ACCOUNT";
    cout << "\nName: " << name;
    cout << "\nDOB: " << dob;
    cout << "\nGmail: " << gmail;
    cout << "\nAccount #: " << accountNumber;
    for(map<string,int>::const_iterator it = balances.begin(); it != balances.end(); ++it)
        cout << "\nBalance (" << it->first << "): " << it->second;
    cout << "\nPrivate Key: " << privateKey;
    cout << "\nPrevious Hash: " << previousHash;
    cout << "\nCurrent Hash: " << currentHash;
    if (tampered) cout << "\n! Block Tampered!";
    cout << "\n----------------------------\n";
}

string AccountBlock::calculateHash() const {
    stringstream ss;
    ss << index << timestamp << name << dob << gmail << accountNumber;
    for(map<string,int>::const_iterator it = balances.begin(); it != balances.end(); ++it)
        ss << it->first << it->second;
    ss << previousHash;
    unsigned long hash = 0;
    string data = ss.str();
    for(size_t i=0; i<data.length(); i++) hash = hash*31 + data[i];
    return to_string(hash);
}

