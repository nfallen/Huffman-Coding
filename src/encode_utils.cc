#include "encode_utils.h"
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include "char_node.h"
#include "encoding.pb.h"
#include "freq_node.h"
#include "inner_node.h"

namespace encode_utils {

	class Comparator {
	public:
	    bool operator()(const std::shared_ptr<FreqNode>& a, 
	    				const std::shared_ptr<FreqNode>& b) {
	        return (a->get_freq() > b->get_freq());
	    }
	};

	std::unordered_map<char, int> count_freq(const std::string& s) {
		std::unordered_map<char, int> counter;
		for (auto it = s.begin(); it != s.end(); ++it) {
			std::unordered_map<char,int>::iterator res = counter.find(*it);
			if (res == counter.end()) {
				counter.emplace(*it, 1);
			} else {
				res->second = res->second + 1;
			}
		}
		return counter;
	}

	std::shared_ptr<FreqNode> create_optimal_hufftree(const std::string& s) {

		std::unordered_map<char, int>&& counter = count_freq(s);

		// We use shared_ptr because the priority queue only provides 
		// access to the top element as a const reference.
		// Thus, it is impossible to move the ownership of the node or its 
		// child nodes.
		// Alternatively, we could copy the node out of the queue,
		// but as we combine nodes into a tree throughout the algorithm,
		// this would entail copying the entire tree, 
		// making the algorithm O(n^2) rather than O(n lg n).
		std::priority_queue<std::shared_ptr<FreqNode>, 
							std::vector<std::shared_ptr<FreqNode>>, 
							Comparator> minheap;
		for (auto it = counter.begin(); it != counter.end(); ++it) {
			// Allocate each character node on the heap
			minheap.push(std::shared_ptr<CharNode>{
				new CharNode(it->first, it->second)});
		}

		int numchars = minheap.size();
		for (int i = 1; i < numchars; ++i) {
			std::shared_ptr<FreqNode> left(minheap.top());
			minheap.pop();
			std::shared_ptr<FreqNode> right(minheap.top());
			minheap.pop();
			minheap.push(std::shared_ptr<InnerNode>{
				new InnerNode(left, right)});
		}
		std::shared_ptr<FreqNode> root(minheap.top());
		minheap.pop();
		return root;
	}

	std::unordered_map<char, boost::dynamic_bitset<>> encode_tree(const FreqNode& root) {
		std::unordered_map<char, boost::dynamic_bitset<>> encodings;
		boost::dynamic_bitset<> bits;
		root.encode_node(bits, encodings);
		return encodings;
	}

	void concat_bitsets(boost::dynamic_bitset<>& bits1, 
						const boost::dynamic_bitset<>& bits2) {
		size_t orig_size = bits1.size();
		bits1.resize(orig_size + bits2.size());
		for (size_t i = 0; i < bits2.size(); i++) {
			bits1[orig_size + i] = bits2[i];
		}
	}

	Status encode_string(const std::unordered_map<char, boost::dynamic_bitset<>>& encodings,
					   	 const std::string& s,
					   	 boost::dynamic_bitset<>& bits) {
		for (auto it = s.begin(); it != s.end(); ++it) {
			std::unordered_map<char,boost::dynamic_bitset<>>::const_iterator res = encodings.find(*it);
			if (res == encodings.end()) {
				return Status::kInvalid;
			}
			concat_bitsets(bits, res->second);
		}
		return Status::kOk;
	}

	Status from_proto(const encode_utils::FreqNodeProto& proto_node,
	 			      std::shared_ptr<FreqNode>& node) {
		if (proto_node.type() == encode_utils::FreqNodeProto_Type_CHAR) {
			// TODO: convert to char
			google::protobuf::int32 int_c = proto_node.c();
			char c = static_cast<char>(int_c);
			int freq = proto_node.freq();
			node = std::shared_ptr<FreqNode>(new CharNode(c, freq));
			return Status::kOk;
		} else if (proto_node.type() == encode_utils::FreqNodeProto_Type_INNER) {
			std::shared_ptr<FreqNode> lc;
			std::shared_ptr<FreqNode> rc;
			if (from_proto(proto_node.lc(), lc) == Status::kOk &&
				from_proto(proto_node.rc(), rc) == Status::kOk) {
				node = std::shared_ptr<FreqNode>(new InnerNode(lc, rc));
				return Status::kOk;
			} else {
				return Status::kInvalid;
			}
		} else {
			return Status::kInvalid;
		}
	}

	Status decode_bits(const FreqNode& root,
					   const boost::dynamic_bitset<>& encoded_bits,
					   std::string& decoding) {
		size_t bit_index(0);
		while (bit_index < encoded_bits.size()) {
			char c;
			if (root.find_next_char(encoded_bits, bit_index, c) == Status::kOk) {
				decoding.push_back(c);
			} else {
				// An invalid status occurs if there are not enough bits 
				// in the bitset to reach a char node.
				return Status::kInvalid;
			}
		}
		return Status::kOk;
	}
}