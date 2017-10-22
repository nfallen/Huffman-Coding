#include <iostream>
#include <iomanip>
#include <string>
#include "char_node.h"
#include "encode_utils.h"
#include "freq_node.h"
#include "inner_node.h"

bool test1() {
    std::shared_ptr<CharNode> cn1{new CharNode('a', 1)};
    std::shared_ptr<CharNode> cn2{new CharNode('b', 1)};

    InnerNode inner = InnerNode(cn1, cn2);
    return inner.get_freq() == 2; 
}

bool test2() {
    std::shared_ptr<CharNode> cn1{new CharNode('a', 1)};
    std::shared_ptr<CharNode> cn2{new CharNode('b', 2)};
    return cn2 > cn1; 
}

bool test3() {
    std::string s = "helloworld";
    std::unordered_map<char, int> counts = encode_utils::count_freq(s);
    return counts['o'] == 2;
}

bool test4() {
    std::string s = "helloworld";
    std::unordered_map<char, int> counts = encode_utils::count_freq(s);
    return counts['h'] == 1;
}

bool test5() {
    std::shared_ptr<CharNode> cn1{new CharNode('a', 1)};
    std::shared_ptr<CharNode> cn2{new CharNode('b', 2)};
    InnerNode inner = InnerNode(cn1, cn2);

    std::unordered_map<char, boost::dynamic_bitset<>> encodings = encode_utils::encode_tree(inner);

    return encodings.size() == 2;
}

int main() {
    std::cout << std::boolalpha;
    std::cout<<"Test 1: "<<test1()<<"\n";
    std::cout<<"Test 2: "<<test2()<<"\n";
    std::cout<<"Test 3: "<<test3()<<"\n";
    std::cout<<"Test 4: "<<test4()<<"\n";
    std::cout<<"Test 5: "<<test5()<<"\n";
    return 0;
}