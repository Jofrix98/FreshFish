#ifndef FRESHFISH_PARTIE_HPP
#define FRESHFISH_PARTIE_HPP

#include "plateau.hpp"
#include "pioche.hpp"
#include "joueur.hpp"

#include <vector>

struct Joueur ;

struct Partie {
  Partie(int nb_joueurs) ;

  //tourne en boucle jusqu'à la fin de la partie
  void lancer() ;

  //données de la partie
  Plateau plateau ;
  Pioche pioche ;
  std::vector<Joueur> joueurs;
  int joueur_courant ;
} ;

#endif
