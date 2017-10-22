#ifndef INNERNODE_H
#define INNERNODE_H

#include <unordered_map>
#include <boost/dynamic_bitset.hpp>
#include "encoding.pb.h"
#include "freq_node.h"
#include "status.h"

// Inner node of a Huffman tree
// Used to determine an optimal encoding for a document in the greedy algorithm
class InnerNode : public FreqNode {

private:
    std::shared_ptr<FreqNode> lc;
    std::shared_ptr<FreqNode> rc;

public:
    InnerNode(std::shared_ptr<FreqNode>, std::shared_ptr<FreqNode>);
    Status find_next_char(const boost::dynamic_bitset<>&,
                          size_t&,
                          char&) const final;
    void encode_node(boost::dynamic_bitset<>, 
                     std::unordered_map<char, boost::dynamic_bitset<>>&) const final;
    void to_proto(encode_utils::FreqNodeProto* proto_node) const final;
};

#endif