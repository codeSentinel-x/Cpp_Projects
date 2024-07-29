#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>

using std::ifstream, std::ofstream, std::string, std::cout, std::cin, std::vector, std::ios;


void _encrypt(const string& filePath, int key){

    ifstream inputFile(filePath);
    vector<char> charVector;
    char c;

    while (inputFile.get(c)) charVector.push_back(c + key);

    inputFile.close();


    ofstream outputFile(filePath, ios::out | ios::trunc);

    for (const char cA : charVector) outputFile.put(cA);

    outputFile.close();
}

void _d(const string& filePath, int key){

    ifstream inputFile(filePath);
    vector<char> charVector;
    char c;

    while (inputFile.get(c)) charVector.push_back(c - key);

    inputFile.close();

    
    ofstream outputFile(filePath, ios::out | ios::trunc);

    for (const char cA : charVector) outputFile.put(cA);

    outputFile.close();
}

void _ap(string& path){

    cout << "Please enter path to input file of operation\n";
    cin >> path;

}

void _ak(int& key){

    cout << "Please enter the key\n";
    cin >> key;

}


int main(){
    string filePath;
    int key;
    int opt;
    
    do{
        cout << "Press 1 to decrypt one file\nPress 2 to encrypt one file\n" <<
            "Press 3 to decrypt multiple files\nPress 4 to encrypt multiple files\nPress 0 to quit\n";
        cin >> opt;

        switch (opt){
            case 1:

                _ap(filePath);
                _ak(key);
                _d(filePath, key);
                break;

            case 2:

                _ap(filePath);
                _ak(key);
                _encrypt(filePath, key);
                break;

            case 3:

                int a3;
                bool b3;

                cout << "How much file do you want to encrypt?\n";
                cin >> a3;
                cout << "Do you want to use different key for every one(0 = false, 1 = true)\n";
                cin >> b3;

                if (b3) _ak(key);

                for (int i{ 0 }; i < a3; i++){
                    _ap(filePath);
                    if (!b3) _ak(key);
                }
                break;

            case 4:

                int a4;
                bool b4;

                cout << "How much file do you want to decrypt?\n";
                cin >> a4;
                cout << "Do you want to use different key for every one(0 = false, 1 = true)\n";
                cin >> b4;

                if (b4) _ak(key);
                for (int i{ 0 }; i < a4; i++){
                    _ap(filePath);
                    if (!b4) _ak(key);
                }

                break;

            default:
                break;
        }

        cout << '\n';

    } while (opt != 0);


    return 0;
}