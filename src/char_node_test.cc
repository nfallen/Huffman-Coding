#include "char_node.h"
#include "freq_node.h"
#include "gtest/gtest.h"

namespace {
class CharNodeTest : public ::testing::Test {

};

TEST(CharNodeTest, ConstructorSetsVars) {
	CharNode cn('a', 2);
	EXPECT_EQ('a', cn.get_char());
	EXPECT_EQ(2, cn.get_freq());
}
}