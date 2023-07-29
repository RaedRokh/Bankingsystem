#include <iostream>
#include <fstream>
#include <map>
#define MIN_BALANCE 500
using namespace std;
class Account {
private:
string firstName;
string lastName;
int id;
static int nextid;
float balance;
public:
Account(){}
Account(string f, string l, float b);
string getfirstName(){return firstName;}
string getlastName(){return lastName;}
int getid(){return id;}
float getbalance(){return balance;}
static int getlastid(){return nextid;}
static void setlastid(int id){nextid=id;}
void deposit(float amount);
void withdraw(float amount);
friend ostream & operator<<(ostream &o,Account &acc);
friend ofstream & operator<<(ofstream &file, Account &acc);
friend ifstream & operator>>(ifstream &file,Account &acc);
    };
int Account::nextid=0;
Account::Account(string f, string l, float b){
    try{
nextid++;
firstName=f;
lastName=l;
if (b< MIN_BALANCE){
    throw 200;
}
else {balance=b;};}
catch(...){
cout<<"Insufficient Balance"<<endl;};
};
void Account::deposit(float amount){
balance+=amount;}
void Account::withdraw(float amount){
balance-=amount;}
ostream & operator<<(ostream &o,Account &acc){
o<<acc.firstName<<endl;
o<<acc.lastName<<endl;
o<<acc.id<<endl;
o<<acc.balance<<endl;
return o;}
ifstream & operator>>(ifstream& file,Account& acc){

    file>>acc.id;
    file>>acc.firstName;
    file>>acc.lastName;
    return file;
}
ofstream & operator<<(ofstream& file,Account& acc){

    file<<acc.id<<endl;
    file<<acc.firstName<<endl;
    file<<acc.lastName<<endl;
    return file;

}
class Bank{
private:
    map<int,Account> accounts;
public:
    Bank();
    Account openAccount(string firstName, string lastName, float balance);
    Account checkBalance(int id);
    Account deposit(int id, float amount);
    Account withdraw(int id, float amount);
    void closeAccount(int id);
    void showallAccounts();
    ~Bank();
    };
Bank::Bank(){
    Account acc;
    ifstream file;
    file.open("logs.txt");
    do {
    file>>acc;
    accounts.insert(pair<int,Account>(acc.getid(),acc));
    }while(!file.eof());
    Account::setlastid(acc.getid());
    file.close();
}
Account Bank::checkBalance(int id){
    return accounts.find(id)->second;
}
Account Bank::deposit(int id, float amount){
    Account acc=accounts.find(id)->second;
    acc.deposit(amount);
    return acc;
}
Account Bank::withdraw(int id, float amount){
    Account acc=accounts.find(id)->second;
    acc.withdraw(amount);
    return acc;
}
int main(){
    cout<<"test";
    return 0;}
