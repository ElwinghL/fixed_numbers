#include "gtest/gtest.h"

#include "fixed.h"


/*
   ____                         _                           _
  / ___|   ___    _ __    ___  | |_   _ __   _   _    ___  | |_    ___    _ __   ___
 | |      / _ \  | '_ \  / __| | __| | '__| | | | |  / __| | __|  / _ \  | '__| / __|
 | |___  | (_) | | | | | \__ \ | |_  | |    | |_| | | (__  | |_  | (_) | | |    \__ \
  \____|  \___/  |_| |_| |___/  \__| |_|     \__,_|  \___|  \__|  \___/  |_|    |___/

 */
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
TEST(fixedNumberCreation, fromCopy2) {
    fp::Q_8_8 test(1.0);
    fp::fixed<16,16> testCopied(test);
    EXPECT_EQ(65536, testCopied.value);
}

TEST(fixedNumberCreation, fromSmallerCopy) {
    fp::Q_8_8 test(1.0);
    fp::Q_16_16 testCopied(test);
    EXPECT_EQ(65536, testCopied.value);
}

TEST(fixedNumberCreation, constructCopy) {
    fp::Q_8_8 test(1.0);
    fp::Q_8_8 testCopied = test;
    EXPECT_EQ(256, testCopied.value);
}

TEST(fixedNumberCreation, constructSmallerCopy) {
    fp::Q_8_8 test(1.0);
    fp::Q_16_16 testCopied = test;
    EXPECT_EQ(65536, testCopied.value);
}
/*
     _                  _                                      _
    / \     ___   ___  (_)   __ _   _ __ ___     ___   _ __   | |_
   / _ \   / __| / __| | |  / _` | | '_ ` _ \   / _ \ | '_ \  | __|
  / ___ \  \__ \ \__ \ | | | (_| | | | | | | | |  __/ | | | | | |_
 /_/   \_\ |___/ |___/ |_|  \__, | |_| |_| |_|  \___| |_| |_|  \__|
                            |___/
   ___                                  _
  / _ \   _ __     ___   _ __    __ _  | |_    ___    _ __   ___
 | | | | | '_ \   / _ \ | '__|  / _` | | __|  / _ \  | '__| / __|
 | |_| | | |_) | |  __/ | |    | (_| | | |_  | (_) | | |    \__ \
  \___/  | .__/   \___| |_|     \__,_|  \__|  \___/  |_|    |___/
         |_|
 */
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

    test += test2;
    EXPECT_EQ(512, test.value);
}

TEST(fixedNumberOperations, plusFromSmallerOne) {
    fp::Q_16_16 test(1.0);
    fp::Q_8_8 test2(1.0);

    test += test2;
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

    test -= test2;
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

    test *= test2;

    EXPECT_EQ(512, test.value);
}

TEST(fixedNumberOperations, timefromSmallerOne) {
    fp::Q_8_8 test(1.0);
    fp::Q_16_16 test2(2.0);

    test2 *= test;

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
/*
   ____                                                      _
  / ___|   ___    _ __ ___    _ __     __ _   _ __    __ _  (_)  ___    ___    _ __
 | |      / _ \  | '_ ` _ \  | '_ \   / _` | | '__|  / _` | | | / __|  / _ \  | '_ \
 | |___  | (_) | | | | | | | | |_) | | (_| | | |    | (_| | | | \__ \ | (_) | | | | |
  \____|  \___/  |_| |_| |_| | .__/   \__,_| |_|     \__,_| |_| |___/  \___/  |_| |_|
                             |_|
   ___                                  _
  / _ \   _ __     ___   _ __    __ _  | |_    ___    _ __   ___
 | | | | | '_ \   / _ \ | '__|  / _` | | __|  / _ \  | '__| / __|
 | |_| | | |_) | |  __/ | |    | (_| | | |_  | (_) | | |    \__ \
  \___/  | .__/   \___| |_|     \__,_|  \__|  \___/  |_|    |___/
         |_|
 */
TEST(fixedNumberComparaison, equal) {
    fp::Q_8_8 test(1.0);
    fp::Q_16_16 test2(1.0);
    fp::Q_8_8 test3(1.0001);
     
    EXPECT_TRUE(test == test2);
    EXPECT_TRUE(test == test3);
}
TEST(fixedNumberComparaison, negEqual) {
    fp::Q_8_8 test(-1.0);
    fp::Q_16_16 test2(-1.0);
    fp::Q_8_8 test3(-1.000001);

    EXPECT_TRUE(test == test2);
    EXPECT_FALSE(test == test3);
}
TEST(fixedNumberComparaison, inEqual) {
    fp::Q_8_8 test(1.0);
    fp::Q_16_16 test2(2.0);
	fp::Q_8_8 test3(1.00);
    fp::Q_16_16 test4(1.01);

    EXPECT_FALSE(test == test2);
    EXPECT_TRUE(test != test2);
    EXPECT_TRUE(test3 != test4);
}

TEST(fixedNumberComparaison, negInEqual) {
    fp::Q_8_8 test(-1.0);
    fp::Q_16_16 test2(-2.0);
	fp::Q_8_8 test3(-1.01);
    fp::Q_16_16 test4(-1.00);

    EXPECT_FALSE(test == test2);
    EXPECT_TRUE(test != test2);
    EXPECT_TRUE(test3 != test4);
}
TEST(fixedNumberComparaison, inferior) {
    fp::Q_8_8 test(1.0);
    fp::Q_16_16 test2(2.0);

    EXPECT_TRUE(test < test2);
    EXPECT_FALSE(test < test);
}
TEST(fixedNumberComparaison, negInferior) {
    fp::Q_8_8 test(-2.0);
    fp::Q_16_16 test2(-1.0);

    EXPECT_TRUE(test < test2);
    EXPECT_FALSE(test < test);
}
TEST(fixedNumberComparaison, superior) {
    fp::Q_8_8 test(1.0);
    fp::Q_16_16 test2(2.0);

    EXPECT_TRUE(test2 > test);
    EXPECT_FALSE(test > test);
}
TEST(fixedNumberComparaison, negSuperior) {
    fp::Q_8_8 test(-2.0);
    fp::Q_16_16 test2(-1.0);

    EXPECT_TRUE(test2 > test);
    EXPECT_FALSE(test > test);
}
TEST(fixedNumberComparaison, inferiorEqual) {
    fp::Q_8_8 test(1.0);
    fp::Q_16_16 test2(2.0);

    EXPECT_TRUE(test <= test2);
    EXPECT_TRUE(test <= test);
}
TEST(fixedNumberComparaison, negInferiorEqual) {
    fp::Q_8_8 test(-2.0);
    fp::Q_16_16 test2(-1.0);

    EXPECT_TRUE(test <= test2);
    EXPECT_TRUE(test <= test);
}
TEST(fixedNumberComparaison, superiorEqual) {
    fp::Q_8_8 test(1.0);
    fp::Q_16_16 test2(2.0);

    EXPECT_TRUE(test2 >= test);
    EXPECT_TRUE(test >= test);
}
TEST(fixedNumberComparaison, negSuperiorEqual) {
    fp::Q_8_8 test(-2.0);
    fp::Q_16_16 test2(-1.0);

    EXPECT_TRUE(test2 >= test);
    EXPECT_TRUE(test >= test);
}
/*
  _____                          _     _
 |  ___|  _   _   _ __     ___  | |_  (_)   ___    _ __    ___
 | |_    | | | | | '_ \   / __| | __| | |  / _ \  | '_ \  / __|
 |  _|   | |_| | | | | | | (__  | |_  | | | (_) | | | | | \__ \
 |_|      \__,_| |_| |_|  \___|  \__| |_|  \___/  |_| |_| |___/

 */

TEST(fixedNumberFunctions, sqrt) {
    fp::Q_8_8 test(4.0);
    fp::Q_8_8 test2(sqrt(test));

    EXPECT_EQ(512,test2.value);
}

TEST(fixedNumberFunctions, sqrt2) {
    fp::Q_8_8 test(4.0);
    fp::Q_16_16 test2(sqrt(test));

    EXPECT_EQ(131072,test2.value);
}

/*
  _____                                _     _
 | ____| __  __   ___    ___   _ __   | |_  (_)   ___    _ __    ___
 |  _|   \ \/ /  / __|  / _ \ | '_ \  | __| | |  / _ \  | '_ \  / __|
 | |___   >  <  | (__  |  __/ | |_) | | |_  | | | (_) | | | | | \__ \
 |_____| /_/\_\  \___|  \___| | .__/   \__| |_|  \___/  |_| |_| |___/
                              |_|
 */

TEST(fixedNumberExceptions, constrOverflow) {
    EXPECT_THROW(({fp::fixed<0, 1> test(1.0);}),std::overflow_error);

}
TEST(fixedNumberExceptions, copyOverflow) {
    fp::fixed<1, 1> test(1.0);
    EXPECT_THROW(({fp::fixed<0, 1> test1(test);}),std::overflow_error);

}
TEST(fixedNumberExceptions, div0) {
    fp::Q_8_8 test(1.0);
    fp::Q_8_8 test2(0.0);
    EXPECT_THROW(({test/=test2;}), std::overflow_error);
}

TEST(fixedNumberExceptions, sqrt) {
    fp::Q_8_8 test(-4.0);
    EXPECT_THROW(({fp::fixed<16, 16> test2(sqrt(test));}), std::overflow_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
