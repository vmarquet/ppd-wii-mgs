#ifndef INGAME_H
#define INGAME_H

#include "defjeu.h"
#include "personnage.h"
#include <time.h>
#include "balle.h"
#include "mine.h"
#include <vector>



using namespace std;

class Ingame
{
 public:  // méthodes
  Ingame();   // constructeur
  void initSnake(Personnage& Snake);
  void initBoss(Personnage& Boss);
  void initSoldat(Personnage& Soldat);
  void moveSnake(Personnage& Snake, vector<Balle>& b, vector<Mine>& m, ir_t irPointer);
  void drawSoldat(Personnage& Soldat, Personnage Snake);
  void updateBoss(Personnage& Boss, Personnage& Snake, vector<Balle>& bBoss);
  void drawDecor(Personnage& Snake);
  void drawPlayer(Personnage& Snake);
  void drawProjectiles(Personnage Snake, vector<Balle>& b, Personnage& Boss);
  void drawMines(Personnage Snake, vector<Mine>& m);
  void drawBoss(Personnage Snake, Personnage& Boss, vector<Balle>& bBoss);
  void drawProjBoss(Personnage& Snake, Personnage Boss, vector<Balle>& bBoss);
  void destructeur();
  void gameOver();
  
  bool gameover;
  bool endOfLevel1;
  
  
 private:
  bool collision(Balle bullet, Personnage Boss, int w, int h);
  GRRLIB_texImg* chooseSnake(Personnage& Snake);
  GRRLIB_texImg* chooseSoldat(Personnage& Soldat);
  GRRLIB_texImg* decor01;
  GRRLIB_texImg* decor02; 
  GRRLIB_texImg* decor03;
  GRRLIB_texImg* decor04;
  GRRLIB_texImg* decor05;
  GRRLIB_texImg* decor06;
  GRRLIB_texImg* decor07;
  GRRLIB_texImg* decor08;
  GRRLIB_texImg* perso0;
  GRRLIB_texImg* perso1;
  GRRLIB_texImg* perso2;
  GRRLIB_texImg* perso3;
  GRRLIB_texImg* perso4;  
  GRRLIB_texImg* perso5;
  GRRLIB_texImg* perso6;
  GRRLIB_texImg* perso7;
  GRRLIB_texImg* perso8;
  GRRLIB_texImg* perso9;
  GRRLIB_texImg* persot1;
  GRRLIB_texImg* persot2;
  GRRLIB_texImg* persot3;
  GRRLIB_texImg* persot4;
  GRRLIB_texImg* persot5;
  GRRLIB_texImg* persot6;
  GRRLIB_texImg* persot7;
  GRRLIB_texImg* persot8;
  GRRLIB_texImg* perso10;
  GRRLIB_texImg* soldat0;
  GRRLIB_texImg* soldat1;
  GRRLIB_texImg* soldat2;
  GRRLIB_texImg* soldat3;
  GRRLIB_texImg* soldat4;
  GRRLIB_texImg* soldat5;
  GRRLIB_texImg* soldat6;
  GRRLIB_texImg* balle;
  GRRLIB_texImg* balleg;
  GRRLIB_texImg* mine;
  GRRLIB_texImg* mineExploded;
  GRRLIB_texImg* tex_sprite_png;
  GRRLIB_texImg* picGameover;
  GRRLIB_texImg* boss;  
};

#endif
