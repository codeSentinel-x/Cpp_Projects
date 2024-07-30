#include <iostream>
#include <string>
#include <fstream>

using std::string, std::cout, std::cin;
const string filePath = "BankData.txt";

class BankAccount{

    private:
    string name;
    string password;
    double balance;
    void SaveData(){
        std::fstream file(filePath);
        if (!file.is_open()) std::cerr << "Unable to open file " << filePath << "\n";
        string line;
        while (getline(file, line)){
            if (line.find(name) != string::npos){
                getline(file, line);
                cout << line;
            }
        }


    }
    void LoadData(){
        std::fstream file(filePath);
        if (!file.is_open()) std::cerr << "Unable to open file " << filePath << "\n";
        string line;
        int i = 0;
        while (getline(file, line)){
            if (line.find(name) != string::npos){
                name = line;
                line = "";
                i = 2;
            } else if (i == 2){
                password = line;
                i--;
            } else if (i == 1){
                balance = std::stod(line);
                i--;
            }
        }
        Display();
    }
    public:
    BankAccount(){ }
    BankAccount(string accountName, string password) : name(accountName), password(password){
        LoadData();
    }
    BankAccount(string accountName, string password, double initialBalance) : name(accountName), password(password), balance(initialBalance){
        SaveData();
    }

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
        cout << "\nAccount name: " << name << "\nBalance: " << balance << "$\n";
    }
};
bool CheckForUser(string& name, string& password){
    std::fstream file(filePath);
    string nameFromFile, passwordFromFile;
    if (!file.is_open()) std::cerr << "Unable to open file " << filePath << "\n";
    string line;
    int i = 0;
    while (getline(file, line)){
        if (line.find(name) != string::npos){
            nameFromFile = line;
            line = "";
            i = 1;
        } else if (i == 1){
            passwordFromFile = line;
            i--;
        } 
    }
    if (nameFromFile == name && passwordFromFile == password) return true;
    else{
        cout << "Wrong username or password\n";
        return false;
    }
}

int main(){
    string name;
    string password;
    double initialBalance;
    char choice;
    BankAccount account;
    cout << "Choose option\nL - log in\nC - create account\n";
    cin >> choice;
    if (choice == 'L' || choice == 'l'){
        while (true){
            cout << "Enter your name: ";
            getline(cin, name);
            cout << "Enter password: ";
            getline(cin, password);
            if (name == " " || name == "")continue;
            if (CheckForUser(name, password))break;
        }
        account = BankAccount(name, password);
    } else{
        cout << "Enter your name: ";
        getline(cin, name);
        cout << "\nEnter your password: ";
        getline(cin, password);
        cout << "\nEnter your initial balance: ";
        cin >> initialBalance;
        account = BankAccount(name,password, initialBalance);
    }


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