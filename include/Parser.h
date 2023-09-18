#ifndef PARSER_H
#define PARSER_H

#include<vector>
#include<sstream>
#include<algorithm>
#include<cctype>
#include<regex>
#include"Polynomial.h"

class PolyParser{
    public:
        static Polynomial* generatePoly(std::string input);
    private:
        static std::vector<std::string> split(std::string input, char delim);
        static Polynomial* generateList(std::vector<std::string> vec);
        static std::pair<int, int> getKeyAndVal(std::string part);
};

#endif