#include "gtest/gtest.h"
#include "Rpn.test"

//
//TEST(CreatingRpn, FirstTest) {
//    string test_str = "1+f()+g(a)";
//    auto ans = make_rpn(test_str);
//    EXPECT_FALSE(ans.empty());
//}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
