#include "partie.hpp"
#include "melangeur.hpp"

#include <iostream>
#include <cstdlib>

int main() {

  MelangeurOptions::imprevisible() ;

  Partie p(5) ;

  //std::system("clear") ;
  std::cout << p.plateau << std::endl ;
  //std::system("sleep 10") ;

  p.lancer() ;

#ifndef NO_GRAPHICS
  p.plateau.dessiner("output.svg") ;
#endif

  return 0 ;
}
