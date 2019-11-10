#include "gtest/gtest.h"
#include <count_function_args.h>
//#include "Count.test"
#include <string>
#include <unordered_map>

TEST(Kek, TestingTest) {
    string my_str = "f()";
    auto ans = count_function_args(my_str);
    EXPECT_EQ(ans["f"], 0U);
    EXPECT_TRUE(ans.size() == 1 );
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
