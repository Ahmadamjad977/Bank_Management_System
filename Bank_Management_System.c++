#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Account
{
private:
    int accNo;
    string name;
    int pin;
    double balance;

public:
    Account()
    {
        accNo = 0;
        name = "";
        pin = 0;
        balance = 0;
    }

    Account(int a, string n, int p, double b)
    {
        accNo = a;
        name = n;
        pin = p;
        balance = b;
    }

    int getAccNo() const
    {
        return accNo;
    }

    string getName() const
    {
        return name;
    }

    int getPin() const
    {
        return pin;
    }

    double getBalance() const
    {
        return balance;
    }

    void setBalance(double b)
    {
        balance = b;
    }

    void display() const
    {
        cout << "\n------------------------";
        cout << "\nAccount No : " << accNo;
        cout << "\nName       : " << name;
        cout << "\nBalance    : " << balance;
        cout << "\n------------------------\n";
    }
};

class BankSystem
{
private:
    vector<Account> accounts;

public:
    void loadAccounts()
    {
        accounts.clear();

        ifstream file("accounts.txt");

        int accNo, pin;
        string name;
        double balance;

        while (file >> accNo >> name >> pin >> balance)
        {
            accounts.push_back(
                Account(accNo, name, pin, balance)
            );
        }

        file.close();
    }

    void saveAccounts()
    {
        ofstream file("accounts.txt");

        for (int i = 0; i < accounts.size(); i++)
        {
            file << accounts[i].getAccNo() << " "
                 << accounts[i].getName() << " "
                 << accounts[i].getPin() << " "
                 << accounts[i].getBalance() << endl;
        }

        file.close();
    }

    void saveTransaction(
        int accNo,
        string type,
        double amount)
    {
        ofstream file(
            "transactions.txt",
            ios::app);

        file << accNo << " "
             << type << " "
             << amount << endl;

        file.close();
    }

    int findAccount(int accNo)
    {
        for (int i = 0; i < accounts.size(); i++)
        {
            if (accounts[i].getAccNo() == accNo)
            {
                return i;
            }
        }

        return -1;
    }

    void createAccount()
    {
        int accNo;
        int pin;
        string name;
        double balance;

        cout << "\nEnter Account Number: ";
        cin >> accNo;

        if (findAccount(accNo) != -1)
        {
            cout << "Account Already Exists!\n";
            return;
        }

        cout << "Enter Name (One Word): ";
        cin >> name;

        cout << "Enter PIN: ";
        cin >> pin;

        cout << "Enter Opening Balance: ";
        cin >> balance;

        accounts.push_back(
            Account(
                accNo,
                name,
                pin,
                balance));

        saveAccounts();

        cout << "\nAccount Created Successfully!\n";
    }

    void depositMoney()
    {
        int accNo;
        double amount;

        cout << "\nEnter Account Number: ";
        cin >> accNo;

        int index = findAccount(accNo);

        if (index == -1)
        {
            cout << "Account Not Found!\n";
            return;
        }

        cout << "Enter Amount: ";
        cin >> amount;

        double newBalance =
            accounts[index].getBalance()
            + amount;

        accounts[index].setBalance(newBalance);

        saveAccounts();

        saveTransaction(
            accNo,
            "Deposit",
            amount);

        cout << "Deposit Successful!\n";
    }

    void withdrawMoney()
    {
        int accNo;
        int pin;
        double amount;

        cout << "\nEnter Account Number: ";
        cin >> accNo;

        int index = findAccount(accNo);

        if (index == -1)
        {
            cout << "Account Not Found!\n";
            return;
        }

        cout << "Enter PIN: ";
        cin >> pin;

        if (pin != accounts[index].getPin())
        {
            cout << "Wrong PIN!\n";
            return;
        }

        cout << "Enter Amount: ";
        cin >> amount;

        if (amount >
            accounts[index].getBalance())
        {
            cout << "Insufficient Balance!\n";
            return;
        }

        double newBalance =
            accounts[index].getBalance()
            - amount;

        accounts[index].setBalance(newBalance);

        saveAccounts();

        saveTransaction(
            accNo,
            "Withdraw",
            amount);

        cout << "Withdrawal Successful!\n";
    }

    void searchAccount()
    {
        int accNo;

        cout << "\nEnter Account Number: ";
        cin >> accNo;

        int index = findAccount(accNo);

        if (index == -1)
        {
            cout << "Account Not Found!\n";
            return;
        }

        accounts[index].display();
    }

    void checkBalance()
    {
        int accNo;
        int pin;

        cout << "\nEnter Account Number: ";
        cin >> accNo;

        int index = findAccount(accNo);

        if (index == -1)
        {
            cout << "Account Not Found!\n";
            return;
        }

        cout << "Enter PIN: ";
        cin >> pin;

        if (pin != accounts[index].getPin())
        {
            cout << "Wrong PIN!\n";
            return;
        }

        cout << "\nCurrent Balance: "
             << accounts[index].getBalance()
             << endl;
    }

    void deleteAccount()
    {
        int accNo;

        cout << "\nEnter Account Number: ";
        cin >> accNo;

        int index = findAccount(accNo);

        if (index == -1)
        {
            cout << "Account Not Found!\n";
            return;
        }

        accounts.erase(
            accounts.begin() + index);

        saveAccounts();

        cout << "Account Deleted Successfully!\n";
    }

    void transactionHistory()
    {
        int accNo;

        cout << "\nEnter Account Number: ";
        cin >> accNo;

        ifstream file(
            "transactions.txt");

        int id;
        string type;
        double amount;

        bool found = false;

        cout << "\nTransaction History\n";
        cout << "----------------------\n";

        while (file >> id >> type >> amount)
        {
            if (id == accNo)
            {
                cout << type
                     << " : "
                     << amount
                     << endl;

                found = true;
            }
        }

        file.close();

        if (!found)
        {
            cout << "No Transactions Found\n";
        }
    }
};

int main()
{
    BankSystem bank;

    bank.loadAccounts();

    int choice;

    do
    {
        cout << "\n================================";
        cout << "\n BANKING MANAGEMENT SYSTEM";
        cout << "\n================================";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Search Account";
        cout << "\n5. Check Balance";
        cout << "\n6. Delete Account";
        cout << "\n7. Transaction History";
        cout << "\n8. Exit";
        cout << "\n================================";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            bank.createAccount();
            break;

        case 2:
            bank.depositMoney();
            break;

        case 3:
            bank.withdrawMoney();
            break;

        case 4:
            bank.searchAccount();
            break;

        case 5:
            bank.checkBalance();
            break;

        case 6:
            bank.deleteAccount();
            break;

        case 7:
            bank.transactionHistory();
            break;

        case 8:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 8);

    return 0;
}