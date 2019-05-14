
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "example.c"

using namespace ::testing;
using ::testing::Return;

/* Mock infrastructure */

class UTMock {
  public:
    virtual ~UTMock() {}
    MOCK_METHOD0(EC_CounterInc, void());
    MOCK_METHOD0(EC_CounterGet, uint32_t());
    MOCK_METHOD1(EC_Factorial, uint32_t(uint32_t));
};

class TestFixture : public ::testing::Test {
  public:
    TestFixture() { _ut_mock.reset(new ::testing::NiceMock<UTMock>()); }
    virtual ~TestFixture() { _ut_mock.reset(); }
    virtual void SetUp() {}
    virtual void TearDown() {}

    static std::unique_ptr<UTMock> _ut_mock;
};

class SubTestFixture : public TestFixture {
  public:
    virtual void SetUp() { 
        printf("SubTestFixture SetUp!\n");
    }
    virtual void TearDown() {}
};

std::unique_ptr<UTMock> TestFixture::_ut_mock;

void EC_CounterInc() { TestFixture::_ut_mock->EC_CounterInc(); }
uint32_t EC_CounterGet() { return TestFixture::_ut_mock->EC_CounterGet(); }
uint32_t EC_Factorial(uint32_t n) {
    return TestFixture::_ut_mock->EC_Factorial(n);
}

/* Basic tests */
TEST(UT_PowerOf, PositiveVal) {
    ASSERT_EQ(25, PowerOf(5, 2));
    ASSERT_EQ(27, PowerOf(3, 3));
    ASSERT_GE(25, 25);
    ASSERT_GT(26, 25);
    ASSERT_LE(26, 30);
    ASSERT_LT(26, 30);
    ASSERT_NE(1, 2);
    ASSERT_NEAR(15, 18, 3); /* Within range of 3*/
    ASSERT_NEAR(18, 15, 3); /* Within range of 3*/
    ASSERT_STREQ("abc", "abc");
    ASSERT_TRUE(1 + 1 == 2);
    ASSERT_FALSE(1 + 1 == 1);
}

TEST(UT_PowerOf, NegativeVal) { 
    ASSERT_EQ(9, PowerOf(-3, 2)); 
    ASSERT_NO_THROW(PowerOf(-3, 2)); 
}

/* Test Disabled */
TEST(DISABLED_UT_Power, FailTest) { 
    ASSERT_EQ(10, PowerOf(-3, 2)); 
}

/* PRED* -> Checks that a function returns true 
for a given set of parameters */
TEST(UT_IsOdd, basicTest) {
    ASSERT_PRED1(IsOdd, 3);
}

/* Modifying global var during the test */
TEST(UT_GlobalVar, basicTest) {
    ExampleGlobalVar = 2;
    ASSERT_EQ(2, GlobalVar());
    ASSERT_EQ(2, ExampleGlobalVar);
}

/* Tests using mocks */
TEST_F(TestFixture, basicTest) {
    /* Test 1 - even*/
    EXPECT_CALL(*_ut_mock, EC_CounterGet())
        .Times(2)
        .WillOnce(Return(4))
        .WillOnce(Return(5));
    EXPECT_CALL(*_ut_mock, EC_CounterInc()).Times(1);
    // EXPECT_CALL(*_ut_mock, EC_Factorial(_))
    //     .Times(0);

    ASSERT_EQ(5, CounterCoreExample());

    /* Test 2 - odd*/
    EXPECT_CALL(*_ut_mock, EC_CounterGet())
        .Times(1)
        .WillOnce(Return(3));
    EXPECT_CALL(*_ut_mock, EC_CounterInc());
    EXPECT_CALL(*_ut_mock, EC_Factorial(5))
        .Times(1)
        .WillOnce(Return(120));

    ASSERT_EQ(120, CounterCoreExample());
}

/* Test using actions */
static uint32_t action_var = 0;

ACTION_P2(my_action, param1, param2) { 
    action_var = param1 * param2;
}

TEST_F(TestFixture, basicTest2) {
    /* Test 1 - OK*/

    EXPECT_CALL(*_ut_mock, EC_CounterGet())
        .Times(2)
        .WillRepeatedly(DoAll(my_action(2, 1), Return(100)));
    EXPECT_CALL(*_ut_mock, EC_CounterInc()).Times(1);

    ASSERT_EQ(100, CounterCoreExample());
    ASSERT_EQ(2, action_var);
}

/* Test using SubFixture */
TEST_F(SubTestFixture, subBasicTest) {
    /* Test 1 - OK*/
    EXPECT_CALL(*_ut_mock, EC_CounterGet())
        .Times(2)
        .WillRepeatedly(Return(20));
    EXPECT_CALL(*_ut_mock, EC_CounterInc()).Times(1);

    ASSERT_EQ(20, CounterCoreExample());
}

/* Main */
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}