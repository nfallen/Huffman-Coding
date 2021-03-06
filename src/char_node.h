#ifndef CHARNODE_H
#define CHARNODE_H

#include <unordered_map>
#include <boost/dynamic_bitset.hpp>
#include "encoding.pb.h"
#include "freq_node.h"
#include "status.h"

// Leaf node of a Huffman tree
// Represents a character and its frequency in the document being encoded
class CharNode : public FreqNode {
private:
    char c;
public:
    CharNode(char c, int freq);
    char get_char() const;
    Status find_next_char(const boost::dynamic_bitset<>&,
                          size_t&,
                          char&) const final;
    void encode_node(boost::dynamic_bitset<>, 
                     std::unordered_map<char, boost::dynamic_bitset<>>&) const final;
    void to_proto(encode_decode::FreqNodeProto* proto_node) const final;
};

#endif