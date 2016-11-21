/**
 * Header de Joueur.cxx
 *
 * @file Joueur.h
 */

#if !defined Joueur_h
#define Joueur_h

#include <vector>
#include "Piece.h"
#include "Echiquier.h"

using namespace std;

/**
 * Declaration d'une classe modelisant un joueur.
 */
class Joueur
{
protected:
  vector<Piece*> m_pieces;

public:
 ~Joueur();
  Joueur();
  Joueur( bool white );

  void placerPieces(Echiquier &e);
  virtual bool isWhite()=0;
  void affiche();
  void unTourBlanc(Echiquier &e);
  void unTourNoir(Echiquier &e);

};

class JoueurBlanc : public Joueur
{
 public:
  JoueurBlanc();
  bool isWhite();
};

class JoueurNoir : public Joueur
{
 public:
  JoueurNoir();
  bool isWhite();
};

#endif
