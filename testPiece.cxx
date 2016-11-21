/**
 * Programme test de Piece
 *
 * @file testPiece.cxx
 */

// Utile pour l'affichage
#include <iostream>
#include "Piece.h"
#include "Joueur.h"
#include "Echiquier.h"

// Pour utiliser les flux de iostream sans mettre "std::" tout le temps.
using namespace std;

bool compare(Piece p1, Piece p2)
{
  return ( (p1.x()==p2.x()) && (p1.y()==p2.y()) );
}


/**
 * Programme principal
 */
int main( int argc, char** argv )
{
  // instancie un objet p1 de type Piece
  Piece p1;
  Piece p2(4,4,false);
  // p1 est une piece blanche de coordonnees (3,3)
  p1.init( 3, 3, true );

  // On l'affiche
  p1.affiche();
  p2.affiche();

  if (compare(p1,p2))
    cout << "Piece dans la meme positions" << endl;
  else
    cout << "Pieces dans une position differentes" << endl;

  p1=p2;

  //Piece tbl[4];

  //Joueur jb(true);
  JoueurBlanc jb;
  //Joueur jn(false);
  JoueurNoir jn;
  jb.affiche();
  jn.affiche();

  Echiquier e;
  jb.placerPieces(e);
  jn.placerPieces(e);
  int i = 0;

  while( i <50){

e.affiche();

jb.unTourBlanc(e);

e.affiche();

jb.unTourNoir(e);

  }


}
