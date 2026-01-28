#ifndef BASEBLOCK_H
#define BASEBLOCK_H

#include "AbstractBlock.h"
#include <string>
using namespace std;

class BaseBlock : public AbstractBlock {
protected:
    string data;

    string getCurrentTime();

public:
    BaseBlock(int idx, const string& prevHash);

    virtual void displayBlock() const = 0;
    virtual string calculateHash() const = 0;

    virtual string getBlockType() const = 0;
    virtual string getName() const { return ""; }
    virtual string getReceiver() const { return ""; }
    virtual int getAmount() const { return 0; }

    virtual void tamperData(const string& newData) = 0;
};

#endif

