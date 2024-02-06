#include "partie.hpp"
#include "melangeur.hpp"

#include <iostream>
#include <cstdlib>
#include <sstream>

int main() {

  Plateau p ;
  p.ajouter({0,0}, {10,10}) ;

  Melangeur<Position> candidates ;
  for(auto& t : p.tuiles) {
    candidates.inserer(t.first) ;
  }

#ifndef NO_GRAPHICS
  int i = 1 ;
  p.dessiner("output/plateau_0.png") ;
#endif

  while(candidates.taille() > 0) {
    Position pos = candidates.retirer() ;
    if(p.tuiles[pos].amenagement == Amenagement::VIDE) {
      p.reserver(pos, 0) ;
      p.amenager(pos, Amenagement::ARBRE, 0) ;
      std::cout << "============================================" << std::endl ;
      std::cout << p << std::endl ;

#ifndef NO_GRAPHICS
      std::stringstream ss ;
      ss << "output/plateau_" << i << ".png" ;
      p.dessiner(ss.str()) ;
      ++i ;
#endif
    }
  }


  return 0 ;
}
