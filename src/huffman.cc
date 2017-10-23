#include <iostream>
#include <iomanip>
#include <string>
#include "encode_decode.h"
#include "encoding.pb.h"
#include "status.h"

int main() {
    std::string s = "helloworld";
    std::unordered_map<char, int> m = encode_decode::count_freq(s);
    std::shared_ptr<FreqNode> pre_root = encode_decode::create_optimal_hufftree(s);

    encode_decode::FreqNodeProto proto_root;
    pre_root->to_proto(&proto_root);

	std::cout<<"Proto: \n"<<proto_root.DebugString()<<"\n";

    std::shared_ptr<FreqNode> root;
    Status status = encode_decode::from_proto(proto_root, root);
    if (status == Status::kInvalid) {
    	std::cout<<"Invalid Proto";
    	return 1;
    }

    std::unordered_map<char, boost::dynamic_bitset<>> encodings = encode_decode::encode_tree(*root);

	std::cout<<"Encoding Size "<<encodings.size()<<"\n";

	for (auto elt = encodings.cbegin(); elt != encodings.cend(); ++elt) {
		std::cout<<"Char: "<<elt->first<<"Bitstring: "<<elt->second<<"\n";
	}
	std::cout<<"Root Freq"<<root->get_freq()<<"\n";

	boost::dynamic_bitset<> encoding;
	status = encode_decode::encode_string(encodings, s, encoding);
	if (status == Status::kInvalid) {
		std::cout<<"Char in String Not In Set of Encodable Chars\n";
		return 1;
	} else {
		std::cout<<"Encoding: "<<encoding<<"\n";
	}

	std::string decoding;
	status = encode_decode::decode_bits(*root, encoding, decoding);
	if (status == Status::kInvalid) {
		std::cout<<"Invalid Bits Cannot Be Decoded\n";
		return 1;
	} else {
		std::cout<<"Decoding: "<<decoding<<"\n";
	}

    return 0;
}