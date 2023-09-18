#include"Menu.h"
Menu::Menu():polys{}{
     std::cout << std::flush << "loading history" << std::endl;
    std::ifstream inputFile("store.in");
    if(inputFile.is_open()){
        std::string line;
        while(std::getline(inputFile, line)){
            insertPoly(line);
        }
         std::cout << std::flush << "Successfully loading " << polys.size() << "polynomials" << std::endl;
        displayPoly();
    }
    else{
         std::cout << std::flush << "No History" << std::endl;
    }
}

Menu::~Menu(){
    std::ofstream store("store.in");
     std::cout << std::flush << "saving" << std::endl;
    for(auto& p: polys){
        p->printPoly(store);
    }
    for(auto& p: polys){
        delete p;
    }
     std::cout << std::flush << "bye" << std::endl;
}

void Menu::mainMenu(){

    bool exit = false;
    while(!exit){
         std::cout << std::flush << std::string(50, '*') << std::endl;
         std::cout << std::flush << "choose operations" << std::endl;
         std::cout << std::flush << "1. -- display all polynomials --" << std::endl;
         std::cout << std::flush << "2. -- create new polynomial -- " << std::endl;
         std::cout << std::flush << "3. -- do operations bases on existed polynomials" << std::endl;
         std::cout << std::flush << "q -- quit" << std::endl;
        std::string line;
        // std::cin.clear(); std::cin.sync();
        std::getline(std::cin, line);
        switch (line[0])
        {
        case '2':
            createMenu();
            break;
        case '3':
            operationMenu();
            break;
        case '1':
            displayPoly();
            break;
        case 'q':
            exit = true;
            break;
        default:
             std::cout << std::flush << "unknown input" << std::endl;
            break;
        }
    }
    

}

void Menu::createMenu(){
     std::cout << std::flush << std::string(50, '=') << std::endl;
     std::cout << std::flush << "enter your expression: " << std::endl;
    std::string line;
    std::getline(std::cin, line);
        std::cin.sync();
    insertPoly(line);
     std::cout << std::flush << "append " << std::endl;
    polys.back()->printPoly( std::cout << std::flush);
     std::cout << std::flush << "success!" << std::endl;
}

void Menu::operationMenu(){
     std::cout << std::flush << std::string(50, '=') << std::endl;
     std::cout << std::flush << "choose operations" << std::endl;
     std::cout << std::flush << "1. -- add 2 expressions --" << std::endl;
     std::cout << std::flush << "2. -- mult 2 expressions -- " << std::endl;
     std::cout << std::flush << "3. -- minus 2 expression" << std::endl;
     std::cout << std::flush << "4 -- derive 1 expression" << std::endl;
     std::cout << std::flush << "5 -- compute the expression at value x" << std::endl;
     std::cout << std::flush << "6 -- delete an expression" << std::endl;
    
    std::string line;
    std::getline(std::cin, line);
        std::cin.sync();
    switch (line[0]){
        case '1':
        case '3':
        case '2':
            opMenu(line[0]);
            break;
        case '4': 
            deriveMenu();
            break;
        case '5':
            computeMenu();
            break;
        case '6':
            deleteMenu();
            break;
        default:
             std::cout << std::flush << "unknown input" << std::endl;
            break;
    }
}

void Menu::opMenu(char op){
     std::cout << std::flush << std::string(50, '-') << std::endl;
    size_t i, j;
    std::string line;
    bool valid=false;
    while(! valid){
         std::cout << std::flush << "enter the index the first expression";
        std::cin >> i;
        std::cin.sync();
        if(i>= 0 && i<polys.size()){
            valid=true;
        }else{
             std::cout << std::flush << "invalid index" << std::endl;
        }
    }
    valid = false;
    while(! valid){
         std::cout << std::flush << "enter the index the first expression";
        std::cin >> j;
        // std::cin.sync();
        if(j>= 0 && j<polys.size()){
            valid=true;
        }else{
             std::cout << std::flush << "invalid index" << std::endl;
        }
    }
    Polynomial *p;
    if(op == '3'){
        p = new Polynomial(*polys[i] - *polys[j]);
    }else if(op == '1'){
        p = new Polynomial(*polys[i] + *polys[j]);
    }else{
        p = new Polynomial(*polys[i] * *polys[j]);
    }
    // Polynomial* p = new Polynomial(*polys[i] * *polys[j]);
     std::cout << std::flush << "get : ";
    p->printPoly( std::cout << std::flush);
    //  std::cout << std::flush << "save?(y or n)" << std::endl;
    //  std::cin.ignore();
    std::getline(std::cin, line);
    // if(line[0] == 'y' || line[0] == 'Y'){
        polys.push_back(p);
         std::cout << std::flush << "successfully saved!" << std::endl;
    // }else{
        // delete p;
    // }
    // std::cin.sync();

}

void Menu::deriveMenu(){
     std::cout << std::flush << std::string(50, '-') << std::endl;
     std::cout << std::flush << "enter the index of expression: ";
    size_t i;
    bool valid=false;
    while(!valid){
        std::cin >> i;
        std::cin.sync();
        if(i >= 0 && i < polys.size()){
            valid = true;
        }else{
             std::cout << std::flush << "invalid index" << std::endl;
        }
    }
    polys[i]->derive();
     std::cout << std::flush << "now the i th expression is: ";
    polys[i]->printPoly( std::cout << std::flush);
}
void Menu::computeMenu(){
     std::cout << std::flush << std::string(50, '-') << std::endl;
     std::cout << std::flush << "enter the index of expression: ";
    size_t i;
    bool valid=false;
    while(!valid){
        std::cin >> i;
        std::cin.sync();
        if(i >= 0 && i < polys.size()){
            valid = true;
        }else{
             std::cout << std::flush << "invalid index" << std::endl;
        }
    }
     std::cout << std::flush << "enter a valud x: " <<std::endl;
    double x;
    std::cin >> x;
        std::cin.sync();
     std::cout << std::flush << "the result is : " << polys[i]->compute(x) << std::endl;

}
void Menu::deleteMenu(){
     std::cout << std::flush << "enter the index of the expression" << std::endl;
    size_t i;
    bool valid=false;
    while(!valid){
        std::cin >> i;
        std::cin.sync();
        if(i >= 0 && i < polys.size()){
            valid = true;
        }else{
             std::cout << std::flush << "invalid index" << std::endl;
        }
    }
    delete polys[i];
    polys.erase(polys.begin()+i);
}

void Menu::displayPoly(){
    for(size_t i = 0; i < polys.size(); i++){
         std::cout << std::flush << i << " : " << std::endl;
        polys[i]->printPoly( std::cout << std::flush);
    }
}
void Menu::insertPoly(std::string input){
    try{
        Polynomial* p = PolyParser::generatePoly(input);
        polys.push_back(p);
    }catch(std::exception& e){
         std::cout << std::flush << "invalid polynomial" << std::endl;
         std::cout << std::flush << "fail to insert the polynomial" << std::endl;
    }
    
}