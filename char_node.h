#ifndef CHARNODE_H
#define CHARNODE_H

#include "freq_node.h"
#include <unordered_map>
#include <boost/dynamic_bitset.hpp>

// Leaf node of a Huffman tree
// Represents a character and its frequency in the document being encoded
class CharNode : public FreqNode {
private:
    char c;
public:
    CharNode(char c, int freq);
    char get_char() const;
    char find_next_char(const boost::dynamic_bitset<>&,
                        size_t& bit_index) const final;
    void encode_node(boost::dynamic_bitset<>, 
                     std::unordered_map<char, boost::dynamic_bitset<>>&) const final;
};

#endif