#include "BaseBlock.h"
#include <ctime>

BaseBlock::BaseBlock(int idx, const string& prevHash)
    : AbstractBlock(idx, prevHash, getCurrentTime()) {
}

string BaseBlock::getCurrentTime() {
    time_t now = time(0);
    return ctime(&now);
}



