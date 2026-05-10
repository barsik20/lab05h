#include "Transaction.h"
#include "Account.h"

#include <stdexcept>

Transaction::Transaction() : fee_(0) {}

Transaction::~Transaction() {}

bool Transaction::Make(Account& from, Account& to, int summ) {
  if (summ < 0) {
    throw std::invalid_argument("sum can't be negative");
  }
  
  if (summ < 100) {
    throw std::logic_error("too small");
  }
  
  if (from.id() == to.id()) {
    throw std::logic_error("same account");
  }
  
  if (from.GetBalance() < summ + fee_) {
    return false;
  }
  
  if (!Debit(from, summ + fee_)) {
    return false;
  }
  
  Credit(to, summ);
  SaveToDataBase(from, to, summ);
  return true;
}

void Transaction::Credit(Account& account, int summ) {
  account.Lock();
  account.ChangeBalance(summ);
  account.Unlock();
}

bool Transaction::Debit(Account& account, int summ) {
  if (account.GetBalance() < summ) {
    return false;
  }
  
  account.Lock();
  try {
    account.ChangeBalance(-summ);
  } catch (...) {
    account.Unlock();
    throw;
  }
  account.Unlock();
  return true;
}

void Transaction::SaveToDataBase(Account& from, Account& to, int summ) {
  // Базовая реализация
}