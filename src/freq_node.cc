#include "freq_node.h"

FreqNode::FreqNode(int freq) :freq{freq} {}

int FreqNode::get_freq() const {
    return freq;
}

FreqNode::~FreqNode() {}