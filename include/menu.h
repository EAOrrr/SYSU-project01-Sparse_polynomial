#ifndef MENU_H
#define MENU_H

#include<vector>
#include<fstream>
#include<iomanip>
#include"Polynomial.h"
#include"Parser.h"

class Menu{
    public:
        Menu();
        ~Menu();
        void mainMenu();
        void operationMenu();

        void displayPoly();

        void createMenu();
        void opMenu(char c);
        // void addMenu();
        // void multMenu();
        // void minusMenu();
        void deriveMenu();
        void computeMenu();

        // void insertMenu();
        void deleteMenu();
    private:
        std::vector<Polynomial*> polys;
        void insertPoly(std::string);
};
#endif