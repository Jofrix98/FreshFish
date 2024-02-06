#include "pioche.hpp"

#include <stdexcept>
#include <iostream>

Pioche::Pioche(int nb_joueurs) {
  if(nb_joueurs < 3 || nb_joueurs > 5) {
    throw std::range_error(
        "une partie doit comporter entre 3 et 5 joueurs"
        ) ;
  }

  //amenagements inutiles
  static constexpr const int nb_inutiles[] = {12, 15, 19} ;
  for(int i = 0; i < nb_inutiles[nb_joueurs-3]; ++i) {
    amenagements.inserer(Amenagement::ARBRE) ;
  }

  //boutiques
  for(int i = 0; i < nb_joueurs; ++i) {
    for(Ressource r : toutes_ressources) {
      amenagements.inserer(specifie(Amenagement::BOUTIQUE, r)) ;
    }
  }
}

Amenagement Pioche::piocher() {
  return amenagements.retirer() ;
}

int Pioche::taille() const {
  return amenagements.taille() ;
}
