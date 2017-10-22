#include "char_node.h"
#include <iostream>
#include <unordered_map>
#include <boost/dynamic_bitset.hpp>
#include "encoding.pb.h"
#include "freq_node.h"
#include "status.h"

CharNode::CharNode(char c, int freq) : FreqNode(freq), c{c} {}

char CharNode::get_char() const {
    return c;
}

Status CharNode::find_next_char(const boost::dynamic_bitset<>& encoded_bits,
                                size_t& bit_index,
                                char& found) const {
    found = c;
    return Status::kOk;
}

void CharNode::encode_node(boost::dynamic_bitset<> bits, 
                           std::unordered_map<char, boost::dynamic_bitset<>>& encodings) const {
    encodings.emplace(c, bits);
}

void CharNode::to_proto(encode_utils::FreqNodeProto* proto_node) const {
    proto_node->set_type(encode_utils::FreqNodeProto_Type_CHAR);
    proto_node->set_c(static_cast<google::protobuf::int32>(c));
    proto_node->set_freq(this->get_freq());
}