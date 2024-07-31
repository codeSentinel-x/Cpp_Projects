#include <iostream>
#include <string>
#include <fstream>
#include <vector>

const std::string path = "Database.txt";

void WriteFile(std::vector<std::string> text){
    std::ofstream file(path);
    if(!file.is_open) std::cerr << "Error while opening output file"
}
std::vector<std::string> ReadFile(){
    std::ifstream file(path);
    if (!file.is_open()) std::cerr << "Error while opening input file\n";
    std::string s;
    std::vector<std::string> result;
    while (getline(file, s)){
        result.push_back(s);
    }
}
void createRow(){

}
void createColumn(){

}
void readColumn(){

}
void readRow(){
    
}
int main(){

    



    return 0;
}