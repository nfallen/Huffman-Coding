#include "inner_node.h"
#include "char_node.h"
#include "freq_node.h"
#include "gtest/gtest.h"

namespace {
class InnerNodeTest : public ::testing::Test {
protected:
	std::shared_ptr<FreqNode> cn1;
	std::shared_ptr<FreqNode> cn2;
	InnerNode in;

	InnerNodeTest() : cn1{new CharNode('a', 1)}, 
					  cn2{new CharNode('b', 2)},
					  in(InnerNode(cn1, cn2)) {}
};

TEST_F(InnerNodeTest, ConstructorSetsVars) {
	EXPECT_EQ(3, in.get_freq());
}

TEST_F(InnerNodeTest, LeftAndRightEncodings) {
	boost::dynamic_bitset<> bits;
	boost::dynamic_bitset<> bitsa;
	boost::dynamic_bitset<> bitsb;
	bitsa.push_back(false);
	bitsb.push_back(true);
	std::unordered_map<char, boost::dynamic_bitset<>> encodings;
	in.encode_node(bits, encodings);
	auto found_a = encodings.find('a');
	auto found_b = encodings.find('b');
	ASSERT_TRUE(found_a != encodings.end());
	ASSERT_TRUE(found_b != encodings.end());
	EXPECT_EQ(bitsa, found_a->second);
	EXPECT_EQ(bitsb, found_b->second);
}

TEST_F(InnerNodeTest, FindLeftChar) {
	boost::dynamic_bitset<> bits;
	bits.push_back(false);
	char c;
	size_t index(0);
	in.find_next_char(bits, index, c);
	EXPECT_EQ('a', c);
	EXPECT_EQ(1, index);
}

TEST_F(InnerNodeTest, FindRightCharIndexNonzero) {
	boost::dynamic_bitset<> bits;
	bits.push_back(false);
	bits.push_back(true);
	char c;
	size_t index(1);
	in.find_next_char(bits, index, c);
	EXPECT_EQ('b', c);
	EXPECT_EQ(2, index);
}

TEST_F(InnerNodeTest, ToProto) {
	encode_decode::FreqNodeProto proto;
	in.to_proto(&proto);
	EXPECT_EQ(encode_decode::FreqNodeProto_Type_INNER, proto.type());
	EXPECT_EQ(3, proto.freq());
	EXPECT_EQ('a', proto.lc().c());
	EXPECT_EQ(1, proto.lc().freq());
	EXPECT_EQ('b', proto.rc().c());
	EXPECT_EQ(2, proto.rc().freq());
}

}