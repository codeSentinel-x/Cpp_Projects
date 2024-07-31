#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using std::string, std::cout, std::cin, std::vector;
const string filePath = "BankData.txt";

class BankAccount{

    private:
        string name;
        string password;
        double balance;
        void WriteNewUser(){
            std::ifstream fileI(filePath);
            if (!fileI.is_open()) std::cerr << "Unable to open file " << filePath << "\n";
            string line;
            vector<string> lines;
            while (getline(fileI, line)) lines.push_back(line);

            fileI.close();
            std::ofstream fileO(filePath);
            if (!fileI.is_open()) std::cerr << "Unable to open file " << filePath << "\n";
            for (string l : lines) fileO << l << "\n";
            fileO << "Name:" << name << "\n";
            fileO << "Password:" << password << "\n";
            fileO << balance << "\n";
        }
        void SaveData(){
            std::ifstream fileI(filePath);
            if (!fileI.is_open()) std::cerr << "Unable to open file " << filePath << "\n";
            string line;
            int lineNumber = -1;
            int lineCounter = 0;
            vector<string> lines;
            while (getline(fileI, line)){
                lines.push_back(line);
                if (line.find("Name:" + name) != string::npos){
                    lineNumber = lineCounter;
                }
                lineCounter++;
            }
            fileI.close();
            std::ofstream fileO(filePath);
            if (!fileI.is_open()) std::cerr << "Unable to open file " << filePath << "\n";
            lineCounter = 0;
            for (string l : lines){
                if (lineCounter == lineNumber + 2){
                    fileO << balance << "\n";
                } else{
                    fileO << l << "\n";
                }
                lineCounter++;
            }
            


        }
        void LoadData(){
            std::ifstream file(filePath);
            if (!file.is_open()) std::cerr << "Unable to open file " << filePath << "\n";
            string line;
            int i = 0;
            while (getline(file, line)){
                if (line.find("Name:" +name) != string::npos){
                    name = line.erase(0,5);
                    line = "";
                    i = 2;
                } else if (i == 2){
                    password = line.erase(0,9);
                    i--;
                } else if (i == 1){
                    balance = std::stod(line);
                    i--;
                    break;
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
            WriteNewUser();
        }

        void Deposit(double value){
            if (value > 0){
                balance += value;
                SaveData();
            }
        }

        void Withdraw(double value){
            if (value > 0 && value <= balance){
                balance -= value;
                SaveData();
            } else{
                cout << "You don't have enough money!!\n";
            }
        }
        void Display(){
            cout << "\nAccount name: " << name << "\nBalance: " << balance << "$\n";
        }
};
bool CheckForUser(string& name, string& password){
    std::ifstream file(filePath);
    string nameFromFile, passwordFromFile;
    if (!file.is_open()) std::cerr << "Unable to open file " << filePath << "\n";
    string line;
    int i = 0;
    while (getline(file, line)){
        if (line.find("Name:" + name) != string::npos){
            nameFromFile = line.erase(0,5);
            line = "";
            i = 1;
        } else if (i == 1){
            passwordFromFile = line.erase(0, 9);
            if (nameFromFile == name && passwordFromFile == password) return true;
            i--;
        } 
    }
    cout << "Wrong username or password\n";
    return false;
    
}
bool ValidateNewUserData(const string& name, const string& password, const int& balance){
    if (name.rfind("\n") != string::npos)return false;
    if (name.rfind("Name:") != string::npos)return false;
    if (name.rfind("Password:") != string::npos )return false;
    if (password.rfind("\n") != string::npos )return false;
    if (password.rfind("Name:") != string::npos )return false;
    if (password.rfind("Password:") != string::npos)return false;
    if (name == " " || password == " ") return false;
    if (name.length() < 3 || password.length() < 3){
        cout << "Name and password must be at least 3 characters\n";
        return false;
    }
    std::ifstream file(filePath);
    if (!file.is_open()) std::cerr << "Unable to open file " << filePath << "\n";
    string line;
    while (getline(file, line)){
        if (line.erase(0, 5) == name){
            cout << "User with this name already exist\n";
            file.close();
            return false;
        }
    }
    file.close();
    if (balance < 0){
        cout << "Your balance should be greater than 0\n";
        return false;
    }

    return true;
}
int main(){
    string name;
    string password;
    double initialBalance;
    char choice;
    BankAccount account;
    cout << "Choose option\nL - log in\nC - create account\n";
    cin >> choice;
    cin.ignore();
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
        do{
            cout << "Enter your name: ";
            getline(cin, name);
            cout << "Enter your password: ";
            getline(cin, password);
            cout << "Enter your initial balance: ";
            cin >> initialBalance;
            account = BankAccount(name,password, initialBalance);

        } while (ValidateNewUserData(name, password, initialBalance));
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