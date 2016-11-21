#include <iostream>
#include "Joueur.h"

// Pour utiliser les flux de iostream sans mettre "std::" tout le temps.
using namespace std;

Joueur::Joueur()
{
  //cout << "Constructeur Joueur" << endl;
}

Joueur::~Joueur()
{
  vector<Piece*>::iterator p = m_pieces.begin();
  while ( p != m_pieces.end() )
    {
      delete *p;
      p++;
    }
  //cout << "Destructeur Joueur" << endl;
}

Joueur::Joueur(bool white)
{

}

void
Joueur::placerPieces(Echiquier &e)
{
  vector<Piece*>::iterator p = m_pieces.begin();
  while ( p != m_pieces.end() )
    {
      e.placer((Piece*)*p);
      p++;
    }
  /*
  for (int i=0;i<16;i++)
    e.placer(m_pieces+i);
  */
}


bool
verifCoord(int x, int y)
{
       if((x ||y) > 8 || (x ||y) < 1)
    {

        return false;
    }
    return true;
}
bool
verifPiece(Echiquier &e, int x, int y)
{
  if(e.getPiece( x,y) != NULL){
    return true;
      }
      return false;
}

void
Joueur::unTourBlanc(Echiquier &e)
{
    cout <<"Tour du joueur Blanc"<<endl;
    bool color = false;
    int first_X;
    int first_y;
    int last_X;
    int last_y;

    cout <<"Choisir les coordonnees de la piece en en x"<<endl;
    cin >> first_X;
    cout <<"Choisir les coordonnees de la piece en y"<<endl;
    cin >> first_y;
    verifCoord(first_X,first_y );

    if(e.getPiece(first_X,first_y)->isWhite() == true)
    {
      color = true;
    }
    while((verifPiece(e, first_X,first_y) || color )== false )
    {
        cout <<"les coordonnees de la piece sont non valide"<<endl;
        cout <<"Choisir une autre une coordonnee de la piece en x valide "<<endl;
        cin >> first_X;
        cout <<"Choisir une autre une coordonnee de la piece en y valide "<<endl;
        cin >> first_y;
        verifPiece(e, first_X,first_y);
    }

    cout <<"Choisir la coordonnee du deplacement de la piece en x"<<endl;
    cin >> last_X;
    cout <<"Choisir la coordonnee du deplacement de la piece en y"<<endl;
    cin >> last_y;

    verifCoord(first_X,first_y );
    while(verifCoord(last_X,last_y) == false)
    {
        cout <<"Choisir une coordonnee du deplacement de la piece en x valide "<<endl;
        cin >> last_X;
        cout <<"Choisir une coordonnee du deplacement de la piece en y valide"<<endl;
        cin >> last_y;
        verifCoord(last_X,last_y);
    }

        while(e.getPiece(first_X, first_y)->mouvementValide(e, last_X, last_y) == false)
        {
            cout <<"Le deplacement est impossible"<<endl;
        cout <<"Choisir une coordonnee pour un mouvement possible en x"<<endl;
        cin >> last_X;
        cout <<"Choisir une coordonnee pour un mouvement possible  en y"<<endl;
        cin >> last_y;
        verifCoord(last_X,last_y);
        }
    if(e.getPiece(first_X, first_y)->mouvementValide(e, last_X, last_y)){
        if(e.getPiece(last_X, last_y) !=NULL)
        {
            e.getPiece(first_X, first_y)->mange(e, true, last_X, last_y);
            cout <<"Vous avez mangé la piece du joueur adverse"<<endl;

        }

    e.deplacer(e.getPiece(first_X, first_y),last_X, last_y);


    }
}


 void
Joueur::unTourNoir(Echiquier &e)
{
    cout <<"Tour du joueur Noir"<<endl;
    bool color = false;
    int first_X;
    int first_y;

    int last_X;
    int last_y;
    cout <<"Choisir les coordonnees de la piece en x"<<endl;
    cin >> first_X;
    cout <<"Choisir les coordonnees de la piece en y"<<endl;
    cin >> first_y;
    verifCoord(first_X,first_y );
    if(e.getPiece(first_X,first_y)->isWhite() != true)
    {
      color = true;
    }
    while((verifPiece(e,first_X,first_y) || color )== false )
    {
        cout <<"Les coordonnees de la piece sont non valide"<<endl;
        cout <<"Choisir les coordonnees de la piece en x"<<endl;
        cin >> first_X;
        cout <<"Choisir les coordonnees de la piece en y"<<endl;
        cin >> first_y;
        verifPiece(e, first_X,first_y);
    }

    cout <<"Choisir les coordonnees du deplacement de la piece en x"<<endl;
    cin >> last_X;
    cout <<"Choisir les coordonnees du deplacement de la piece en y"<<endl;
    cin >> last_y;

    verifCoord(first_X,first_y );
    while(verifCoord(last_X,last_y) == false)
    {
        cout <<"Le deplacement est impossible"<<endl;
        cout <<"Choisir les coordonnees du deplacement de la piece en x"<<endl;
        cin >> last_X;
        cout <<"Choisir les coordonnees du deplacement de la piece en y"<<endl;
        cin >> last_y;
        verifCoord(last_X,last_y);
    }

    if(e.getPiece(first_X, first_y)->mouvementValide(e, last_X, last_y)){
        if(e.getPiece(last_X, last_y) !=NULL)
        {
            e.getPiece(first_X, first_y)->mange(e, false, last_X, last_y);
            cout <<"Vous avez mangé une piece du joueur adverse"<<endl;
        }
    e.deplacer(e.getPiece(first_X, first_y),last_X, last_y);

    }



}



bool
JoueurBlanc::isWhite()
{
  return true;
}

bool
JoueurNoir::isWhite()
{
  return false;
}

void
Joueur::affiche()
{
  vector<Piece*>::iterator p = m_pieces.begin();
  while ( p != m_pieces.end() )
    {
      (*p)->affiche();
      p++;
    }
  /*
  for (int i=0;i<16;i++)
    m_pieces[i]->affiche();
  */
}

JoueurBlanc::JoueurBlanc() //: Joueur(true)
{
  Roi *pr = new Roi(true);
  Reine *pq = new Reine(true);
  Cavalier *pcl = new Cavalier(true,true);
  Cavalier *pcr = new Cavalier(true,false);
  Fou *pfl = new Fou(true,true);
  Fou *pfr = new Fou(true,false);
  Tour *ptl = new Tour(true,true);
  Tour *ptr = new Tour(true,false);

  m_pieces.push_back(pr);
  m_pieces.push_back(pq);
  m_pieces.push_back(pcl);
  m_pieces.push_back(pcr);
  m_pieces.push_back(pfl);
  m_pieces.push_back(pfr);
  m_pieces.push_back(ptl);
  m_pieces.push_back(ptr);

  for (int i=1; i<=8; i++)
    {
      Pion *p = new Pion (true,i);
      m_pieces.push_back(p);
    }
  cout << "Constructeur Joueur Blanc" << endl;
}

JoueurNoir::JoueurNoir() //: Joueur(false)
{
  Roi *pr = new Roi(false);
  Reine *pq = new Reine(false);
  Cavalier *pcl = new Cavalier(false,true);
  Cavalier *pcr = new Cavalier(false,false);
  Fou *pfl = new Fou(false,true);
  Fou *pfr = new Fou(false,false);
  Tour *ptl = new Tour(false,true);
  Tour *ptr = new Tour(false,false);

  m_pieces.push_back(pr);
  m_pieces.push_back(pq);
  m_pieces.push_back(pcl);
  m_pieces.push_back(pcr);
  m_pieces.push_back(pfl);
  m_pieces.push_back(pfr);
  m_pieces.push_back(ptl);
  m_pieces.push_back(ptr);

  for (int i=1; i<=8; i++)
    {
      Pion  *p = new Pion (false,i);
      m_pieces.push_back(p);
    }
  cout << "Constructeur Joueur Noir" << endl;
}
