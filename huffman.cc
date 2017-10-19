#include "encode_utils.h"
#include <iostream>
#include <iomanip>
#include <string>

int main() {
    std::string s = "helloworld";
    std::unordered_map<char, int> m = encode_utils::count_freq(s);
    std::shared_ptr<FreqNode> root = encode_utils::create_optimal_hufftree(s);
    std::unordered_map<char, boost::dynamic_bitset<>> encodings = encode_utils::encode_tree(*root);

	std::cout<<"Encoding Size "<<encodings.size()<<"\n";

	for (auto elt = encodings.cbegin(); elt != encodings.cend(); ++elt) {
		std::cout<<"Char: "<<elt->first<<"Bitstring: "<<elt->second<<"\n";
	}
	std::cout<<"Root Freq"<<root->get_freq()<<"\n";

	boost::dynamic_bitset<> encoding = encode_utils::encode_string(encodings, s);
	std::cout<<"Encoding: "<<encoding<<"\n";

	std::string decoding = encode_utils::decode_bits(*root, encoding);
	std::cout<<"Decoding: "<<decoding<<"\n";

    return 0;
}