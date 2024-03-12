#include "partie.hpp"
#include "melangeur.hpp"
#include "plateau.hpp"


#include <iostream>
#include <cstdlib>
#include <sstream>

int main() {

  Plateau p ;
  p.ajouter({0,0}, {9,9}) ;
  Position tab[] = {{1, 3}, {7, 4}, {4, 4}, {5, 1}, {2, 1}, {0, 4},
                    {6, 3}, {9, 3}, {8, 5}, {3, 4}, {4, 6}, {7, 3},
                    {0, 3}, {9, 4}, {4, 5}, {5, 7}, {0, 0}, {3, 1},
                    {0, 5}, {3, 3}, {5, 4}, {8, 9}, {7, 2}, {4, 0},
                    {0, 6}, {4, 8}, {3, 0}, {5, 0}, {6, 4}, {5, 3},
                    {1, 8}, {8, 7}, {9, 5}, {8, 8}, {5, 8}, {9, 0},
                    {4, 7}, {9, 9}, {1, 6}, {7, 1}, {5, 6}, {1, 7},
                    {9, 2}, {7, 5}, {0, 1}, {3, 5}, {7, 8}, {2, 7},
                    {7, 7}, {9, 1}, {2, 8}
};


/*p.tuiles[{0,0}].amenagement = Amenagement::ARBRE;
p.tuiles[{0,1}].amenagement = Amenagement::ARBRE;
p.tuiles[{1,1}].amenagement = Amenagement::ARBRE;
placer_routes(p);
std::cout << p << std::endl ;

exit(1);*/
 
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
      /*for(int i = 0; i < 51;i++){
        if(tab[i] == pos){
          //p.reserver(pos, 0) ;
          p.amenager(pos, Amenagement::ARBRE, 0) ;
        }
        
      }*/
      //p.reserver(pos, 0) ;
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
