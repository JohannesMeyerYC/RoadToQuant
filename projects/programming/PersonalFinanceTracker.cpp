#include <cstddef>
#include <iostream>
#include <fstream>

class Account{
    public:
        double AccountBalance;
        void AccountWithdraw(double Amount);
        void AccountInput(double Amount);
        double getBalance();
        double setBalance(double CurrentBalance);
};



void Account::AccountWithdraw(double Amount){
    double CurrentBalance = getBalance();
    CurrentBalance = CurrentBalance - Amount;
    setBalance(CurrentBalance);
    return;
}

void Account::AccountInput(double Amount){
    double CurrentBalance = getBalance();
    CurrentBalance = CurrentBalance + Amount;
    setBalance(CurrentBalance);
    return;
}

int main(){

    return 0;
}