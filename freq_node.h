#ifndef FREQNODE_H
#define FREQNODE_H

#include <unordered_map>
#include <boost/dynamic_bitset.hpp>
#include "encoding.pb.h"
#include "status.h"

// Node which is a building block of a Huffman tree
class FreqNode {

private:
    int freq;

protected:
    FreqNode(int freq);

public:
    int get_freq() const;
    virtual Status find_next_char(const boost::dynamic_bitset<>&,
                                  size_t&,
                                  char&) const = 0;
    virtual void encode_node(boost::dynamic_bitset<>, 
                             std::unordered_map<char, boost::dynamic_bitset<>>&) const = 0;
    virtual void to_proto(encode_utils::FreqNodeProto* proto_node) const = 0;
    virtual ~FreqNode();
};

#endif