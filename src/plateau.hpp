#ifndef FRESHFISH_PLATEAU_HPP
#define FRESHFISH_PLATEAU_HPP

#include "constantes.hpp"
#include "position.hpp"

#include <map>
#include <iostream>
#include <vector>
#include <string>

struct Tuile {
  Amenagement amenagement ;
  int joueur ;
  bool estVisite;
} ;


struct Plateau {

  //ajout de cases une par une
  void ajouter(const Position& pos) ;

  //ajout d'un rectangle d'un coup
  void ajouter(const Position& pos_min, const Position& pos_max) ;

  //réservation d'un emplacemen pour un joueur
  void reserver(const Position& pos, int joueur) ;

  //placement d'un aménagement
  void amenager(const Position& pos, Amenagement amenagement, int joueur) ;

  //dessin en svg ou en png, nécessite librsvg-2.0
#ifndef NO_GRAPHICS
  void dessiner(const std::string& cible, int unit = 64, float margin = 0., const std::string& style="style.svg") ;
#endif
  
  //stockage des tuiles
  std::map<Position, Tuile> tuiles ;

  //stockage des aménagements éliminés (pour la fin du projet)
  std::vector<Tuile> eliminees ;
} ;

//affichage du plateau en console
std::ostream& operator<<(std::ostream& out, const Plateau& p) ;

#endif
