//
// Created by jirip on 18.10.2021.
//

#ifndef TICTACTOE_PLAYER_H
#define TICTACTOE_PLAYER_H

#include <iostream>

class Player {
    std::string m_name;
    std::string m_symbol;

public:
    Player();
    Player(std::string name, std::string symbol);
    void setName(std::string name);
    std::string getName();
    void setSymbol(std::string symbol);
    std::string getSymbol();

};


#endif //TICTACTOE_PLAYER_H
