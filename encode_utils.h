#ifndef ENCODE_UTILS
#define ENCODE_UTILS

#include <unordered_map>
#include <boost/dynamic_bitset.hpp>
#include "freq_node.h"
#include "encoding.pb.h"
#include "status.h"

namespace encode_utils {
	std::unordered_map<char, int> count_freq(const std::string&);
	std::shared_ptr<FreqNode> create_optimal_hufftree(const std::string&);
	Status encode_string(const std::unordered_map<char, boost::dynamic_bitset<>>&,
					   	 const std::string&,
					   	 boost::dynamic_bitset<>&);
	std::unordered_map<char, boost::dynamic_bitset<>> encode_tree(const FreqNode&);
	Status decode_bits(const FreqNode&,
					   const boost::dynamic_bitset<>&,
					   std::string&);
	Status from_proto(const encode_utils::FreqNodeProto& proto_node,
	 			      std::shared_ptr<FreqNode>& node);
}

#endif