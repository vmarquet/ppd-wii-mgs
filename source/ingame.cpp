#include "ingame.h"
#include <decor01_png.h>
#include <decor02_png.h>
#include <decor03_png.h>
#include <decor04_png.h>
#include <decor05_png.h>
#include <decor06_png.h>
#include <decor07_png.h>
#include <decor08_png.h>
#include <marche0_png.h>
#include <marche1_png.h>
#include <marche2_png.h>
#include <marche3_png.h>
#include <marche4_png.h>
#include <marche5_png.h>
#include <marche6_png.h>
#include <marche7_png.h>
#include <marche8_png.h>
#include <marche9_png.h>
#include <marche10_png.h>
#include <marche1t_png.h>
#include <marche2t_png.h>
#include <marche3t_png.h>
#include <marche4t_png.h>
#include <marche5t_png.h>
#include <marche6t_png.h>
#include <marche7t_png.h>
#include <marche8t_png.h>
#include <soldatface_png.h>
#include <soldatmarche1_png.h>
#include <soldatmarche1g_png.h>
#include <soldatmarche2_png.h>
#include <soldatmarche2g_png.h>
#include <soldatmarche3_png.h>
#include <soldatmarche3g_png.h>
#include <robotv3_png.h>
#include <balle_png.h>
#include <balleg_png.h>
#include <mine_png.h>
#include <mineExploded_png.h>
#include <sprite12_png.h>
#include <gameover_png.h>
#include <robotExploded2_png.h>
#include <robotExploded1_png.h>


#define dolphin

#ifdef wii
  #include <soundGameOver_mp3.h>
  #include <soundExplosion_mp3.h>
#endif


Ingame::Ingame()
{
   decor01=GRRLIB_LoadTexture(decor01_png);
   decor02=GRRLIB_LoadTexture(decor02_png);
   decor03=GRRLIB_LoadTexture(decor03_png);
   decor04=GRRLIB_LoadTexture(decor04_png);
   decor05=GRRLIB_LoadTexture(decor05_png);
   decor06=GRRLIB_LoadTexture(decor06_png);
   decor07=GRRLIB_LoadTexture(decor07_png);
   decor08=GRRLIB_LoadTexture(decor08_png);
   perso0=GRRLIB_LoadTexture(marche0_png);
   perso1=GRRLIB_LoadTexture(marche1_png);
   perso2=GRRLIB_LoadTexture(marche2_png);
   perso3=GRRLIB_LoadTexture(marche3_png);
   perso4=GRRLIB_LoadTexture(marche4_png);
   perso5=GRRLIB_LoadTexture(marche5_png);
   perso6=GRRLIB_LoadTexture(marche6_png);
   perso7=GRRLIB_LoadTexture(marche7_png);
   perso8=GRRLIB_LoadTexture(marche8_png);
   perso9=GRRLIB_LoadTexture(marche9_png);
   perso10=GRRLIB_LoadTexture(marche10_png);
   persot1=GRRLIB_LoadTexture(marche1t_png);
   persot2=GRRLIB_LoadTexture(marche2t_png);
   persot3=GRRLIB_LoadTexture(marche3t_png);
   persot4=GRRLIB_LoadTexture(marche4t_png);
   persot5=GRRLIB_LoadTexture(marche5t_png);
   persot6=GRRLIB_LoadTexture(marche6t_png);
   persot7=GRRLIB_LoadTexture(marche7t_png);
   persot8=GRRLIB_LoadTexture(marche8t_png);
   soldat0= GRRLIB_LoadTexture(soldatface_png);
   soldat1= GRRLIB_LoadTexture(soldatmarche1_png);
   soldat2= GRRLIB_LoadTexture(soldatmarche2_png);
   soldat3= GRRLIB_LoadTexture(soldatmarche3_png);
   soldat4= GRRLIB_LoadTexture(soldatmarche1g_png);
   soldat5= GRRLIB_LoadTexture(soldatmarche2g_png);
   soldat6= GRRLIB_LoadTexture(soldatmarche3g_png);
   balle=GRRLIB_LoadTexture(balle_png);
   balleg=GRRLIB_LoadTexture(balleg_png);
   mine=GRRLIB_LoadTexture(mine_png);
   mineExploded=GRRLIB_LoadTexture(mineExploded_png);
   boss=GRRLIB_LoadTexture(robotv3_png);
   tex_sprite_png = GRRLIB_LoadTexture(sprite12_png);
   gameover=false;
   endOfLevel1=false;
   //Personnage Snake;
}

void Ingame::initSnake(Personnage& Snake){  
  Snake.x = MARGE_G;
  Snake.y = 400;
  Snake.life = 10;
  Snake.saute = false;
  Snake.visible = true;
}

void Ingame::initBoss(Personnage& Boss){
  Boss.x = 4600;
  Boss.y = 400;
  Boss.life = 3;
  Boss.frame = 1;
}

void Ingame::initSoldat(Personnage& Soldat){
  Soldat.x = 2150;
  Soldat.y = 400;
  Soldat.view = LOOK_RIGHT;
  Soldat.frame = 1;
  Soldat.direction = 1;
  Soldat.plan = 2;
}

void Ingame::moveSnake(Personnage& Snake, vector<Balle>& b, vector<Mine>& m, ir_t irPointer)
{
      //Deplacement lateral
      //WPAD_ScanPads();
      u32 wpadheld, wpaddown;
      wpadheld = WPAD_ButtonsHeld(0);
      wpaddown = WPAD_ButtonsDown(0);
      if(wpadheld & WPAD_BUTTON_RIGHT && Snake.x < 4930 && Snake.y == 400){
	Snake.x+=3.0;
	Snake.view=LOOK_RIGHT;
	Snake.direction_new = TILE_RIGHT;
      }
      if(wpadheld & WPAD_BUTTON_LEFT && Snake.x > 5 && Snake.y == 400){
	Snake.x-=3.0;
	Snake.view=LOOK_LEFT;
	Snake.direction_new = TILE_LEFT;
      }

      //Changement de Plan
      if(wpaddown & WPAD_BUTTON_PLUS && Snake.plan < 3 && Snake.y == 400){
	Snake.plan++;
      }
      if(wpaddown & WPAD_BUTTON_MINUS && Snake.plan > 1 && Snake.y == 400){
	Snake.plan--;
      }
      
      //Invisibilité
      if(wpadheld & WPAD_BUTTON_1)
	Snake.visible = false;
      else
	Snake.visible = true;
    
      //Calcul du x relatif (entre 0 et 640)
      if(Snake.x < MARGE_G)
	Snake.xrelatif = Snake.x;
      if(Snake.x >= MARGE_G && Snake.x <= 5120-MARGE)
	Snake.xrelatif = MARGE_G;
      if(Snake.x > 5120-MARGE)  // longueur totale moins marge à droite
	Snake.xrelatif = 640 - (5120 - Snake.x);

      //Tir
      if((wpaddown & WPAD_BUTTON_B)
	 &&(Snake.direction == TILE_RIGHT || Snake.direction == TILE_LEFT
	    || Snake.direction == TILE_JUMPDL || Snake.direction == TILE_JUMPDR)){
	Balle balle;
	if(Snake.direction == TILE_JUMPDR || Snake.direction == TILE_RIGHT)
	  balle.x = Snake.x + 275;
	if(Snake.direction == TILE_JUMPDL || Snake.direction == TILE_LEFT)
	  balle.x = Snake.x;
	balle.y = Snake.y - 143 +Snake.plan*24;
	balle.xdir = Snake.direction;
	if(abs(b.back().x - balle.x) > 100 || b.size() == 0) //fréquence 
	  b.push_back(balle);
      }

      //Explosion des mines
      int n = (int)m.size();
      int i=0;
      while(i<n)
      {
	 if(abs(Snake.x+110-m.at(i).x)<30 && Snake.plan==m.at(i).plan && Snake.y==400)
	 {
	    m.at(i).exploded=true;
	    gameover=true;
	 }
	 i++;
      }

      //Vie de Snake
      if(Snake.life == 0)
	gameover=true;

      //Saut de Snake
      float saut = ((Snake.y-250)/100);
      if(saut <= 0.8)
	saut = 0.8;
      if(Snake.y <= 260)
	saut = 0.3;

      //Limite verticale pour Snake
      if(Snake.y > 400){
	Snake.y = 400.0;
	// On change les Tiles
	if(Snake.direction == TILE_JUMPDR)
	  Snake.direction_new = TILE_RIGHT;
	if(Snake.direction == TILE_JUMPDL)
	  Snake.direction_new = TILE_LEFT;
      }
      if(!Snake.saute){
	if(Snake.direction == TILE_JUMPDR)
	  Snake.direction_new = TILE_RIGHT;
	if(Snake.direction == TILE_JUMPDL)
	  Snake.direction_new = TILE_LEFT;
      }
      if(Snake.saute){
	if(Snake.direction == TILE_RIGHT)
	  Snake.direction_new = TILE_JUMPDR;
	if(Snake.direction == TILE_LEFT)
	  Snake.direction_new = TILE_JUMPDL;
      }
      if(!Snake.saute && Snake.y < 400){
	Snake.y += saut*3.0;
	if(Snake.direction == TILE_LEFT && wpadheld & WPAD_BUTTON_LEFT)
	  Snake.x -= 2.0;
	if(Snake.direction == TILE_RIGHT && wpadheld & WPAD_BUTTON_RIGHT)
	  Snake.x += 2.0;
      }
      if(Snake.saute && Snake.y > 250){
	Snake.y -= saut*3.0;
	if(Snake.direction == TILE_JUMPDL && wpadheld & WPAD_BUTTON_LEFT)
	  Snake.x -= 2.0;
	if(Snake.direction == TILE_JUMPDR && wpadheld & WPAD_BUTTON_RIGHT)
	  Snake.x += 2.0;
      }
      if(Snake.y <= 250)
	Snake.saute = false;
      if(wpaddown & WPAD_BUTTON_A && Snake.y == 400)
	Snake.saute = true;
      //Ajouter les tiles du debut de saut
      
  // END OF LEVEL ONE
  if(Snake.x>4765)
    endOfLevel1=true;
  
}

void Ingame::drawDecor(Personnage& Snake)
{
  // if(Snake.etage==0) {
  if(Snake.x<MARGE_G)
    {
      GRRLIB_DrawImg(0,0,decor01,0,1,1,CLR_WHITE);
      Snake.debutDraw=0;
    }
   if(Snake.x>=640-MARGE && Snake.x<1280-MARGE)  // pendant le passage dans ce if, (Snake.x+MARGE)%640 va de 0 à 639
   {
      GRRLIB_DrawPart(0,0,(int)(Snake.x+MARGE)%640,0,640-((int)(Snake.x+MARGE)%640),528,decor01,0,1,1,CLR_WHITE);
      GRRLIB_DrawPart(640-((int)(Snake.x+MARGE)%640),0,0,0,(int)(Snake.x+MARGE)%640,528,decor02,0,1,1,CLR_WHITE);
      Snake.debutDraw=((int)Snake.x+MARGE)%640;
   }
   if(Snake.x>=1280-MARGE && Snake.x<1920-MARGE)
   {
      GRRLIB_DrawPart(0,0,(int)(Snake.x+MARGE)%640,0,640-((int)(Snake.x+MARGE)%640),528,decor02,0,1,1,CLR_WHITE);
      GRRLIB_DrawPart(640-((int)(Snake.x+MARGE)%640),0,0,0,(int)(Snake.x+MARGE)%640,528,decor03,0,1,1,CLR_WHITE);
      Snake.debutDraw=640+((int)Snake.x+MARGE)%640;
   }
   if(Snake.x>=1920-MARGE && Snake.x<2560-MARGE)
   {
      GRRLIB_DrawPart(0,0,(int)(Snake.x+MARGE)%640,0,640-((int)(Snake.x+MARGE)%640),528,decor03,0,1,1,CLR_WHITE);
      GRRLIB_DrawPart(640-((int)(Snake.x+MARGE)%640),0,0,0,(int)(Snake.x+MARGE)%640,528,decor04,0,1,1,CLR_WHITE);
      Snake.debutDraw=2*640+((int)Snake.x+MARGE)%640;
   }
   if(Snake.x>=2560-MARGE && Snake.x<3200-MARGE)
   {
      GRRLIB_DrawPart(0,0,(int)(Snake.x+MARGE)%640,0,640-((int)(Snake.x+MARGE)%640),528,decor04,0,1,1,CLR_WHITE);
      GRRLIB_DrawPart(640-((int)(Snake.x+MARGE)%640),0,0,0,(int)(Snake.x+MARGE)%640,528,decor05,0,1,1,CLR_WHITE);
      Snake.debutDraw=3*640+((int)Snake.x+MARGE)%640;
   }
   if(Snake.x>=3200-MARGE && Snake.x<3840-MARGE)
   {
      GRRLIB_DrawPart(0,0,(int)(Snake.x+MARGE)%640,0,640-((int)(Snake.x+MARGE)%640),528,decor05,0,1,1,CLR_WHITE);
      GRRLIB_DrawPart(640-((int)(Snake.x+MARGE)%640),0,0,0,(int)(Snake.x+MARGE)%640,528,decor06,0,1,1,CLR_WHITE);
      Snake.debutDraw=4*640+((int)Snake.x+MARGE)%640;
   }
   if(Snake.x>=3840-MARGE && Snake.x<4480-MARGE)
   {
      GRRLIB_DrawPart(0,0,(int)(Snake.x+MARGE)%640,0,640-((int)(Snake.x+MARGE)%640),528,decor06,0,1,1,CLR_WHITE);
      GRRLIB_DrawPart(640-((int)(Snake.x+MARGE)%640),0,0,0,(int)(Snake.x+MARGE)%640,528,decor07,0,1,1,CLR_WHITE);
      Snake.debutDraw=5*640+((int)Snake.x+MARGE)%640;
   }
   if(Snake.x>=4480-MARGE && Snake.x<5120-MARGE)
   {
      GRRLIB_DrawPart(0,0,(int)(Snake.x+MARGE)%640,0,640-((int)(Snake.x+MARGE)%640),528,decor07,0,1,1,CLR_WHITE);
      GRRLIB_DrawPart(640-((int)(Snake.x+MARGE)%640),0,0,0,(int)(Snake.x+MARGE)%640,528,decor08,0,1,1,CLR_WHITE);
      Snake.debutDraw=6*640+((int)Snake.x+MARGE)%640;
   }
   if(Snake.x>=5120-MARGE)
   {
      GRRLIB_DrawImg(0,0,decor08,0,1,1,CLR_WHITE);
      Snake.debutDraw=7*640;
   }   
}

GRRLIB_texImg* Ingame::chooseSnake(Personnage& Snake){
  int tmp = Snake.frame;
  GRRLIB_texImg* perso;
  switch(tmp){
  case 1:{
    if(Snake.visible)
      perso = perso1;
    else
      perso = persot1;
    break;
  }
  case 2:{
    if(Snake.visible)
      perso = perso2;
    else
      perso = persot2;
    break;
  }
  case 3:{
    if(Snake.visible)
      perso = perso3;
    else
      perso = persot3;
    break;
  }
  case 4:{
    if(Snake.visible)
      perso = perso4;
    else
      perso = persot4;
    break;
  }
  case 5:{
    if(Snake.visible)
      perso = perso5;
    else
      perso = persot5;
    break;
  }
  case 6:{
    if(Snake.visible)
      perso = perso6;
    else
      perso = persot6;
    break;
  }
  case 7:{
    if(Snake.visible)
      perso = perso7;
    else
      perso = persot7;
    break;
  }
  case 8:{
    if(Snake.visible)
      perso = perso8;
    else
      perso = persot8;
    break;
  }
  case 9:{
    perso = perso9;
    break;
  }
  case 10:{
    perso = perso10;
    break;
  }
  default:{
    perso = perso0;
  }
  }
  return perso;
}

GRRLIB_texImg* Ingame::chooseSoldat(Personnage& Soldat){
  int tmp = Soldat.frame;
  GRRLIB_texImg* soldat;
  switch(tmp){
  case 1:{
    soldat = soldat1;
    break;
  }
  case 2:{
    soldat = soldat2;
    break;
  }
  case 3:{
    soldat = soldat3;
    break;
  }
  case 4:{
    soldat = soldat4;
    break;
  }
  case 5:{
    soldat = soldat5;
    break;
  }
  case 6:{
    soldat = soldat6;
    break;
  }
  default:{
    soldat = soldat0;
  }
  }
  return soldat;
}

void Ingame::drawPlayer(Personnage& Snake)
{ 
  u32 wpadheld;
  wpadheld = WPAD_ButtonsHeld(0);
  GRRLIB_texImg* perso = chooseSnake(Snake);
  GRRLIB_DrawImg(Snake.xrelatif,Snake.y-240 +Snake.plan*24,perso,0,1,1,CLR_WHITE);
  /*GRRLIB_InitTileSet(tex_sprite_png, 24, 32, 0);
   // Draw a sprite
  GRRLIB_DrawTile(Snake.xrelatif, Snake.y -48 + Snake.plan*24, tex_sprite_png, 0, 2, 2, CLR_WHITE, Snake.frame);
  */

  //---------------A NE PAS METTRE DANS movePlayer ----------------//
  //Sinon on ne rafraichit pas les frames correctement :)
  if(Snake.direction_new != Snake.direction) {
    // Direction has changed, modify frame immediately
    Snake.direction = Snake.direction_new;
    Snake.frame = Snake.direction;
    Snake.wait = 0;
  }
  Snake.wait++;
  if(Snake.wait > TILE_DELAY && !Snake.saute) {
    // wait is needed for the number of frame per second to be OK
    Snake.wait = 0;
    if(Snake.y == 400){
    // On prend la bonne texture en fonction de la direction
      if(wpadheld & WPAD_BUTTON_RIGHT || wpadheld & WPAD_BUTTON_LEFT){
        if(Snake.frame == 1 || Snake.frame == 5)
          Snake.frame += 2;
        else
	         Snake.frame++;
	     }
      else{
	Snake.frame = Snake.direction + 1;
	Snake.wait = 10;
      }
    }
    if(Snake.frame > (int)Snake.direction+3) 
      Snake.frame = (int)Snake.direction;
  }
  //----------------------------------------------------------------//
}

void Ingame::drawSoldat(Personnage& Soldat, Personnage Snake){
  if(Soldat.x < 2150){
    Soldat.view = LOOK_RIGHT;
    Soldat.direction_new = 1;
    Soldat.x = 2150;
  }
  if(Soldat.x > 2720){
    Soldat.view = LOOK_LEFT;
    Soldat.direction_new = 4;
    Soldat.x = 2720;
  }
  if(Soldat.view == LOOK_RIGHT)
    Soldat.x += 3.0;
  if(Soldat.view == LOOK_LEFT)
    Soldat.x -= 3.0;

  if(Snake.visible && abs(Snake.x - Soldat.x) <= 300)
    gameover = true;
  if(!Snake.visible && abs(Snake.x - Soldat.x) <= 50 && Snake.plan == Soldat.plan)
    gameover = true;


  //soldat = GRRLIB_LoadTexture(soldatface_png);
  GRRLIB_texImg* tmp = chooseSoldat(Soldat);
  GRRLIB_DrawImg(Soldat.x - Snake.debutDraw, Soldat.y - 240 + Soldat.plan*24, tmp ,0,1,1,CLR_WHITE);
  if(Soldat.direction_new != Soldat.direction) {
    // Direction has changed, modify frame immediately
    Soldat.direction = Soldat.direction_new;
    Soldat.frame = Soldat.direction;
    Soldat.wait = 0;
  }
  Soldat.wait++;
  if(Soldat.wait > TILE_DELAY) {
    // wait is needed for the number of frame per second to be OK
    Soldat.wait = 0;
    if(Soldat.y == 400){
      Soldat.frame++;
    }
    else{
      Soldat.frame = Soldat.direction;
      Soldat.wait = 10;
    }
  }
  if(Soldat.frame > (int)Soldat.direction+2) 
  Soldat.frame = (int)Soldat.direction;
}


void Ingame::drawProjectiles(Personnage Snake, vector<Balle>& b, Personnage& Boss)
{
  int n = 0;
  int vsize = (int)b.size();
  for(int i = 0; i < vsize; i++){
    if(b.at(i).xdir == TILE_LEFT || b.at(i).xdir == TILE_JUMPDL)
      b.at(i).x -= 4.0;
    if(b.at(i).xdir == TILE_RIGHT || b.at(i).xdir == TILE_JUMPDR)
      b.at(i).x += 4.0;
  }
  while(n < vsize){
    Balle tmp = b.at(n);
    if(abs(tmp.x - Snake.x) > 1000 || collision(tmp,Boss,0,0)){
      if(collision(tmp,Boss,0,0)){
	b.at(n).y = 700;
	Boss.life--;
      }
      else
	b.erase(b.begin()+n);
    }
    else{
      if(tmp.xdir == TILE_LEFT || tmp.xdir == TILE_JUMPDL)
      GRRLIB_DrawImg(tmp.x -Snake.debutDraw, tmp.y+48, balleg,0,1,1,CLR_WHITE);
      if(tmp.xdir == TILE_RIGHT || tmp.xdir == TILE_JUMPDR)
      GRRLIB_DrawImg(tmp.x -Snake.debutDraw, tmp.y+48, balle,0,1,1,CLR_WHITE);
    }
    vsize = (int)b.size();
    n++;
  }
}

void Ingame::drawMines(Personnage Snake, vector<Mine>& m)
{
   int n = (int)m.size();
   int i=0;
   while(i<n)
   {
      Mine tmp=m.at(i);
      if(tmp.exploded==false && abs(tmp.x-Snake.debutDraw)<640)
         GRRLIB_DrawImg(tmp.x-Snake.debutDraw, tmp.y +24 + tmp.plan*24, mine,0,1,1,CLR_WHITE);
      if(tmp.exploded==true && abs(tmp.x-Snake.debutDraw)<640)
      {
         #ifdef wii
           MP3Player_PlayBuffer(soundExplosion_mp3,soundExplosion_mp3_size,NULL);
         #endif
         GRRLIB_DrawImg(tmp.x-Snake.debutDraw-100, tmp.y-136 + tmp.plan*24, mineExploded,0,1,1,CLR_WHITE);
         GRRLIB_Render();
         for(time_t t = time(0) + 3; time(0) < t; )
         {
            drawDecor(Snake);
            GRRLIB_DrawImg(tmp.x-Snake.debutDraw-100, tmp.y-136 + tmp.plan*24, mineExploded,0,1,1,CLR_WHITE);
            GRRLIB_Render();
         }
         #ifdef wii
           MP3Player_Stop();
         #endif
      }
      i++;
   }
}

void Ingame::updateBoss(Personnage& Boss, Personnage& Snake, 
			vector<Balle>& bBoss){
  if(abs(Snake.x - Boss.x) <= 500){
    Balle balle;
    if(Snake.x - Boss.x < 0)
      balle.x = Boss.x ;
    else
      balle.x = Boss.x + 300;
    balle.y = Boss.y -10 ;
    if(Snake.x - Boss.x < 0)
      balle.xdir = TILE_LEFT;
    if(Snake.x - Boss.x > 0)
      balle.xdir = TILE_RIGHT;
    if(abs(bBoss.back().x - balle.x) > 600 || bBoss.size() == 0) //fréquence 
      bBoss.push_back(balle);
  }
}

bool Ingame::collision(Balle bullet, Personnage Boss, int w, int h){
  return(abs(bullet.x - Boss.x - 75) <= 90 && bullet.y <= Boss.y +h);
}

void Ingame::drawBoss(Personnage Snake, Personnage& Boss, 
		      vector<Balle>& bBoss){
  if(Boss.life > 0)
    GRRLIB_DrawImg(Boss.x-Snake.debutDraw, Boss.y -240, boss,0,1,1,CLR_WHITE);
  else{
    if(Boss.frame == 3)
      Boss.x = 0;
    #ifdef wii
      MP3Player_Stop();
    #endif
    if(Boss.frame == 1) {
      #ifdef wii
        MP3Player_PlayBuffer(soundExplosion_mp3,soundExplosion_mp3_size,NULL);
      #endif
      boss = GRRLIB_LoadTexture(robotExploded1_png);
    }
    if(Boss.frame == 2)
      boss = GRRLIB_LoadTexture(robotExploded2_png);
    GRRLIB_DrawImg(Boss.x-Snake.debutDraw, Boss.y -240, boss,0,1,1,CLR_WHITE);
    Boss.wait++;
    if(Boss.wait > 15) {
      // wait is needed for the number of frame per second to be OK
      Boss.wait = 0;
      if(Boss.y == 400)
	Boss.frame++;
      else{
	Boss.frame = 1;
	Boss.wait = 15;
      }
    }
  }
}

void Ingame::drawProjBoss(Personnage& Snake, Personnage Boss, 
			  vector<Balle>& bBoss){
  if(Boss.life > 0){
    int n = 0;
    int vsize = (int)bBoss.size();
    for(int i = 0; i < vsize; i++){
      if(bBoss.at(i).xdir == TILE_LEFT || bBoss.at(i).xdir == TILE_JUMPDL)
	bBoss.at(i).x -= 4.0;
      if(bBoss.at(i).xdir == TILE_RIGHT || bBoss.at(i).xdir == TILE_JUMPDR)
	bBoss.at(i).x += 4.0;
    }
    while(n < vsize){
      Balle tmp = bBoss.at(n);
      if(abs(tmp.x - Boss.x) > 1000 || collision(tmp,Snake,0,80)){
	if(collision(tmp,Snake,0,80)){
	  bBoss.at(n).y = 700;  //Dat triche :)
	  Snake.life--;
	}
	else
	  bBoss.erase(bBoss.begin()+n);
      }
      else{
	if((tmp.xdir == TILE_LEFT || tmp.xdir == TILE_JUMPDL))
	  GRRLIB_DrawImg(tmp.x -Snake.debutDraw, tmp.y, balleg,0,1,1,CLR_WHITE);
	if((tmp.xdir == TILE_RIGHT || tmp.xdir == TILE_JUMPDR))
	  GRRLIB_DrawImg(tmp.x -Snake.debutDraw, tmp.y, balle,0,1,1,CLR_WHITE);
      }
      vsize = (int)bBoss.size();
      n++;
    }
  }
  else
    bBoss.clear();
}

void Ingame::gameOver()
{
   #ifdef wii
     MP3Player_PlayBuffer(soundGameOver_mp3,soundGameOver_mp3_size,NULL);
   #endif
   picGameover=GRRLIB_LoadTexture(gameover_png);
   while(1)
   {
      WPAD_ScanPads();
      GRRLIB_DrawImg(0, 0, picGameover,0,1,1,CLR_WHITE);
      PUSH_ANY_BUTTON()
      GRRLIB_Render();
   }
   free(picGameover);
   #ifdef wii
     MP3Player_Stop();
   #endif
   return;
}

void Ingame::destructeur()
{
   GRRLIB_FreeTexture(decor01);
   GRRLIB_FreeTexture(decor02);
   GRRLIB_FreeTexture(decor03);
   GRRLIB_FreeTexture(decor04);
   GRRLIB_FreeTexture(decor05);
   GRRLIB_FreeTexture(decor06);
   GRRLIB_FreeTexture(decor07);
   GRRLIB_FreeTexture(decor08);
   GRRLIB_FreeTexture(perso0);
   GRRLIB_FreeTexture(perso1);
   GRRLIB_FreeTexture(perso2);
   GRRLIB_FreeTexture(perso3);
   GRRLIB_FreeTexture(perso4);
   GRRLIB_FreeTexture(perso5);
   GRRLIB_FreeTexture(perso6);
   GRRLIB_FreeTexture(perso7);
   GRRLIB_FreeTexture(perso8);
   GRRLIB_FreeTexture(perso9);
   GRRLIB_FreeTexture(perso10);
   GRRLIB_FreeTexture(balle);
   GRRLIB_FreeTexture(balleg);
   GRRLIB_FreeTexture(tex_sprite_png);
   GRRLIB_FreeTexture(boss);
   GRRLIB_FreeTexture(soldat0);
   GRRLIB_FreeTexture(soldat1);
   GRRLIB_FreeTexture(soldat2);
   GRRLIB_FreeTexture(soldat3);
   GRRLIB_FreeTexture(soldat4);
   GRRLIB_FreeTexture(soldat5);
   GRRLIB_FreeTexture(soldat6);
   GRRLIB_FreeTexture(persot1);
   GRRLIB_FreeTexture(persot2);
   GRRLIB_FreeTexture(persot3);
   GRRLIB_FreeTexture(persot4);
   GRRLIB_FreeTexture(persot5);
   GRRLIB_FreeTexture(persot6);
   GRRLIB_FreeTexture(persot7);
   GRRLIB_FreeTexture(persot8);
}

