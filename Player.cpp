//
// Created by jirip on 18.10.2021.
//

#include "Player.h"


Player::Player(){
    m_name = "default";
    m_symbol = "X";
}

Player::Player(std::string name, std::string symbol){
    m_name = name;
    m_symbol = symbol;
}

void Player::setName(std::string name){
    m_name = name;
}

std::string Player::getName(){
    return m_name;
}

void Player::setSymbol(std::string symbol){
    m_symbol = symbol;
}

std::string Player::getSymbol(){
    return m_symbol;
}