#ifndef FRESHFISH_CONSTANTES_HPP
#define FRESHFISH_CONSTANTES_HPP

//types de ressources
enum struct Ressource {
  AVOCAT,
  BROCOLI,
  CAROTTE,
  DATTE,
  ECHALOTE
} ;

//tableau permettant d'itérer sur les ressources
static constexpr const Ressource toutes_ressources[] = {
  Ressource::AVOCAT,
  Ressource::BROCOLI,
  Ressource::CAROTTE,
  Ressource::DATTE,
  Ressource::ECHALOTE
} ;

//tous les aménagements
enum struct Amenagement {
  PRODUCTEUR,
  PRODUCTEUR_AVOCAT,
  PRODUCTEUR_BROCOLI,
  PRODUCTEUR_CAROTTE,
  PRODUCTEUR_DATTE,
  PRODUCTEUR_ECHALOTE,
  BOUTIQUE,
  BOUTIQUE_AVOCAT,
  BOUTIQUE_BROCOLI,
  BOUTIQUE_CAROTTE,
  BOUTIQUE_DATTE,
  BOUTIQUE_ECHALOTE,
  ARBRE,
  ROUTE,
  RESERVEE,
  VIDE
} ;

//chaîne de carractères pour afficher l'aménagement
const char* nom_amenagement(Amenagement t) ;

//BOUTIQUE_AVOCAT => BOUTIQUE
Amenagement type(Amenagement t) ;

//BOUTIQUE + AVOCAT => BOUTIQUE_AVOCAT
Amenagement specifie(Amenagement t, Ressource r) ;

//les cases construites ne permettent plus de circuler dans le graphe
bool construit(Amenagement t) ;

#endif
