#include "inner_node.h"
#include <iostream>
#include <unordered_map>
#include <boost/dynamic_bitset.hpp>
#include "encoding.pb.h"
#include "freq_node.h"
#include "status.h"

InnerNode::InnerNode(std::shared_ptr<FreqNode> l, 
                     std::shared_ptr<FreqNode> r) 
    : FreqNode(l->get_freq() + r->get_freq()), 
      lc{l}, 
      rc{r} {}

Status InnerNode::find_next_char(const boost::dynamic_bitset<>& encoded_bits,
                                 size_t& bit_index,
                                 char& found) const {
    if (bit_index >= encoded_bits.size()) {
        return Status::kInvalid;
    }else if (encoded_bits[bit_index] == 0) {
        bit_index++;
        lc->find_next_char(encoded_bits, bit_index, found);
        return Status::kOk;
    } else {
        bit_index++;
        rc->find_next_char(encoded_bits, bit_index, found);
        return Status::kOk;
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

void InnerNode::to_proto(encode_utils::FreqNodeProto* proto_node) const {
    proto_node->set_type(encode_utils::FreqNodeProto_Type_INNER);
    proto_node->set_freq(this->get_freq());
    encode_utils::FreqNodeProto* proto_lc = proto_node->mutable_lc();
    encode_utils::FreqNodeProto* proto_rc = proto_node->mutable_rc();
    lc->to_proto(proto_lc);
    rc->to_proto(proto_rc);
}
