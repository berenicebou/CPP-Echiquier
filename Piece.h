/**
 * Header de Piece.cxx
 *
 * @file Piece.h
 */

#if !defined Piece_h
#define Piece_h

//#include "Echiquier.h"
class Echiquier;

/**
 * Declaration d'une classe modélisant une piece de jeu d'echec.
 */
class Piece
{
protected:
  int m_x;
  int m_y;
  bool m_white;

public:
  Piece();
  virtual ~Piece();
  Piece( int x, int y, bool white );
  Piece( const Piece & autre );
  Piece & operator=(const Piece & autre);
  virtual bool mouvementValide(Echiquier &e, int x, int y);
  void mange(Echiquier &e, bool m_white, int x, int y);
  void init( int x, int y, bool white );
  void move( int x, int y );
  int x();
  int y();
  bool isWhite();
  bool isBlack();
  void affiche();
  virtual char myCode();
};

class Roi : public Piece
{
public:
  Roi(bool white);
  bool mouvementValide(Echiquier &e, int x, int y);
  char myCode();
  bool roque();
};

class Tour : virtual public Piece
{
public:
  Tour(bool white, bool left);
  bool mouvementValide(Echiquier &e, int x, int y);
  char myCode();
};

class Fou : virtual public Piece
{
public:
  Fou(bool white, bool left);
  bool mouvementValide(Echiquier &e, int x, int y);
  char myCode();
};

class Reine : public Tour, public Fou
{
public:
  Reine(bool white);
  bool mouvementValide(Echiquier &e, int x, int y);
  char myCode();
};

class Cavalier : public Tour, public Fou
{
public:
  Cavalier(bool white, bool left);
  bool mouvementValide(Echiquier &e, int x, int y);
  char myCode();
};
class Pion : virtual public Piece
{
public:
  Pion(bool white, int position);
  bool mouvementValide(Echiquier &e, int x, int y);
  char myCode();
};
#endif // !defined Piece_h
