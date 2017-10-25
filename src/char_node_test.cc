#include "char_node.h"
#include "freq_node.h"
#include "gtest/gtest.h"

namespace {

TEST(CharNodeTest, ConstructorSetsVars) {
	CharNode cn('a', 2);
	EXPECT_EQ('a', cn.get_char());
	EXPECT_EQ(2, cn.get_freq());
}

TEST(CharNodeTest, ToProto) {
	CharNode cn('a', 2);
	encode_decode::FreqNodeProto proto;
	cn.to_proto(&proto);
	EXPECT_EQ(encode_decode::FreqNodeProto_Type_CHAR, proto.type());
	EXPECT_EQ('a', proto.c());
	EXPECT_EQ(2, proto.freq());
}
}