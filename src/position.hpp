#ifndef FRESHFISH_POSITION_HPP
#define FRESHFISH_POSITION_HPP

#include <utility>
#include <iostream>

using Position = std::pair<int, int> ;

//  0 -> haut
//  1 -> gauche
//  2 -> bas
//  3 -> droite
Position voisine(const Position& pos, int index) ;

std::ostream& operator<<(std::ostream& out, const Position& pos) ;

#endif
