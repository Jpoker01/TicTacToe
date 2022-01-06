//
// Created by jirip on 17.10.2021.
//

#ifndef TICTACTOE_LAYOUT_H
#define TICTACTOE_LAYOUT_H


#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdexcept>

#include "Size.h"
#include "Position.h"


template <class T> class Layout {
    std::vector<std::vector<T>> m_layout;
    T m_fillSymbol;
public:
    Layout(const Size size, const T fillSymbol);
    void setValue(const Position position, const T value) throw (std::out_of_range) ;
    T getValue(const Position position) const throw (std::out_of_range);
    T getFillSymbol() const;
    void printLayout() const;
    Size getSize() const;

};

template <class T> Layout<T>::Layout(const Size size, const T fillSymbol){
    std::vector<std::vector<T>> layout(size.rows, std::vector<T>(size.cols, fillSymbol));
    m_layout = layout;
    m_fillSymbol = fillSymbol;
}

template <class T> Size Layout<T>::getSize() const{
    unsigned int rows = m_layout.size();
    unsigned int cols = m_layout.at(0).size();
    return Size{rows, cols};
}

template <class T> void Layout<T>::setValue(const Position position, const T value) throw (std::out_of_range) {
    try{
        Size size = Size{m_layout.size(), m_layout.at(0).size()};
        if (position.row > size.rows or position.col > size.cols){
            std::out_of_range ex ("The given position is out of range of the layout");
            throw ex;
        }
        if (position.row < 0 or position.col < 0){
            std::out_of_range ex ("The given position is out of range of the layout");
            throw ex;
        }
        m_layout.at(position.row).at(position.col) = value;
    } catch (std::out_of_range &e){
        std::cerr << "The given parameter must be within the limits of the layout " << std::endl;
        std::cerr << e.what() << std::endl;
    }
}

template <class T> T Layout<T>::getFillSymbol() const {
    return m_fillSymbol;
}

template <class T> T Layout<T>::getValue(const Position position) const throw (std::out_of_range){
    try {
        Size size = {m_layout.size(), m_layout.at(0).size()};
        if (position.row > size.rows or position.col > size.cols){
            std::out_of_range ex ("The given position is out of range of the layout");
            throw ex;
        }
        if (position.row < 0 or position.col < 0){
            std::out_of_range ex ("The given position is out of range of the layout");
            throw ex;
        }

        return m_layout.at(position.row).at(position.col);
    } catch (std::out_of_range &e){
        std::cerr << "The given parameter must be within the limits of the layout " << std::endl;
        std::cerr << e.what() << std::endl;
    }
}



template <class T> void Layout<T>::printLayout() const{
    int stringLgth = m_layout.at(0).at(0).length();
    std::string space(" ", stringLgth);
    for (int i = 0; i < m_layout.size(); i++){
        if (i == 0){
            std::cout << "  ";
        }
        std::cout << i << space;
    }
    std::cout << std::endl;
    for (int i = 0; i < m_layout.size(); i++){
        std::cout << i << " ";
        for (int j = 0; j < m_layout.at(0).size(); j++){
            std::cout << m_layout.at(i).at(j) << " ";
        }
        std::cout << std::endl;

    }
}






#endif //TICTACTOE_LAYOUT_H
