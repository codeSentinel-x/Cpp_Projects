#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using std::string, std::cout, std::cin, std::vector;
const string filePath = "BankData.txt";

enum UserStatus{
    normie,
    admin
};
class BankAccount{

    private:
        string name;
        string password;
        double balance;
        UserStatus status;

        void WriteNewUser(){
            std::ifstream fileI(filePath);
            if (!fileI) std::cerr << "Write new user input file error : Unable to open file " << filePath << "\n";
            string line;
            vector<string> lines;
            while (getline(fileI, line)) lines.push_back(line);

            fileI.close();
            std::ofstream fileO(filePath);
            if (!fileO) std::cerr << "Write new user output file error : Unable to open file " << filePath << "\n";
            for (string l : lines) fileO << l << "\n";
            fileO << "Name:" << name << "\n";
            fileO << "Password:" << password << "\n";
            fileO << balance << "\n";
            fileO << "Status:normie" << "\n";
            fileO.close();
        }
        void SaveData(){
            std::ifstream fileI(filePath);
            if (!fileI) std::cerr << "Save data input file error: Unable to open file " << filePath << "\n";
            string line;
            int lineNumber(-1);
            int lineCounter(0);
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
            if (!fileO) std::cerr << "Save data output file error: Unable to open file " << filePath << "\n";
            lineCounter = 0;
            for (string l : lines){
                if (lineCounter == lineNumber + 2){
                    fileO << balance << "\n";
                } else{
                    fileO << l << "\n";
                }
                lineCounter++;
            }
            fileO.close();


        }
        void LoadData(){
            std::ifstream file(filePath);
            if (!file) std::cerr << "Load data error: Unable to open file " << filePath << "\n";
            string line;
            int i(-10);
            while (getline(file, line)){
                if (line.find("Name:" +name) != string::npos){
                    name = line.erase(0, 5);
                    i = 2;
                } else if (i == 2){
                    password = line.erase(0,9);
                    i--;
                } else if (i == 1){
                    balance = std::stod(line);
                    i--;
                } else if (i == 0){
                    if (line.erase(0, 7) == "admin"){
                        status = UserStatus::admin;
                    } else{
                        status = UserStatus::normie;
                    }
                    break;
                }
            }
            file.close();
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
        UserStatus GetStatus(){
            return status;
        }
        string GetName(){
            return name;
        }
};
bool CheckForUser(string& name, string& password){
    std::ifstream file(filePath);
    string nameFromFile, passwordFromFile;
    if (!file) std::cerr << "Check for user error : Unable to open file " << filePath << "\n";
    string line;
    int i(0);
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
void DisplayAllUsers(){
    std::ifstream file(filePath);
    if (!file) std::cerr << "Display all user error : Unable to open file " << filePath << "\n";
    string line;
    while (getline(file, line)){
        if (line.find_first_of("#") == 0) continue;
        if (line.find("Password:") != string::npos) continue;
        cout << line << "\n";
    }
    file.close();
}
bool CheckForUser(string& name){
    std::ifstream file(filePath);
    string nameFromFile, passwordFromFile;
    if (!file) std::cerr << "Check for user error : Unable to open file " << filePath << "\n";
    string line;

    while (getline(file, line)){
        if (line.find("Name:" + name) != string::npos){
            return true;
        }
    }
    cout << "Username with name: " << name << " doesn't exist\n";
    return false;
    
}
void ChangeBalance(string& name, double& newBalance){
    std::ifstream fileI(filePath);
    if (!fileI) std::cerr << "Change balance input file error: Unable to open file " << filePath << "\n";
    string line;
    int lineNumber(-1);
    int lineCounter(0);
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
    if (!fileO) std::cerr << "Change balance output file error: Unable to open file " << filePath << "\n";
    lineCounter = 0;
    for (string l : lines){
        if (lineCounter == lineNumber + 2){
            fileO << newBalance << "\n";
        } else{
            fileO << l << "\n";
        }
        lineCounter++;
    }
    fileO.close();

}
void DeleteUser(string& name){
    std::ifstream fileI(filePath);
    if (!fileI) std::cerr << "Delete user input file error : Enable to open file " << filePath << "\n";
    string line;
    vector<string> lines;
    int userLine(-1);
    int counter(0);
    while (getline(fileI, line)){
        lines.push_back(line);
        if (line.find("Name:" + name) != string::npos) userLine = counter;
        counter++;
    }
    fileI.close();
    std::ofstream fileO(filePath);
    if (!fileO) std::cerr << "Delete user output file error : Enable to open file " << filePath << "\n";
    counter = 0;
    for (string s : lines){
        if (counter >= userLine && counter < userLine + 4) continue;
        fileO << s << "\n";
        counter++;
    }
}
bool ValidateNewUserData(const string& name, const string& password, const double& balance){
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
    if (!file.is_open()) std::cerr << "Validate user error: Unable to open file " << filePath << "\n";
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
    string name("");
    string password("");
    double initialBalance(0);
    double value(0);
    char choice(' ');
    BankAccount account;

    cout << "Choose option\nL - log in\nC - create account\n";
    cin >> choice;

    if (choice == 'L' || choice == 'l'){
        while (true){
            cin.ignore();
            cout << "Enter your name: ";
            getline(cin, name);
            cout << "Enter password: ";
            getline(cin, password);
            if (name == " " || name == "")continue;
            if (CheckForUser(name, password))break;
        }
        account = BankAccount(name, password);
    } else{
        while (true){
            cin.ignore();
            cout << "Enter your name: ";
            getline(cin, name);
            cout << "Enter your password: ";
            getline(cin, password);
            cout << "Enter your initial balance: ";
            cin >> initialBalance;
            if (ValidateNewUserData(name, password, initialBalance)) break;
        }
        account = BankAccount(name, password, initialBalance);
    }
    if (account.GetStatus() == UserStatus::admin){
        string usernameInput;
        double value(0);
        do{
            cout<< "\nWhat do you want to do?"
                << "\nW - withdraw from your account"
                << "\nD - deposit to your account"
                << "\nS - display your balance"
                << "\nE - display all user balances" 
                << "\nC - change user balance"
                << "\nX - delete user"
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
                case 'e':
                case 'E':
                    cout << "\n";
                    DisplayAllUsers();
                    break;
                case 'c':
                case 'C':
                    while (true){
                        cin.ignore();
                        cout << "\nEnter name for account you want to change: ";
                        getline(cin, usernameInput);
                        cout << "\nEnter new balance: ";
                        cin >> value;
                        cin.ignore();
                        if (CheckForUser(usernameInput)){
                            for (int i = 0; i < 3; i++){
                                cout << "\nEnter a password to change balance " << usernameInput << ": ";
                                getline(cin, password);
                                if (CheckForUser(name, password)){
                                    ChangeBalance(usernameInput, value);
                                    break;
                                } else{
                                    cout << "\nWrong password!";
                                    if (i == 2) cout << "\nOperation aborted";
                                }
                            }
                            break;
                        }
                    }
                    break;
                case 'x':
                case 'X':
                    while (true){
                        cin.ignore();
                        cout << "\nEnter user name to delete: ";
                        getline(cin, usernameInput);
                        if (CheckForUser(usernameInput)){
                            for (int i = 0; i < 3; i++){
                                cout << "\nEnter a password to delete user " << usernameInput << ": ";
                                getline(cin, password);
                                if (CheckForUser(name, password)){
                                    DeleteUser(usernameInput);
                                    break;
                                } else{
                                    cout << "\nWrong password!";
                                    if (i == 2) cout << "\nOperation aborted";
                                }
                            }
                            break;
                        }
                    }
                    break;
                default:
                    break;
            }

        } while (choice != 'Q' && choice != 'q');
        
    } else{
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
    }

    return 0;

}