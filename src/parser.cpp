#include"Parser.h"
Polynomial* PolyParser::generatePoly(std::string input){
    std::vector<std::string> vec = split(input, '+');
    // for(auto item: vec){
    //     std::cout << item << ',' << std::endl;
    // }
    return generateList(vec);
}
std::vector<std::string> PolyParser::split(std::string input, char delim){
    input.erase(std::remove_if(input.begin(), input.end(), [](char c){return isspace(c);}), input.end());
    std::istringstream iss(input);
    std::string token;
    std::vector<std::string> tokens;
    while(std::getline(iss, token, delim)){
        tokens.push_back(token);
    }
    return tokens;
    // delim = '+';
    // std::vector<std::string> res;
    // std::string s = "";
    // for (char ch : input) {
    //     if (ch != '+' && ch != '-') {
    //         s.push_back(ch);
    //     } else {
    //         res.push_back(s);
    //         if(ch == '+'){
    //             s = "";
    //         }else{
    //             s = "-";
    //         }
    //     }
    // }
    // res.push_back(s);
    // return res;
}
Polynomial* PolyParser::generateList(std::vector<std::string> vec){
    Polynomial* poly = new Polynomial();
    // std::vector<std::string> vec{"9y", "73x^7", "5z^56", "8", "u^3", "7x^8"};
    static std::string pattern = 
    R"(^\(?(-?\d*\.?\d*)?\)?([a-zA-Z]?)\^?\(?(-?\d*\.?\d*)?\)?$)";
    static std::regex reg(pattern);
    std::smatch result;
    for(auto item :vec)
        if(std::regex_search(item,result, reg)){
            int key; double value;
            if(result[3] == ""){
                // evaluate key
                if(result[2] == ""){
                    key = 0;
                }else{
                    key = 1;
                }
            }else{
                key = std::stoi(result[3]);
            }

            if(result[1] == ""){
                // evaluate value
                value = 1.0;
            }else if(result[1] =="-"){
                value = -1.0;
            }else{
                value = std::stod(result[1]);
            }
            // std::cout << value << 'x' << key << std::endl;
            poly->insert(key, value);
            // poly->printPoly();
        }
    return poly;
}