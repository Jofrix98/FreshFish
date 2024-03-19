#include "constantes.hpp"
#include "plateau.hpp"
#include "console_pad.hpp"

#include <stdexcept>
#include <sstream>
#include <cassert>
#include "melangeur.hpp"
#include <unordered_map>
#include <vector>
#include <algorithm>




static void explorer(Plateau& p, const Position& pos) {
 
  p.tuiles.at(pos).remontee = p.tuiles.at(pos).profondeur;
  for(int i=0;i<4;i++){
    
    if(p.tuiles.find(voisine(pos, i)) != p.tuiles.end()){
      
      arc A;
      A.debut = pos;
      A.fin = voisine(pos, i);
      if(!(p.tuiles.at(voisine(pos, i)).amenagement == Amenagement::VIDE)){
        A.type = type_arc::IMPASSE;
          
        /*std::cout << "position Debut: " << A.debut << std::endl;
        std::cout << "position fin: " << A.fin << std::endl;
        std::cout << "Type lien: " << A.type << std::endl;*/

      }else if(!p.tuiles.at(voisine(pos, i)).estVisite) {
        A.type = type_arc::UTILISE;
      } else {
        A.type = type_arc::IGNORE;
      }
    
      p.tab_arc.push_back(A);

      


      if((!p.tuiles.at(voisine(pos, i)).estVisite) 
          && 
        (p.tuiles.at(voisine(pos, i)).amenagement == Amenagement::VIDE || p.tuiles.at(voisine(pos, i)).amenagement == Amenagement::ROUTE)){
            p.tuiles.at(voisine(pos, i)).estVisite = true;
            int profondeur_voisin = p.tuiles.at(voisine(pos, i)).profondeur;
            int profondeur_courant = p.tuiles.at(pos).profondeur;
            profondeur_voisin =  profondeur_courant + 1;
            p.tuiles.at(voisine(pos, i)).profondeur = profondeur_voisin;
            
            explorer(p, voisine(pos, i));  
    }

    if(p.tab_arc.back().type == type_arc::UTILISE ){
      p.tuiles.at(pos).remontee = fmin(p.tuiles.at(pos).remontee,p.tuiles.at(voisine(pos, i)).remontee);

    } else if(p.tab_arc.back().type == type_arc::IGNORE ){
      p.tuiles.at(pos).remontee = fmin(p.tuiles.at(pos).remontee,p.tuiles.at(voisine(pos, i)).profondeur);
    }

  }

}}

void parcours_profondeur(Plateau& p, const Position& pos){
  for(auto& t : p.tuiles){
    t.second.estVisite = false;
    t.second.profondeur = 0;
    t.second.remontee = 0;
  }

  p.tab_arc.clear();
  p.tuiles.at(pos).estVisite = true;
  explorer(p, pos);

}

static bool clos(Plateau& p, const Position& pos){

    int t = 0;
    for(int i=0;i<4;i++){
    
      if((p.tuiles.find(voisine(pos, i)) == p.tuiles.end())||
      !(p.tuiles.at(voisine(pos, i)).amenagement == Amenagement::VIDE || 
      p.tuiles.at(voisine(pos, i)).amenagement == Amenagement::ROUTE )){
        t++;
  
    }

  }

  if(t == 4){
    return true;
  }

  return false;

}


 void placer_routes_naive(Plateau& p) {
  for(auto& t : p.tuiles){

    if(t.second.amenagement == Amenagement::VIDE){
      t.second.amenagement = Amenagement::ARBRE;

      for(auto& tp : p.tuiles){
        if(!(tp.second.amenagement == Amenagement::VIDE || tp.second.amenagement == Amenagement::ROUTE ) && clos(p, tp.first)){
          t.second.amenagement = Amenagement::ROUTE;   
        }

        if(tp.second.amenagement == Amenagement::VIDE || tp.second.amenagement == Amenagement::ROUTE ){
          parcours_profondeur(p, tp.first);
          for(auto& tpp : p.tuiles){
            if(!tpp.second.estVisite  && (tpp.second.amenagement == Amenagement::VIDE || tpp.second.amenagement == Amenagement::ROUTE)){
             t.second.amenagement = Amenagement::ROUTE;
             break;
            }          
          }         
        }
      }
      if(t.second.amenagement == Amenagement::ARBRE){
        t.second.amenagement = Amenagement::VIDE;
      }     
    }   
  }
}

// Fonction pour placer les routes en utilisant l'algorithme élaboré
void placer_routes_elabore(Plateau& p) {
  for (auto& tuile : p.tuiles) {
        tuile.second.profondeur = 0;
        tuile.second.remontee = 0;
    }
}


void Plateau::ajouter(const Position& pos) {
  if(tuiles.find(pos) != tuiles.end()) {
    throw std::domain_error(
        "une tuile existe déjà à cet endroit"
        ) ;
  }

  Tuile& nouveau = tuiles[pos] ;
  nouveau.amenagement = Amenagement::VIDE ;
  nouveau.joueur = -1 ;
}

void Plateau::ajouter(const Position& pos_min, const Position& pos_max) {
  for(int i = pos_min.first; i <= pos_max.first; ++i) {
    for(int j = pos_min.second; j <= pos_max.second; ++j) {
      try {
        ajouter({i,j}) ;
      } catch(std::exception& e) {
        //erreur ignorée pour pouvoir simplement créer un plateau par blocs
      }
    }
  }
}

void Plateau::reserver(const Position& pos, int joueur) {
  Tuile& t = tuiles.at(pos) ;

  if(t.joueur >= 0) {
    throw std::invalid_argument(
        "cette tuile est déjà réservée"
        ) ;
  }

  t.joueur = joueur ;
  t.amenagement = Amenagement::RESERVEE ;
}

void Plateau::amenager(const Position& pos, Amenagement amenagement, int joueur) {
  Tuile& t = tuiles.at(pos) ;


  /*if(t.amenagement != Amenagement::RESERVEE) {
    throw std::invalid_argument(
        "cette tuile n'a pas été réservée"
        ) ;
  }

  if(t.joueur != joueur) {
    throw std::invalid_argument(
        "cette tuile n'est pas réservée pour le joueur"
        ) ;
  }*/


  t.joueur = joueur ;
  t.amenagement = amenagement ;
  placer_routes_naive(*this) ;
}

std::ostream& operator<<(std::ostream& out, const Plateau& plateau) {
  //pas de tuile pas d'affichage
  if(plateau.tuiles.size() == 0) return out ;

  //dimensions du plateau
  int lmin, lmax, cmin, cmax ;
  lmin = lmax = plateau.tuiles.begin()->first.first ;
  cmin = cmax = plateau.tuiles.begin()->first.second ;
  for(auto& t : plateau.tuiles) {
    lmin = std::min(lmin, t.first.first) ;
    lmax = std::max(lmax, t.first.first) ;
    cmin = std::min(cmin, t.first.second) ;
    cmax = std::max(cmax, t.first.second) ;
  }

  //creation d'un buffer de suffisamment de lignes
  int eliminees = plateau.eliminees.size() > 0 ? 4 : 0 ;
  ConsolePad pad((lmax - lmin + 1) * 2 + 1 + eliminees) ;

  //dessin d'une tuile
  auto dessiner = [&] (const Position& pos, const Tuile& tuile) {
    //ligne et colonne dans le pad
    unsigned int l = 2*(pos.first - lmin) ;
    unsigned int c = 4*(pos.second - cmin) ;

    //tuile vide
    pad.moveto(l, c) ;
    pad 
      << "+   +" << std::endl
      << "     " << std::endl
      << "+   +" ;

    //murs
    static constexpr const int positions_murs[] = {
      0, 1,
      1, 4,
      2, 1,
      1, 0
    } ;
    for(int i = 0; i < 4; ++i) {
      Position v = voisine(pos, i) ;
      if(plateau.tuiles.find(v) == plateau.tuiles.end()) {
        pad.moveto(l+positions_murs[2*i], c+positions_murs[2*i+1]) ;
        if(i%2 == 1) {
          pad << "|" ;
        } else {
          pad << "---" ;
        }
      }
    }

    //contenu possible des tuiles
    static constexpr const char* txt_amenagements[] = {
      "+ +", "+A+", "+B+", "+C+", "+D+", "+E+",
      "$ $", "$A$", "$B$", "$C$", "$D$", "$E$",
      "{:}",
      " # ",
      " @ ",
      "   "
    } ;
    static constexpr const char* couleurs_joueurs[] = {
#ifndef NO_COLOR
      "\x1B[38;5;38m", //bleu
      "\x1B[38;5;208m", //orange
      "\x1B[38;5;135m", //violet
      "\x1B[38;5;11m", //jaune
      "\x1B[38;5;206m" //rose
      //"\x1B[38;5;124m" //rouge
#else
      ""
#endif
    } ;
    static constexpr const int nb_couleurs = sizeof(couleurs_joueurs) / sizeof(char*) ;
  
    static constexpr const char* couleur_defaut = 
#ifndef NO_COLOR
      "\x1B[39m"
#else
      ""
#endif
    ;

    pad.moveto(l+1, c+1) ;
    Amenagement base = type(tuile.amenagement) ;
    if(base == Amenagement::BOUTIQUE || base == Amenagement::RESERVEE) {
      pad << couleurs_joueurs[tuile.joueur % nb_couleurs] ;
    }
    pad << txt_amenagements[(int) tuile.amenagement] ;
    if(base == Amenagement::BOUTIQUE || base == Amenagement::RESERVEE) {
      pad << couleur_defaut ;
    }
  } ;

  //dessin
  for(auto& t : plateau.tuiles) {
    dessiner(t.first, t.second) ;
  }

  //tuiles eliminees
  int nb_eliminees = plateau.eliminees.size() ;
  for(int i = 0; i < nb_eliminees; ++i) {
    dessiner({lmax + 2, cmin + i}, plateau.eliminees[i]) ;
  }


  out << pad.lines() ;
  return out ;
}


#ifndef NO_GRAPHICS
  #include <librsvg-2.0/librsvg/rsvg.h>
  #include <cairo/cairo.h>
  #include <cairo/cairo-svg.h>

void Plateau::dessiner(const std::string& cible, int unit, float margin, const std::string& style) {
  //pas de tuile pas d'affichage
  if(tuiles.size() == 0) return ;

  //dimensions du plateau
  int lmin, lmax, cmin, cmax ;
  lmin = lmax = tuiles.begin()->first.first ;
  cmin = cmax = tuiles.begin()->first.second ;
  for(auto& t : tuiles) {
    lmin = std::min(lmin, t.first.first) ;
    lmax = std::max(lmax, t.first.first) ;
    cmin = std::min(cmin, t.first.second) ;
    cmax = std::max(cmax, t.first.second) ;
  }

  //chargement du fichier de style svg
#ifndef FF_ASSETS
#define FF_ASSETS "../assets/"
#endif
  std::stringstream style_path ;
  style_path << FF_ASSETS << style ;
  GError* svg_error = nullptr ;
  RsvgHandle* style_handle = rsvg_handle_new_from_file(style_path.str().c_str(), &svg_error) ;
  if(svg_error) {
    throw std::invalid_argument("fichier de style introuvable") ;
  }

  //creation d'une surface cairo pour enregistrer le dessin
  cairo_surface_t* record = cairo_recording_surface_create(CAIRO_CONTENT_COLOR_ALPHA, nullptr) ;

  //contexte de dessin
  cairo_t* cr = cairo_create(record) ;

  //dessin d'site
  auto dessiner = [&] (const Position& pos, const Tuile& tuile) {
    //fenetre a dessiner
    double x = pos.second ;
    double y = pos.first ;
    RsvgRectangle rect({x, y, 1, 1}) ;

    //id dans le fichier de style svg
    static constexpr const char* ids[] {
      "producteur",
      "producteur_avocat",
      "producteur_brocoli",
      "producteur_carotte",
      "producteur_datte",
      "producteur_echalote",
      "boutique",
      "boutique_avocat",
      "boutique_brocoli",
      "boutique_carotte",
      "boutique_datte",
      "boutique_echalote",
      "inutile",
      "route",
      "reservee",
      "vide"
    } ;

    std::stringstream svg_id ;
    svg_id << "#" << ids[(int) tuile.amenagement] ;
    Amenagement base = type(tuile.amenagement) ;
    if(base == Amenagement::BOUTIQUE || base == Amenagement::RESERVEE) {
      svg_id << "_" << tuile.joueur ;
    }

    //dessin
    GError* error = nullptr ;
    rsvg_handle_render_layer(style_handle, cr, svg_id.str().c_str(), &rect, &error) ;
    if(error) {
      std::cout << "got an error : " << svg_id.str() << " " << x << " " << y << std::endl ;
    }
  } ;

  //dessin
  for(auto& t : tuiles) {
    dessiner(t.first, t.second) ;
  }

  //tuiles eliminees
  int nb_eliminees = eliminees.size() ;
  for(int i = 0; i < nb_eliminees; ++i) {
    dessiner({lmax + 2, cmin + i}, eliminees[i]) ;
  }

  cairo_surface_flush(record) ;


  //finalisation du dessin
  cairo_destroy(cr) ;
  g_object_unref(style_handle) ;

  //export
  double x0, y0, largeur, hauteur ;
  cairo_recording_surface_ink_extents(record, &x0, &y0, &largeur, &hauteur) ;

  //il semble qu'il y ait un bug dans le calcul des largeur, hauteur, et origine
  largeur -= 2 ;
  hauteur -= 2 ;
  x0 += 1 ;
  y0 += 1 ;

  //ouvrir une surface pour l'export
  int umargin = margin * unit ;
  cairo_surface_t* img ;
  const std::string& extension = cible.substr(cible.find_last_of(".") + 1) ;
  if(extension == "svg") {
     img = cairo_svg_surface_create(
         cible.c_str(), unit*largeur + 2*umargin, unit*hauteur + 2*umargin
         ) ;
  } else if(extension == "png") {
    img = cairo_image_surface_create(
        CAIRO_FORMAT_ARGB32, unit*largeur + 2*umargin, unit*hauteur + 2*umargin
        ) ;
  } else {
    throw std::invalid_argument("seul l'export svg ou png est possible") ;
  }

  //creer un contexte pour l'export
  cr = cairo_create(img) ;
  cairo_translate(cr, umargin, umargin) ;
  cairo_scale(cr, unit, unit) ;

  //rejouer l'enregistrement
  cairo_set_source_surface(cr, record, -x0, -y0) ;
  cairo_paint(cr) ;
  cairo_show_page(cr) ;

  //finalisation de l'image
  cairo_surface_flush(img) ;

  //ecriture du png si besoin
  if(extension == "png") {
    cairo_surface_write_to_png(img, cible.c_str()) ;
  }

  //destruction du contexte
  cairo_destroy(cr) ;

  //destruction de la surface d'export
  cairo_surface_finish(img) ;
  cairo_surface_destroy(img) ;
  cairo_surface_finish(record) ;
  cairo_surface_destroy(record) ;
}

#endif
