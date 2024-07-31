#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//I need to make some research for this one! I will be back 
const std::string path = "Database.txt";
std::vector<std::string> fileData;

void WriteFile(){
    std::ofstream file(path);
    if (!file.is_open()) std::cerr << "Error while opening output file";
    for (std::string s : fileData){
        file << s << "\n";
    }
}
void ReadFile(){
    std::ifstream file(path);
    if (!file.is_open()) std::cerr << "Error while opening input file\n";
    std::string s;
    fileData.clear();
    while (getline(file, s)){
        fileData.push_back(s);
    }
}
void createRow(){

}
void createColumn(){

}
void readColumn(){

}

int main(){

    



    return 0;
}

