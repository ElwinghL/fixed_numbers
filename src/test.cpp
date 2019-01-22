#include "gtest/gtest.h"

#include "fixed.h"

TEST(fixedNumberCreation, fromFloat) {
    fp::fixed<8, 8> test(static_cast<float>(1.0));
    EXPECT_EQ(256, test.value);
}

TEST(fixedNumberCreation, fromFloat2) {
    fp::fixed<16, 16> test(static_cast<float>(1.0));
    EXPECT_EQ(65536, test.value);
}


TEST(fixedNumberCreation, fromDouble) {
    fp::fixed<8, 8> test(static_cast<double>(1.0));
    EXPECT_EQ(256, test.value);
}

TEST(fixedNumberCreation, fromDouble2) {
    fp::fixed<16, 16> test(static_cast<double>(1.0));
    EXPECT_EQ(65536, test.value);
}

TEST(fixedNumberCreation, fromCopy) {
    fp::Q_8_8 test(1.0);
    fp::Q_8_8 testCopied(test);
    EXPECT_EQ(256, testCopied.value);
}

TEST(fixedNumberCreation, fromSmallerCopy) {
    fp::Q_8_8 test(1.0);
    fp::Q_16_16 testCopied(test);
    EXPECT_EQ(65536, testCopied.value);
}

TEST(fixedNumberCreation, constructCopy) {
    fp::Q_8_8 test(1.0);
    fp::Q_8_8 testCopied(test);
    EXPECT_EQ(256, testCopied.value);
}

TEST(fixedNumberCreation, constructSmallerCopy) {
    fp::Q_8_8 test(1.0);

    fp::Q_16_16 testCopied(test);
    EXPECT_EQ(65536, testCopied.value);
}

TEST(fixedNumberOperations, plusFromFloat) {
    fp::Q_8_8 test(1.0);
    test += static_cast<float>(1.0);

    EXPECT_EQ(512, test.value);
}

TEST(fixedNumberOperations, plusFromDouble) {
    fp::Q_8_8 test(1.0);
    test += static_cast<double>(1.0);

    EXPECT_EQ(512, test.value);
}
TEST(fixedNumberOperations, plusFromOne) {
    fp::Q_8_8 test(1.0);
    fp::Q_8_8 test2(1.0);

    test+=test2;
    EXPECT_EQ(512, test.value);
}

TEST(fixedNumberOperations, plusFromSmallerOne) {
    fp::Q_16_16 test(1.0);
    fp::Q_8_8 test2(1.0);

    test+=test2;
    EXPECT_EQ(131072, test.value);
}

TEST(fixedNumberOperations, minusFromFloat) {
    fp::Q_8_8 test(2.0);
    test -= static_cast<float>(1.0);

    EXPECT_EQ(256, test.value);
}

TEST(fixedNumberOperations, minusFromDouble) {
    fp::Q_8_8 test(2.0);
    test -= static_cast<double>(1.0);

    EXPECT_EQ(256, test.value);
}

TEST(fixedNumberOperations, minusFromOne) {
    fp::Q_8_8 test(2.0);
    fp::Q_8_8 test2(1.0);

    test-=test2;
    EXPECT_EQ(256, test.value);
}

TEST(fixedNumberOperations, minusFromSmallerOne) {
    fp::Q_16_16 test(2.0);
    fp::Q_8_8 test2(1.0);

    test -= test2;
    EXPECT_EQ(65536, test.value);
}


TEST(fixedNumberOperations, timeFromFloat) {
    fp::Q_8_8 test(1.0);
    test *= static_cast<float>(2.0);

    EXPECT_EQ(512, test.value);
}

TEST(fixedNumberOperations, timeFromDouble) {
    fp::Q_8_8 test(1.0);
    test *= static_cast<double>(2.0);

    EXPECT_EQ(512, test.value);
}

TEST(fixedNumberOperations, timeForOne) {
    fp::Q_8_8 test(1.0);
    fp::Q_8_8 test2(2.0);

    test*=test2;

    EXPECT_EQ(512, test.value);
}

TEST(fixedNumberOperations, timefromSmallerOne) {
    fp::Q_8_8 test(1.0);
    fp::Q_16_16 test2(2.0);

    test2*=test;

    EXPECT_EQ(131072, test2.value);
}

TEST(fixedNumberOperations, divFromFloat) {
    fp::Q_8_8 test(1.0);
    test /= static_cast<float>(2.0);

    EXPECT_EQ(128, test.value);
}

TEST(fixedNumberOperations, divFromDouble) {
    fp::Q_8_8 test(1.0);
    test /= static_cast<double>(2.0);

    EXPECT_EQ(128, test.value);
}

TEST(fixedNumberOperations, divFromOne) {
    fp::Q_8_8 test(1.0);
    fp::Q_8_8 test2(0.5);
    test /= test2;

    EXPECT_EQ(512, test.value);
}

TEST(fixedNumberOperations, divFromSmallerOne) {
    fp::Q_16_16 test(1.0);
    fp::Q_8_8 test2(0.5);
    test /= test2;

    EXPECT_EQ(131072, test.value);
}

TEST(fixedNumberExceptions,constrOverflow) {
    try {
        fp::fixed<0,1> test(1.0);
        EXPECT_TRUE(false);
    } catch (std::overflow_error& e) {
        EXPECT_TRUE(true);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
