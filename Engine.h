//
// Created by jirip on 17.10.2021.
//

#ifndef TICTACTOE_ENGINE_H
#define TICTACTOE_ENGINE_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "Position.h"
#include "Size.h"
#include "Layout.h"
#include "Player.h"

class Engine{
    Layout<std::string>* m_layout;
    Player* m_player1;
    Player* m_player2;
    Player* m_activePlayer;
    std::string m_filename;

public:
    Engine(const Size size, const std::string filename, const std::string fillSymbol);
    void play();
private:
    void setUpPlayerProfiles();
    Position getUserInput() const;
    bool isWithinDesk(const Position position) const;
    bool isPositionEmpty(const Position position) const ;
    void insertMove(const Position position, const std::string symbol);
    bool boolCheckVictory(Position position);
    void switchUser();
    void loadDesk() const throw(std::invalid_argument);
    void saveDesk() const throw(std::invalid_argument);

};




#endif //TICTACTOE_ENGINE_H
