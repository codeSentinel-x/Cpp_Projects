#include <iostream>
#include <string>
using namespace std;

class BankAccount{

    private:
    string name;
    double balance;

    public:
    BankAccount(string accountName, double initialBalance) : name(accountName), balance(initialBalance){}

    void Deposit(double value){
        if (value > 0){
            balance += value;
        }
    }

    void Withdraw(double value){
        if (value > 0 && value <= balance){
            balance -= value;
        } else{
            cout << "You don't have enough money!!\n";
        }
    }
    void Display(){
        cout << "\nAccount name: " << name << "\nBalance: " << balance << "$" << endl;
    }
};

int main(){
    string name;
    string password;
    double initialBalance;
    char choice;

    cout << "Choose option\nL - log in\nC - create account\n";
    cin >> choice;
    if (choice == 'L' || choice == 'l'){
        
    } else{
        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Enter your password: ";
        getline(cin, password);
        cout << "\nEnter your initial balance: ";
        cin >> initialBalance;
    }

    BankAccount account(name, initialBalance);

    double value;

    do{
        cout << "\nWhat do you want to do?"
            << "\nW - withdraw"
            << "\nD - deposit"
            << "\nS - display"
            << "\nQ - quit\n";
        cin >> choice;
        switch (choice){
            case 'w':
            case 'W':
                cout << "\nHow much do you want to withdraw?: ";
                cin >> value;
                account.Withdraw(value);
                break;
            case 'D':
            case 'd':
                cout << "\nHow much do you want to deposit?: ";
                cin >> value;
                account.Deposit(value);
                break;
            case 's':
            case 'S':
                account.Display();
                break;
            default:
                break;
        }

    } while (choice != 'Q' && choice != 'q');
    return 0;
}