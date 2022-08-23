#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;
#define MIN_BALANCE 500
class account
{
    private:
        long account_number;
        string first_name;
        string last_name;
        float balance;
        static long next_account_number;
    public:
        account(){}
        account(string fname,string lname,float balance);
        long get_account_number(){return account_number;}
        string get_first_name(){return first_name;}
        string get_last_name(){return last_name;}
        float get_balance(){return balance;}
        void deposit(float amount);
        void withdraw(float amount);
        static void set_last_account_number(long accountnumber);
        static long get_last_account_number();
        friend ofstream & operator<<(ofstream &ofs,account &acc);
        friend ifstream & operator>>(ifstream &ifs,account &acc);
        friend ostream & operator<<(ostream &os,account &acc);
};
long account::next_account_number=0;
class bank
{
    private:
        map<long,account> accounts;
    public:
        bank();
        account open_account(string fname,string lname,float balance);
        account balance_enquiry(long account_number);
        account deposit(long account_number,float amount);
        account withdraw(long account_number,float amount);
        void close_account(long account_number);
        void show_all_accounts();
        ~bank();
};
int main()
{
    bank b;
    account acc;
    int choice;
    string fname,lname;
    float balance;
    long accountnumber;
    float amount;
    cout<<"***Banking System***\n";
    do
    {
        cout<<"\n";
        cout<<"\t1) Open an Account\n";
        cout<<"\t2) Balance Enquiry\n";
        cout<<"\t3) Deposit\n";
        cout<<"\t4) Withdrawal\n";
        cout<<"\t5) Close an Account\n";
        cout<<"\t6) Show all Accounts\n";
        cout<<"\t7) Quit\n";
        cout<<"\tEnter the choice : ";
        cin>>choice;
        switch(choice)
        {
            case 1:
               cout<<"Enter first name : ";
               cin>>fname;
               cout<<"Enter last name : ";
               cin>>lname;
               cout<<"Enter initial balance : ";
               cin>>balance;
               acc=b.open_account(fname,lname,balance);
               cout<<"Congrajulations account is created\n";
               cout<<acc;
               break;
            case 2:
               cout<<"Enter Account Number : ";
               cin>>accountnumber;
               acc=b.balance_enquiry(accountnumber);
               cout<<"Your account details\n";
               cout<<acc;
               break;
            case 3:
               cout<<"Enter Account Number : ";
               cin>>accountnumber;
               cout<<"Enter Balance : ";
               cin>>amount;
               acc=b.deposit(accountnumber,amount);
               cout<<"Amount is Deposited\n";
               cout<<acc;
               break;
            case 4:
               cout<<"Enter Account Number : ";
               cin>>accountnumber;
               cout<<"Enter amount : ";
               cin>>amount;
               acc=b.withdraw(accountnumber,amount);
               cout<<"Amount withdrawn\n";
               cout<<acc;
               break;
            case 5:
               cout<<"Enter Account Number : ";
               cin>>accountnumber;
               b.close_account(accountnumber);
               cout<<"Account is closed\n";
               break;
            case 6:
               b.show_all_accounts();
               break;
            case 7:
               break;
            default:
               cout<<"Enter the correct choice";
               break; 
        }
    }while(choice!=7);
    return 0;
}
account::account(string fname,string lname,float balance)
{
    next_account_number++;
    account_number=next_account_number;
    first_name=fname;
    last_name=lname;
    this->balance=balance;
}
void account::deposit(float amount)
{
    balance+=amount;
}
void account::withdraw(float amount)
{
    if(balance-amount<MIN_BALANCE)
        cout<<"InsufficientFunds\n";
    else
        balance-=amount;
}
void account::set_last_account_number(long accountnumber)
{
    next_account_number=accountnumber;
}
ofstream & operator<<(ofstream &ofs,account &acc)
{
    ofs<<acc.account_number<<endl;
    ofs<<acc.first_name<<endl;
    ofs<<acc.last_name<<endl;
    ofs<<acc.balance<<endl;
    return ofs;
}
ifstream & operator>>(ifstream &ifs,account &acc)
{
    ifs>>acc.account_number;
    ifs>>acc.first_name;
    ifs>>acc.last_name;
    ifs>>acc.balance;
    return ifs;
}
ostream & operator<<(ostream &os,account &acc)
{
    os<<"First Name : "<<acc.get_first_name()<<endl;
    os<<"Last Name : "<<acc.get_last_name()<<endl;
    os<<"Account Number : "<<acc.get_account_number()<<endl;
    os<<"Balance : "<<acc.get_balance()<<endl;
    return os;
}
bank::bank()
{
    account acc;
    ifstream infile;
    infile.open("Bank.data");
    if(!infile)
    {
        return;
    }
    while(!infile.eof())
    {
        infile>>acc;
        accounts.insert(pair<long,account>(acc.get_account_number(),acc));
    }
    account::set_last_account_number(acc.get_account_number());
    infile.close();
}
account bank::open_account(string fname,string lname,float balance)
{
    account acc(fname,lname,balance);
    accounts.insert(pair<long,account>(acc.get_account_number(),acc));
    return acc;
}
account bank::balance_enquiry(long accountnumber)
{
    map<long,account>::iterator itr=accounts.find(accountnumber);
    return itr->second;
}
account bank::deposit(long accountnumber,float amount)
{
    map<long,account>::iterator itr=accounts.find(accountnumber);
    itr->second.deposit(amount);
    return itr->second;
}
account bank::withdraw(long accountnumber,float amount)
{
    map<long,account>::iterator itr=accounts.find(accountnumber);
    itr->second.withdraw(amount);
    return itr->second;
}
void bank::close_account(long accountnumber)
{
    map<long,account>::iterator itr=accounts.find(accountnumber);
    accounts.erase(accountnumber);
    return;
}
void bank::show_all_accounts()
{
    map<long,account>::iterator itr;
    for(itr=accounts.begin();itr!=accounts.end();itr++)
        cout<<itr->second<<endl;
    return;
}
bank::~bank()
{
    ofstream outfile;
    outfile.open("Bank.data",ios::trunc);
    map<long,account>::iterator itr;
    for(itr=accounts.begin();itr!=accounts.end();itr++)
         outfile<<itr->second;
    outfile.close();
    return;
}
