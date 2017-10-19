#include "char_node.h"
#include <iostream>
#include <unordered_map>
#include <boost/dynamic_bitset.hpp>
#include "freq_node.h"

CharNode::CharNode(char c, int freq) : FreqNode(freq), c{c} {}

char CharNode::get_char() const {
    return c;
}

char CharNode::find_next_char(const boost::dynamic_bitset<>& encoded_bits,
                              int& bit_index) const {
    return c;
}

void CharNode::encode_node(boost::dynamic_bitset<> bits, 
                           std::unordered_map<char, boost::dynamic_bitset<>>& encodings) const {
    encodings.emplace(c, bits);
}

