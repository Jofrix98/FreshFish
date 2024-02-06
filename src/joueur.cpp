#include "joueur.hpp"
#include "melangeur.hpp"

Joueur::Action Joueur::agir(const Partie& partie) {
  //compter le nombre de réservations
  int nb_reservations = 0 ;
  int nb_vides = 0 ;
  for(const auto& t : partie.plateau.tuiles) {
    if(t.second.amenagement == Amenagement::RESERVEE && t.second.joueur == index) {
      ++nb_reservations ;
    }
    if(t.second.amenagement == Amenagement::VIDE) {
      ++ nb_vides ;
    }
  }

  //si aucun emplacement ne peut être réservé, pioche
  if(nb_vides == 0) return Action::PIOCHER ;

  //pas assez de réservations, réserver un espace
  if(nb_reservations < 3) return Action::RESERVER ;

  //toutes les réservations placées, piocher
  if(nb_reservations == 8) return Action::PIOCHER ;

  //sinon une chance sur deux
  Melangeur<Joueur::Action> possibilites ;
  possibilites.inserer(Action::RESERVER) ;
  possibilites.inserer(Action::PIOCHER) ;
  return possibilites.retirer() ;
}

Position Joueur::reserver(const Partie& partie, bool initial) {
  //lister les emplacements possibles. Pour la première réservation de la
  //partie, tous les emplacements sont valides. Ensuite, seules les cases
  //vides voisines des cases non vides sont possibles
  Melangeur<Position> candidates ;
  for(const auto& t : partie.plateau.tuiles) {
    if(t.second.amenagement == Amenagement::VIDE) {
      if(initial) {
        candidates.inserer(t.first) ;
      } else {
        for(int i = 0; i < 4; ++i) {
          Position v = voisine(t.first, i) ;
          try {
            if(partie.plateau.tuiles.at(v).amenagement != Amenagement::VIDE) {
              candidates.inserer(t.first) ;
            }
          } catch(std::exception& e) {
            //la positione est hors du plateau
          }
        }
      }
    }
  }

  return candidates.retirer() ;
}

Position Joueur::amenager(const Partie& partie, Amenagement amenagement) {
  //lister les réservations
  Melangeur<Position> candidates ;
  for(const auto& t : partie.plateau.tuiles) {
    if(t.second.amenagement == Amenagement::RESERVEE && t.second.joueur == index) {
      candidates.inserer(t.first) ;
    }
  }

  //retourner une réservation au hasard
  return candidates.retirer() ;
}

int Joueur::miser(const Partie& partie, Amenagement amenagement) {
  return 0 ;
}
