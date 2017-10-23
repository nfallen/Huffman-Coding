#include "inner_node.h"
#include "char_node.h"
#include "freq_node.h"
#include "gtest/gtest.h"

namespace {
class InnerNodeTest : public ::testing::Test {

};

TEST(InnerNodeTest, ConstructorSetsVars) {
	std::shared_ptr<CharNode> cn1{new CharNode('a', 1)};
    std::shared_ptr<CharNode> cn2{new CharNode('b', 1)};

    InnerNode in = InnerNode(cn1, cn2);
	EXPECT_EQ(2, in.get_freq());
}
}