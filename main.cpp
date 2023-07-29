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

nextid++;
id=nextid;
firstName=f;
lastName=l;
balance=b;}
void Account::deposit(float amount){
balance+=amount;}
void Account::withdraw(float amount){
    try{
    if (balance-amount>MIN_BALANCE){
balance-=amount;}
else{
    throw 200;
    };}
catch(...){
    cout<<"Insufficient balance"<<endl;
}}
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
    file.open("logs.data");
    while(!file.eof()){
    file>>acc;
    accounts.insert(pair<int,Account>(acc.getid(),acc));
    };
    Account::setlastid(acc.getid());
    file.close();

}
Account Bank::openAccount(string firstName, string lastName, float balance){
Account acc(firstName,lastName,balance);
accounts.insert(pair<int,Account>(acc.getid(),acc));
return acc;}
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
void Bank::showallAccounts(){
    map<int,Account>::iterator itr ;
    for (itr=accounts.begin(); itr != accounts.end(); itr++){
        cout<<"Account ID:"<<itr->first<<endl<<" Account Details:"<<itr->second<<endl;
    }
}
void Bank::closeAccount(int id){
accounts.erase(id);
}
Bank::~Bank(){
    ofstream file;
    file.open("logs.data",ios::trunc);
    map<int,Account>::iterator itr;
    for (itr=accounts.begin(); itr!=accounts.end(); itr++){
        file<<itr->second;
    }
    file.close();
}
int main(){
    Account a("a","b",700);
    Account b("a","c",100);
    cout<<a;
    cout<<b;
    a.deposit(100);
    b.withdraw(500);
        cout<<a;
    cout<<b;

    return 0;}
