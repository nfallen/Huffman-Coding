#include "inner_node.h"
#include <iostream>
#include <unordered_map>
#include <boost/dynamic_bitset.hpp>
#include "freq_node.h"

InnerNode::InnerNode(std::shared_ptr<FreqNode> l, 
                     std::shared_ptr<FreqNode> r) 
    : FreqNode(l->get_freq() + r->get_freq()), 
      lc{l}, 
      rc{r} {}

char InnerNode::find_next_char(const boost::dynamic_bitset<>& encoded_bits,
                               int& bit_index) const {
    if (encoded_bits[bit_index] == 0) {
        bit_index++;
        return lc->find_next_char(encoded_bits, bit_index);
    } else {
        bit_index++;
        return rc->find_next_char(encoded_bits, bit_index);
    }
}

void InnerNode::encode_node(boost::dynamic_bitset<> bits, 
                            std::unordered_map<char, boost::dynamic_bitset<>>& encodings) const {
    bits.push_back(false);
    lc->encode_node(bits, encodings);

    bits.pop_back();
    bits.push_back(true);
    rc->encode_node(bits, encodings);
}
