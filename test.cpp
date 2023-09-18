#include<regex>
#include<iostream>
using std::cout; using std::endl;

int main(void){
    std::vector<std::string> vec{"9y", "73x^7", "5z^56", "8", "u^3", "7x^8"};
    std::string pattern = R"(^((\d)*)?([a-zA-Z]?)\^?((\d)*)?$)";
    std::regex reg(pattern);
    std::smatch result;
    for(auto item :vec)
        if(std::regex_search(item,result, reg)){
            // cout << "yes";
            int key, value;
            if(result[4] == ""){
                if(result[3] == ""){
                    key = 1;
                }else{
                    key = 0;
                }
                }else{
                    key = std::stoi(result[4]);
                }
            if(result[1] == ""){
                value = 1;
            }else{
                value = std::stoi(result[1]);
            }
            // cout << result[1] << result[3] << endl;
            std::cout << value << result[3] << key << endl;
        }

}