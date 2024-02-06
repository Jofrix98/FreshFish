#include "partie.hpp"
#include "melangeur.hpp"

#include <iostream>
#include <cstdlib>
#include <sstream>

Partie::Partie(int nb_joueurs) : pioche(nb_joueurs) {
  //création du plateau par défaut
  plateau.ajouter({0,0}, {9,9}) ;

  //placement des producteurs
  Melangeur<Position> candidates ;
  for(auto& t : plateau.tuiles) {
    candidates.inserer(t.first) ;
  }
  for(auto r : toutes_ressources) {
    Position pos = candidates.retirer() ;
    plateau.amenager(pos, specifie(Amenagement::PRODUCTEUR, r), 0) ;
  }

  //création des joueurs
  for(int i = 0; i < nb_joueurs; ++i) {
    joueurs.emplace_back(i) ;
    Position p = joueurs.back().reserver(*this, true) ;
    plateau.reserver(p, i) ;
    std::cout << "le joueur " << i << " réserve la position " << p << std::endl ;
  }

  //le joueur 0 commence
  joueur_courant = 0 ;
}

void Partie::lancer() {
  //utilitaire
  int nb_joueurs = joueurs.size() ;

#ifndef NO_GRAPHICS
  int i = 1 ;
  plateau.dessiner("output/plateau_0.svg", 100) ;
#endif

  while(pioche.taille() > 0) {
    if(joueurs[joueur_courant].agir(*this) == Joueur::Action::RESERVER) {
      //le joueur a choisi de réserver
      plateau.reserver(joueurs[joueur_courant].reserver(*this), joueur_courant) ;
      //TODO vérifier que le joueur ne triche pas
    } else {
      //récupérer un aménagement dans la pioche
      Amenagement a = pioche.piocher() ;

      if(a == Amenagement::ARBRE) {
        //aménagement inutile, laisser le joueur le placer 
        for(int i = 0; i < nb_joueurs; ++i) {
          try {
            plateau.amenager(joueurs[(joueur_courant + i)%nb_joueurs].amenager(*this, a), a, joueur_courant) ;
            break ;
          } catch(std::exception& a) {
            //en cas d'exception, le plateau est plein donc le joueur ne pouvait
            //pas réserver, mais il n'a pas de réservation disponible. Dans ce
            //cas, le prochain joueur ayant un jeton disponible doit aménager
          }
        }
      } else {
        //boutique, lister les joueurs pouvant la placer
        bool disponible[5] = {true, true, true, true, true} ;
        for(const auto& t : plateau.tuiles) {
          if(t.second.amenagement == a) {
            disponible[t.second.joueur] = false ;
          }
        }
        for(const auto& t : plateau.eliminees) {
          if(t.amenagement == a) {
            disponible[t.joueur] = false ;
          }
        }
        
        //encheres
        int vainqueur = -1 ;
        int prix = -1 ;
        for(int i = 0; i < nb_joueurs; ++i) {
          int joueur = (joueur_courant + i) % nb_joueurs ;
          if(disponible[joueur]) {
            //le joueur n'a pas encore placé cette boutique, demander sa mise
            int mise = joueurs[joueur].miser(*this, a) ;
            if(mise > prix) {
              vainqueur = joueur ;
              prix = mise ;
            }
          }
        }
        try {
          plateau.amenager(joueurs[vainqueur].amenager(*this, a), a, vainqueur) ;
        } catch(std::exception& e) {
          //le joueur n'avait aucune réservation, sa boutique est éliminée
          plateau.eliminees.push_back({a, vainqueur}) ;
        }
        //TODO gérer les sous
      }
    }



    std::cout << "=========================================" << std::endl ;
    //std::system("clear") ;
    std::cout << plateau << std::endl ;
    //std::system("read a") ;
    
#ifndef NO_GRAPHICS
    std::stringstream ss ;
    ss << "output/plateau_" << i << ".svg" ;
    ++i ;
    plateau.dessiner(ss.str(), 100) ;
#endif

    joueur_courant = (joueur_courant + 1) % nb_joueurs ;
  }
}
