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
o<<acc.id<<endl;
o<<acc.firstName<<endl;
o<<acc.lastName<<endl;
o<<acc.balance<<endl;
return o;}
ifstream & operator>>(ifstream& file,Account& acc){
    file>>acc.id;
    file>>acc.firstName;
    file>>acc.lastName;
    file>>acc.balance;
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
    void checkBalance(int id);
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
        if (!file){
        cout<<"File can't be opened"<<endl;
        return;
    }
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
void Bank::checkBalance(int id){
     cout<<" Account Details:"<<itr->second<<endl;
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
    if (!accounts.empty()){
    for (itr=accounts.begin(); itr != accounts.end(); itr++){
        cout<<" Account Details:"<<itr->second<<endl;
    }} else {cout<<"There's no accounts";}
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
    Bank ba;
    int choice;
    cout <<" Hello to the banking system"<<endl;
    cout<<" Select option"<<endl;
    do {

        cout<<"1. Create a new account"<<endl;
        cout<<"2. Check your account's balance"<<endl;
        cout<<"3. Deposit money"<<endl;
        cout<<"4. Withdraw money"<<endl;
        cout<<"5. Close your account"<<endl;
        cout<<"5. Show all accounts details"<<endl;
        cout<<"6. Exit system"<<endl;
        cout<<" Enter your choice:"<<endl;
        cin>>choice;
        switch(choice){
    case 1:
        string f,l;
        int b;
        cout<<"Enter your first name, last name, balance"<<endl;
        cin>>f>>l>>b;
        ba.openAccount(f,l,b)
        cout<<"Account was created successfully"<<endl;
        ba.checkBalance();
        break;
    case 2:
        cout<<"Enter your account's ID:"<<endl;
        cin<<id;
        ba.checkBalance(id);
        break;
    case 3:
        int id;
        cout<<"Enter your account's ID:"<<endl;
        cin<<id;
            cout<<"Enter amount to deposit:"<<endl;
        cin<<id;
        ba.deposit(id);
        break;
    case 4:
        int id;
        cout<<"Enter your account's ID:"<<endl;
        cin<<id;
        cout<<"Enter amount to withdraw:"<<endl;
        cin<<id;
        ba.deposit(id);
        break;
    case 5:
        break;
    case 6:
        break;
    default:
        break;}
    }while(choice !=6)
    return 0;}
