#ifndef FRESHFISH_JOUEUR_HPP
#define FRESHFISH_JOUEUR_HPP

#include "partie.hpp"

struct Partie ;

struct Joueur {

  //un joueur peut faire deux actions
  enum struct Action {
    RESERVER,
    PIOCHER
  } ;

  Joueur(int index) : index(index) {};

  //appelée par la partie pour déterminer ce que veut faire le joueur
  Action agir(const Partie& partie) ;

  //appelée par la partie pour déterminer quelle case le joueur veut réserver
  Position reserver(const Partie& partie, bool initial = false) ;

  //appelée par la partie pour déterminer dans quelle case un joueur souhaite
  //aménager une case
  Position amenager(const Partie& partie, Amenagement amenagement) ;

  //appelée par la partie pour déterminer la mise d'un joueur aux enchères
  int miser(const Partie& partie, Amenagement amenagement) ;

  int index ;
} ;

#endif
