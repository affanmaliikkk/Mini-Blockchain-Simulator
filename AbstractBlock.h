#ifndef ABSTRACTBLOCK_H
#define ABSTRACTBLOCK_H

#include <string>
using namespace std;

class AbstractBlock {
protected:
    int index;
    string timestamp;
    string previousHash;
    string currentHash;
    bool tampered;

public:
    AbstractBlock(int idx, const string& prevHash, const string& time)
        : index(idx), timestamp(time), previousHash(prevHash), tampered(false) {}

    virtual void displayBlock() const = 0;
    virtual string calculateHash() const = 0;

    string getCurrentHash() const { return currentHash; }
    string getPreviousHash() const { return previousHash; }
    string getTimestamp() const { return timestamp; }

    void markTampered() { tampered = true; }

    virtual ~AbstractBlock() {}
};

#endif

