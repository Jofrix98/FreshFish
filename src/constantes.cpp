#include "constantes.hpp"

#include <stdexcept>

const char* nom_amenagement(Amenagement t) {
  static constexpr const char* noms_amenagements[] {
    "producteur",
    "producteur d'avocat",
    "producteur de brocoli",
    "producteur de carotte",
    "producteur de datte",
    "producteur d'échalote",
    "boutique",
    "boutique d'avocat",
    "boutique de brocoli",
    "boutique de carotte",
    "boutique de datte",
    "boutique d'échalote",
    "arbre",
    "route",
    "reservee",
    "vide"
  } ;

  return noms_amenagements[(int) t] ;
}

Amenagement type(Amenagement t) {
  if((int) t < (int) Amenagement::BOUTIQUE) {
    return Amenagement::PRODUCTEUR ;
  }
  if((int) t < (int) Amenagement::ARBRE) {
    return Amenagement::BOUTIQUE ;
  }
  return t ;
}

Amenagement specifie(Amenagement t, Ressource r) {
  if(t != Amenagement::PRODUCTEUR && t != Amenagement::BOUTIQUE) {
    throw std::invalid_argument(
        "la ressource de cet aménagement ne peut pas être spécifiée"
        ) ;
  }
  return (Amenagement) ( (int) t + (int) r + 1 ) ;
}

bool construit(Amenagement t) {
  return 
    t != Amenagement::ROUTE 
    && t != Amenagement::RESERVEE 
    && t != Amenagement::VIDE ;
}
