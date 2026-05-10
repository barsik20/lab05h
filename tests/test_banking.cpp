#include "banking/Account.h"
#include "banking/Transaction.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <stdexcept>

// Mock класс для Account
class AccountMock : public Account {
public:
    AccountMock(int id, int balance) : Account(id, balance) {}

    MOCK_CONST_METHOD0(GetBalance, int());
    MOCK_METHOD1(ChangeBalance, void(int diff));
    MOCK_METHOD0(Lock, void());
    MOCK_METHOD0(Unlock, void());
};

// ==================== Account Tests ====================

TEST(Account, SimpleTest) {
    Account acc(1, 100);

    EXPECT_EQ(acc.id(), 1);
    EXPECT_EQ(acc.GetBalance(), 100);

    EXPECT_THROW(acc.ChangeBalance(100), std::runtime_error);

    EXPECT_NO_THROW(acc.Lock());

    acc.ChangeBalance(100);

    EXPECT_EQ(acc.GetBalance(), 200);

    EXPECT_THROW(acc.Lock(), std::runtime_error);
}

TEST(Account, GetBalanceTest) {
    Account acc(2, 500);
    EXPECT_EQ(acc.GetBalance(), 500);
}

TEST(Account, LockUnlockTest) {
    Account acc(3, 1000);
    EXPECT_NO_THROW(acc.Lock());
    EXPECT_NO_THROW(acc.Unlock());
    EXPECT_NO_THROW(acc.Lock());
}

TEST(Account, ChangeBalanceNegativeTest) {
    Account acc(4, 1000);
    acc.Lock();
    acc.ChangeBalance(-300);
    EXPECT_EQ(acc.GetBalance(), 700);
    acc.Unlock();
}

TEST(Account, ChangeBalanceWithoutLockTest) {
    Account acc(5, 1000);
    EXPECT_THROW(acc.ChangeBalance(100), std::runtime_error);
}

// ==================== Transaction Tests ====================

TEST(Transaction, SimpleTest) {
    Transaction tr;

    Account ac1(1, 50);
    Account ac2(2, 500);

    tr.set_fee(100);

    EXPECT_EQ(tr.fee(), 100);

    EXPECT_THROW(tr.Make(ac1, ac1, 0), std::logic_error);
    EXPECT_THROW(tr.Make(ac1, ac2, -1), std::invalid_argument);
    EXPECT_THROW(tr.Make(ac1, ac2, 99), std::logic_error);

    EXPECT_FALSE(tr.Make(ac1, ac2, 199));
    EXPECT_FALSE(tr.Make(ac2, ac1, 500));
    EXPECT_TRUE(tr.Make(ac2, ac1, 300));
}

TEST(Transaction, FeeTest) {
    Transaction tr;
    EXPECT_EQ(tr.fee(), 0);
    tr.set_fee(50);
    EXPECT_EQ(tr.fee(), 50);
}

TEST(Transaction, MakeWithFeeSuccessTest) {
    Transaction tr;
    tr.set_fee(10);
    
    Account ac1(1, 200);
    Account ac2(2, 100);
    
    EXPECT_TRUE(tr.Make(ac1, ac2, 100));
    EXPECT_EQ(ac1.GetBalance(), 90);
    EXPECT_EQ(ac2.GetBalance(), 200);
}

TEST(Transaction, MockTest) {
    using ::testing::Return;
    using ::testing::_;
    
    Transaction tr;
    tr.set_fee(100);
    
    AccountMock ac1(1, 50);
    AccountMock ac2(2, 500);
    
    // Установить, что GetBalance возвращает достаточно средств
    EXPECT_CALL(ac2, GetBalance())
        .WillRepeatedly(Return(500));
    
    EXPECT_CALL(ac1, GetBalance())
        .WillRepeatedly(Return(50));
    
    // Успешный перевод: с ac2 на ac1 300
    EXPECT_CALL(ac2, Lock()).Times(1);
    EXPECT_CALL(ac2, ChangeBalance(-400)).Times(1);  // -300 -100 fee
    EXPECT_CALL(ac2, Unlock()).Times(1);
    
    EXPECT_CALL(ac1, Lock()).Times(1);
    EXPECT_CALL(ac1, ChangeBalance(300)).Times(1);
    EXPECT_CALL(ac1, Unlock()).Times(1);
    
    EXPECT_TRUE(tr.Make(ac2, ac1, 300));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}