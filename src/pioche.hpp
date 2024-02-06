#ifndef FRESHFISH_PIOCHE_HPP
#define FRESHFISH_PIOCHE_HPP

#include "melangeur.hpp"
#include "constantes.hpp"

struct Pioche {
  Pioche(int nb_joueurs) ;
  Amenagement piocher() ;
  int taille() const ;

  Melangeur<Amenagement> amenagements ;
} ;

#endif
