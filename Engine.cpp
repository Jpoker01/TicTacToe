//
// Created by jirip on 17.10.2021.
//

#include "Engine.h"

Engine::Engine(const Size size, const std::string filename, std::string fillSymbol){
    m_filename = filename;

    Layout<std::string>* layout1 = new Layout<std::string>(size, fillSymbol);
    m_layout = layout1;

    Player* player1 = new Player("player1", "O");
    m_player1 = player1;
    Player* player2 = new Player("player2", "X");
    m_player2 = player2;

    m_activePlayer = m_player1;
}

void Engine::setUpPlayerProfiles() {
    std::string name1, name2;
    std::string symbol1, symbol2;
    std::cout << "Please type in the name of the first player: " << std::endl;
    std::cin >> name1;
    std::cout << "Please type in which symbol they will use: " << std::endl;
    std::cin >> symbol1;
    m_player1->setName(name1);
    m_player1->setSymbol(symbol1);
    std::cout << "Profile successfully created!" << std::endl;

    std::cout << "Please type in the name of the second player: " << std::endl;
    std::cin >> name2;
    std::cout << "Please type in which symbol they will use: " << std::endl;
    std::cin >> symbol2;
    m_player2->setName(name2);
    m_player2->setSymbol(symbol2);
    std::cout << "Profile successfully created!" << std::endl;

    m_activePlayer = m_player1;
}


void Engine::play(){

    std::cout << "Welcome to the game Tic Tac Toe. " << std::endl;
    std::cout << "Start with setting up your profiles. " << std::endl;
    setUpPlayerProfiles();

    Position position;
    std::string symbol;
    int count = 0;
    char decision;

    bool finished = false;

    m_layout->printLayout();
    while (!finished){
        symbol = m_activePlayer->getSymbol();
        if (count % 5 == 0 and count != 0){
            std::cout << "Would you like to save the game ? (y/n)" << std::endl;
            std::cin >> decision;
            if (decision == 'y'){
                saveDesk();
            }
        }
        position = getUserInput();
        if ((isWithinDesk(position)) and isPositionEmpty(position)){
                insertMove(position, symbol);
                finished = boolCheckVictory(position);
            } else {
            while ((!isWithinDesk(position)) and (!isPositionEmpty(position))){
                position = getUserInput();
            }
            insertMove(position, symbol);
            finished = boolCheckVictory(position);
        }
        count++;
        switchUser();
        m_layout->printLayout();
    }

    std::cout << "The player " << m_activePlayer->getName() << " has won the game." << std::endl;
    std::cout << "Thanks for playing!" << std::endl;

}

Position Engine::getUserInput() const{
    Position position;
    std::cout << "Type in the position where you want to place your next symbol (row, column):" << std::endl;
    std::cin >> position.row >> position.col;
    return position;
}

bool Engine::isWithinDesk(const Position position) const{
    Size size = m_layout->getSize();

    if ((position.row >= 0 and position.row < size.rows)
    and (position.col >= 0 and position.col < size.cols)){
        return true;
    } else {
        return false;
    }
}

bool Engine::isPositionEmpty(const Position position) const {
    std::string fillSymbol = m_layout->getFillSymbol();
    std::string valueOfPosition = m_layout->getValue(position);
    if (valueOfPosition == fillSymbol){
        return true; // empty
    } else {
        return false; //not empty
    }
}
void Engine::insertMove(const Position position, const std::string symbol){
    if (isPositionEmpty(position)){
       m_layout->setValue(position, symbol);
    }
}
bool Engine::boolCheckVictory(Position position){
    int victoryCondition = 5;
    bool victory;
    int pocet = 0;
    std::string symbol = m_activePlayer->getSymbol();
    Size size = m_layout->getSize();

    for (unsigned int i = 0; i < size.cols; i++){
        if (m_layout->getValue({position.row, i}) == symbol){
            pocet++;
            if (pocet == victoryCondition){
                victory = true;
            }
        } else {
            pocet = 0;
        }
    }
    pocet = 0;


    for (unsigned int i = 0; i < size.rows; i++){
        if (m_layout->getValue({position.col, i}) == symbol){
            pocet++;
            if (pocet == victoryCondition){
                victory = true;
            }
        } else {
            pocet = 0;
        }
    }


    pocet = 0;
    unsigned int iRow = position.row;
    unsigned int jCol = position.col;

    while (iRow > 0 and jCol > 0){
        iRow--;
        jCol--;
    }

    while (iRow < size.rows and jCol < size.cols){
        if (m_layout->getValue({iRow, jCol}) == symbol){
            pocet++;
            if (pocet == victoryCondition){
                victory = true;
            }
        } else {
            pocet = 0;
        }
        iRow++;
        jCol++;
    }

    pocet = 0;
    iRow = position.row;
    jCol = position.col;


    while (iRow > 0 and jCol < size.cols - 1){
        iRow--;
        jCol++;
        //std::cout << "i" << iRow << std::endl;
        //std::cout << "j" << jCol << std::endl;
    }

    while (iRow < size.rows - 1 and jCol > 0){


        if (m_layout->getValue({iRow, jCol}) == symbol){
            pocet++;
            if (pocet == victoryCondition){
                victory = true;
            }
        } else {
            pocet = 0;
        }
        iRow++;
        jCol--;
        //std::cout << "while i" << iRow << std::endl;
        //std::cout << "while j" << jCol << std::endl;
    }

    if (victory){
        return true;
    } else {
        return false;
    }

}

void Engine::switchUser(){
    if (m_activePlayer == m_player1){
        m_activePlayer = m_player2;
    } else {
        m_activePlayer = m_player1;
    }
}

void Engine::saveDesk() const throw(std::invalid_argument){

    std::ofstream file(m_filename);
    Size layoutSize = m_layout->getSize();

    if (file.is_open()){
        file << layoutSize.rows;
        file << layoutSize.cols;
        file << std::endl;
        for (unsigned int row = 0; row < layoutSize.rows; row++){
            for (unsigned int col = 0; col < layoutSize.cols; col++){
                file << m_layout->getValue(Position{row, col});
            }
            file << std::endl;
        }

        file.close();
    } else {
        throw std::invalid_argument("Cannot open the file");
    }

}

void Engine::loadDesk() const throw(std::invalid_argument){
    std::ifstream input(m_filename);
    Size layoutSize = m_layout->getSize();
    Size loadedLayoutSize;
    std::string symbol;

    if (input.is_open()){
         input >> loadedLayoutSize.rows >> loadedLayoutSize.cols;

         if ((loadedLayoutSize.rows == layoutSize.rows) and (
                 loadedLayoutSize.cols == layoutSize.cols)){
             for (unsigned int row = 0; layoutSize.rows; ++row){
                 for (unsigned int col = 0; col < layoutSize.cols; ++col){
                    input >> symbol;
                    m_layout->setValue(Position{row, col}, symbol);
                 }
             }
         }
         else {
             std::cerr << "The given file cannot be used as the saved layout size is: "
             << loadedLayoutSize.rows << " " << loadedLayoutSize.cols << std::endl;
             std::cerr << "The size of the layout in this instance is: "
             << layoutSize.rows << " " << layoutSize.cols << std::endl;
         }
        input.close();
    } else {
        throw std::invalid_argument("Cannot open the file");
    }
}

