/**
 * Mise en oeuvre de Piece.h
 *
 * @file Piece.cxx
 */

// A besoin de la declaration de la classe
#include <stdlib.h>
#include <iostream>
#include "Piece.h"
#include "Echiquier.h"
// Pour utiliser les flux de iostream sans mettre "std::" tout le temps.
using namespace std;

Piece::Piece()
{
  // ne fait rien => objet instancie mais non valide.
  cout << "Constructeur Piece" << endl;
}

Piece::~Piece()
{
  // cout << "Destructeur Piece" << endl;
}

Piece::Piece(const Piece & autre)
{
   cout << "Constructeur Piece par copie" << endl;
   m_x=autre.m_x;
   m_y=autre.m_y;
   m_white=autre.m_white;
}

Piece &
Piece::operator=(const Piece & autre)
{
  cout << "Operateur affectation Piece" << endl;
  m_x=autre.m_x;
  m_y=autre.m_y;
  m_white=autre.m_white;
  return *this;
}

Piece::Piece( int x, int y, bool white )
{
  //cout << "Constructeur Piece Specialise" << endl;
  m_x = x;
  m_y = y;
  m_white = white;
}

bool
Piece::mouvementValide(Echiquier &e, int x, int y)
{

}
void
Piece::mange(Echiquier &e, bool m_white,  int x, int y)
{
    if((e.getPiece(x, y) != NULL) && e.getPiece( x,  y)->isWhite() != m_white)
    {
    e.enleverPiece( x,  y);

    }
}

void
Piece::init( int x, int y, bool white )
{
  m_x = x;
  m_y = y;
  m_white = white;
}

void
Piece::move( int x, int y )
{
  m_x = x;
  m_y = y;
}

int
Piece::x()
{
  return m_x;
}

int
Piece::y()
{
  return m_y;
}

bool
Piece::isWhite()
{
  return m_white;
}


bool
Piece::isBlack()
{
  return !m_white;
}

void
Piece::affiche()
{
  cout << "Piece: x=" << m_x << " y=" << m_y << " "
       << ( m_white ? "blanche" : "noire" ) << endl;
}

char
Piece::myCode()
{
  if (m_white) return 'B';
  return 'N';
}

Roi::Roi(bool white) : Piece(5,(white?1:8),white)
{
  //cout << "Constructeur Roi" << endl;
}

bool
Roi::roque()
{
  //cout << "Roque Roi" << endl;
  return false;
}

Tour::Tour(bool white, bool left) : Piece((left?1:8),(white?1:8),white)
{
  //cout << "Constructeur Tour" << endl;
}

Fou::Fou(bool white, bool left) : Piece((left?3:6),(white?1:8),white)
{
  //cout << "Constructeur Fou" << endl;
}
Cavalier::Cavalier(bool white, bool left) : Piece((left?2:7),(white?1:8),white),Fou(white,true), Tour(white,true)
{
  //cout << "Constructeur Cavalier" << endl;
}

Reine::Reine(bool white) : Piece(4,(white?1:8),white), Fou(white,true), Tour(white,true)
{
 // cout << "Constructeur Reine" << endl;
}

Pion::Pion(bool white, int position) : Piece(position, white?2:7,white)
{
//cout << "Constructeur Pion" << endl;
}

bool
Roi::mouvementValide(Echiquier &e, int x, int y)
{
if(Piece::mouvementValide(e,x,y))
{
    if((x-m_x)<=1 && (y-m_y)<=1 && (x!=m_x || y!=m_y))
    {
        cout << "Mouvement valide" << endl;
        return true;
    }
}
return false;
}
bool
Tour::mouvementValide(Echiquier &e, int x, int y)
{
    if(Piece::mouvementValide(e,x,y))
    {
       if((x && y != 0))
       {
         cout << "mouvement non valide de Tour" << endl;
         return false;
       }
        if(y == 0)
        {
            for(int i=min(x,m_x)+1;i<max(x,m_x);i++)
            {
                if(e.getPiece(i, y))
                {
                    cout << "Mouvement non valde, une piece est sur le trajet" << endl;
                    return false;
                }
            }
        }
         else if(x == m_x)
        {
            for(int i=min(y,m_y)+1;i<max(y,m_y);i++)
            {
                if(e.getPiece(x, i))
                {
                    cout << "Impossible d'aller sur la case désigné" << endl;
                    return false;
                }
            }
        }
        cout << "Mouvement valide" << endl;
        return true;
    }
    cout << "mouvementValide Tour" << endl;
    return true;
}
bool
Fou::mouvementValide(Echiquier &e, int x, int y)
{
    if(Piece::mouvementValide(e,x,y))
    {
        if((x||y == 0) || (x !=y))
        {

                cout << "mouvement non valide Fou" << endl;
               return false;
        }
        else
        {
            if((m_white == true) && (e.getPiece(x,y)->isBlack() ==true))
            {
            cout << "mouvementValide Fou" << endl;
            return true;
            }
            else if ((m_white == false) && (e.getPiece(x,y)->isWhite() ==true))
            {
            cout << "mouvementValide Fou" << endl;
            return true;
            }
            else
            {
            cout << "Une piece de cette couleur est déjà sur cette case"  << endl;
            return false;
            }
        }
    }
}

bool
Reine::mouvementValide(Echiquier &e, int x, int y)
{

  if((Fou::mouvementValide(e,x,y) || Tour::mouvementValide(e,x,y)) == true){
    cout << "mouvement Valide Reine" << endl;
    return true;
  }
  else{
    cout << "mouvement non Valide Reine" << endl;
    return false;
  }
}

bool
Cavalier::mouvementValide(Echiquier &e, int x, int y)
{

    if(Piece::mouvementValide(e,x,y))
    {
        if((abs(m_x-x) >2 )&& (abs(m_y-y)>1) )
        {
            cout << "mouvement non Valide Cavalier" << endl;
            return false;
        }
        else if((abs(m_x-x) >1 )&& (abs(m_y-y)>2)){
        cout << "mouvement non Valide Cavalier" << endl;
        return false;
        }
        else
        {

            if((Fou::mouvementValide(e,x,y) || Tour::mouvementValide(e,x,y)) ==false)
            {
                cout << "mouvement  Cavalier Valide" << endl;
                return true;
            }else
            {
                cout << "mouvement  Cavalier non Valide" << endl;
                return false;
            }

        }
    }
}

bool
Pion::mouvementValide(Echiquier &e, int x, int y)
{
    if(Piece::mouvementValide(e,x,y))
    {
        if(m_white == true)
        {
            if(m_y == 2 && m_y +2 == y && (e.getPiece(m_x, 3)==NULL &&e.getPiece(m_y, 4)==NULL))
            {
                cout << "Premier deplacement accorde" << endl;
                return true;
            }
            else if((m_y +1 == y && m_x == x) && e.getPiece(m_x, m_y+1)==NULL)
            {
                cout << "Deplacement en ligne accorde" << endl;
                return true;
            }
            else if(((abs(m_x - x && m_y - y)) ==1) && (e.getPiece(x,y)!=NULL)&&(e.getPiece(x,y)->isWhite()==false))
            {
            cout << "Deplacement en diagonal accorde" << endl;

           // Piece.mange(&e, e.getPiece(m_y, m_x).m_white(),  x,  y);

                return true;
            }else
            {
               cout << "Deplacement impossible" << endl;
               return false;
            }
        }else
        {
            if(m_x == 7 && m_x -2 == x && (e.getPiece(m_y, 6)==NULL &&e.getPiece(m_y, 5)==NULL))
            {
                cout << "Premier deplacement accorde" << endl;
                return true;
            }
            else if((m_x -1 == x && m_y == y) && e.getPiece(m_y, m_x+1)==NULL)
            {
                cout << "Deplacement en ligne accorde" << endl;
                return true;
            }
            else if((x && y) ==1 && (e.getPiece(abs(m_y -y),m_x+1)!=NULL)&&(e.getPiece(abs(m_y -y),m_x+1)->isWhite()==true))
            {
            cout << "Deplacement en diagonal accorde" << endl;
                return true;
            }else
            {
               cout << "Deplacement impossible" << endl;
               return false;
            }
        }

    }
/*

    if(Piece::mouvementValide(e,x,y))
    {
        if((m_white && y == 4 && m_y==2 && e.getPiece(m_x, 3)==NULL) || ((!m_white) && y == 5 && m_y==7 && e.getPiece(m_x, 6)==NULL))
        {
            cout << "Premier deplacement accorde" << endl;
            return true;
        }
        else if((m_white && y == m_y+1 && (x-m_x)<=1) || ((!m_white) && y == m_y-1 && (x-m_x)<=1))
        {
            cout << "Mouvement possible" << endl;
            if(x-m_x==1)
            {
                cout << "deplacement impossible" << endl;
                if(e.getPiece(x,y)!= NULL)
                {
                    if(e.getPiece(x,y)->isWhite() != m_white)
                    {
                        cout << "Déplacemet possible, prend une piece adverse" << endl;
                        return true;
                    }
                }
                return false;
            }
            if(e.getPiece(x,y)==NULL)
            {
                return true;
            }
        }
    }
    return false;*/
}
char
Pion::myCode()
{
    if (m_white) return 'P';
return 'p';
}
char
Roi::myCode()
{
  if (m_white) return 'R';
  return 'r';
}

char
Tour::myCode()
{
  if (m_white) return 'T';
  return 't';
}

char
Fou::myCode()
{
  if (m_white) return 'F';
  return 'f';
}
char
Cavalier::myCode()
{
  if (m_white) return 'C';
  return 'c';
}
char
Reine::myCode()
{
  if (m_white) return 'Q';
  return 'q';
}
