#include "position.hpp"

#include <stdexcept>

Position voisine(const Position& pos, int index) {
  Position res = pos ;

  //votre code ici

  return res ;
}

std::ostream& operator<<(std::ostream& out, const Position& pos) {
  out << "{" << pos.first << "," << pos.second << "}" ;
  return out ;
}
