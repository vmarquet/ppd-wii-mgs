#include "jeu.h"
#include "dialogues.h"
#include "codec.h"
#include "ingame.h"
/*********** Images Importées *********/
#include <pic1_png.h>
#include <pic2_png.h>
#include <photo1_png.h>
#include <robot_png.h>
#include <pointer_png.h>
#include <menu1_png.h>
#include <menu2_png.h>
#include <menu3_png.h>
#include <menu4_png.h>
#include <menu5_png.h>
#include <menu6_png.h>
#include <about_png.h>
#include <codec1_png.h>
#include <codec2_png.h>
#include <font_png.h>
#include <tuto_png.h>
#include <end_png.h>

#define dolphin

#ifdef wii
  #include <music01_mp3.h>
  #include <music02_mp3.h>
  #include <soundCodec_mp3.h>
#endif


/************ METHODES DE LA CLASSE JEU **********/
Jeu::Jeu()  // constructeur
{

}

void Jeu::intro()  // ESIEA Productions
{
   GRRLIB_texImg* pic1;
   pic1=GRRLIB_LoadTexture(pic1_png);
   for (time_t t = time(0) + 3; time(0) < t; )  // tempo 5 sec
   {
      GRRLIB_DrawImg(0,0,pic1,0,1,1,0xFFFFFFFF);
      GRRLIB_Render();
   }
   GRRLIB_FreeTexture(pic1);
}
   
     
void Jeu::menu()
{
   #ifdef wii
     MP3Player_PlayBuffer(music01_mp3,music01_mp3_size,NULL);
   #endif
   GRRLIB_texImg* pic2;
   pic2=GRRLIB_LoadTexture(pic2_png);
   GRRLIB_texImg* menu1;
   menu1=GRRLIB_LoadTexture(menu1_png);
   GRRLIB_texImg* menu2;
   menu2=GRRLIB_LoadTexture(menu2_png);
   /*GRRLIB_texImg* menu3;
   menu3=GRRLIB_LoadTexture(menu3_png);
   GRRLIB_texImg* menu4;
   menu4=GRRLIB_LoadTexture(menu4_png);*/
   GRRLIB_texImg* menu5;
   menu5=GRRLIB_LoadTexture(menu5_png);
   GRRLIB_texImg* menu6;
   menu6=GRRLIB_LoadTexture(menu6_png);
   
   GRRLIB_texImg* pointer = GRRLIB_LoadTexture(pointer_png);
   GRRLIB_SetMidHandle(pointer,true);  // afficher le pointeur
   ir_t irPointer;  // IR pointer*/
   bool wantToQuit=false;
   while(1)
   {
      WPAD_ScanPads();  // Scan the Wiimotes
      WPAD_IR(WPAD_CHAN_0, &irPointer);
      GRRLIB_DrawImg(0,0,pic2,0,1,1,0xFFFFFFFF);
      GRRLIB_DrawImg(270,200,menu1,0,1,1,0xFFFFFFFF);
      //GRRLIB_DrawImg(270,250,menu3,0,1,1,0xFFFFFFFF);
      GRRLIB_DrawImg(270,350,menu5,0,1,1,0xFFFFFFFF);
      if(irPointer.x>270 && irPointer.x<570 && irPointer.y>200 && irPointer.y<300) // PLAY
      {
         GRRLIB_DrawImg(270,200,menu2,0,1,1,0xFFFFFFFF);
         if(WPAD_ButtonsDown(0) & WPAD_BUTTON_A)
            break;  // sortie du while -> jeu.codec()  (cf main)
      }
      /*if(irPointer.x>270 && irPointer.x<570 && irPointer.y>250 && irPointer.y<350)  // SETTINGS
      {
         GRRLIB_DrawImg(270,250,menu4,0,1,1,0xFFFFFFFF);
      }*/
      if(irPointer.x>270 && irPointer.x<570 && irPointer.y>350 && irPointer.y<450) // ABOUT
      {
         GRRLIB_DrawImg(270,350,menu6,0,1,1,0xFFFFFFFF);
         if(WPAD_ButtonsDown(0) & WPAD_BUTTON_A)
         {
            about();
         }
      }
      if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
      {
         wantToQuit=true;
         break;  // on sort du while(1)
      }
      GRRLIB_DrawImg(irPointer.x, irPointer.y, pointer, 0, 1, 1, 0xFFFFFFFF);
      GRRLIB_Render();
      
   }
   GRRLIB_FreeTexture(pic2);
   GRRLIB_FreeTexture(menu1);
   GRRLIB_FreeTexture(menu2);
   //GRRLIB_FreeTexture(menu3);
   //GRRLIB_FreeTexture(menu4);
   GRRLIB_FreeTexture(menu5);
   GRRLIB_FreeTexture(menu6);
   #ifdef wii
     MP3Player_Stop();
   #endif
   if(wantToQuit==true)
   {
      GRRLIB_Exit();
      exit(0);
   }
}
    
     
void Jeu::codec()
{
   GRRLIB_texImg* photo1;
   photo1=GRRLIB_LoadTexture(photo1_png);  // idée: on voit snake dans une boite en carton qui avance vers l'entrée
   for (time_t t = time(0) + 3; time(0) < t; )  // afficher la date reelle/le lieu (voir localtime(); )
   {
      WPAD_ScanPads();
      if(WPAD_ButtonsDown(0) & WPAD_BUTTON_A)
         return;
      GRRLIB_DrawImg(0,0,photo1,0,1,1,CLR_WHITE);
      GRRLIB_Render();
   }
   GRRLIB_FreeTexture(photo1);
   GRRLIB_texImg* codec1;
   codec1=GRRLIB_LoadTexture(codec1_png);
   GRRLIB_texImg* codec2;
   codec2=GRRLIB_LoadTexture(codec2_png);
   //GRRLIB_texImg* texFont = GRRLIB_LoadTexture(font_png);
   //GRRLIB_InitTileSet(texFont, 8, 16, 0);
   #ifdef wii
     MP3Player_PlayBuffer(soundCodec_mp3,soundCodec_mp3_size,NULL);
   #endif

   char dial[200];
   
   sprintf(dial, DIAL_1);
   for(time_t t = time(0) + 3; time(0) < t; )
     MACRO_DIAL_C;
   
   sprintf(dial, DIAL_2);
   for(time_t t = time(0) + 3; time(0) < t; )
     MACRO_DIAL_S;
     
   sprintf(dial, DIAL_3);
   for(time_t t = time(0) + 3; time(0) < t; )
     MACRO_DIAL_S;
     
   sprintf(dial, DIAL_4);
   for(time_t t = time(0) + 3; time(0) < t; )
     MACRO_DIAL_C;
     
   sprintf(dial, DIAL_5);
   for(time_t t = time(0) + 3; time(0) < t; )
     MACRO_DIAL_S;
     
   sprintf(dial, DIAL_6);
   for(time_t t = time(0) + 3; time(0) < t; )
     MACRO_DIAL_C;
     
   sprintf(dial, DIAL_6B);
   for(time_t t = time(0) + 3; time(0) < t; )
     MACRO_DIAL_C;
     
   GRRLIB_texImg* robot;
   robot=GRRLIB_LoadTexture(robot_png);
   for (time_t t = time(0) + 2; time(0) < t; )
   {
      WPAD_ScanPads();
      if(WPAD_ButtonsDown(0) & WPAD_BUTTON_A)
         return;
      GRRLIB_DrawImg(0,0,robot,0,1,1,CLR_WHITE);
      GRRLIB_Render();
   }
   GRRLIB_FreeTexture(robot);
     
   sprintf(dial, DIAL_7);
   for(time_t t = time(0) + 3; time(0) < t; )
     MACRO_DIAL_S;
     
   sprintf(dial, DIAL_8);
   for(time_t t = time(0) + 3; time(0) < t; )
     MACRO_DIAL_C;
     
   sprintf(dial, DIAL_9);
   for(time_t t = time(0) + 3; time(0) < t; )
     MACRO_DIAL_S;
     
   sprintf(dial, DIAL_10);
   for(time_t t = time(0) + 3; time(0) < t; )
     MACRO_DIAL_C;
     
   sprintf(dial, DIAL_11);
   for(time_t t = time(0) + 3; time(0) < t; )
     MACRO_DIAL_C;
     
   sprintf(dial, DIAL_11B);
   for(time_t t = time(0) + 3; time(0) < t; )
     MACRO_DIAL_C;
     
   sprintf(dial, DIAL_12);
   for(time_t t = time(0) + 3; time(0) < t; )
     MACRO_DIAL_S;
     
   sprintf(dial, DIAL_13);
   for(time_t t = time(0) + 3; time(0) < t; )
     MACRO_DIAL_C;
     
   sprintf(dial, DIAL_14);
   for(time_t t = time(0) + 3; time(0) < t; )
     MACRO_DIAL_C;
     
   sprintf(dial, DIAL_14B);
   for(time_t t = time(0) + 5; time(0) < t; )
     MACRO_DIAL_C;
     
   sprintf(dial, DIAL_14C);
   for(time_t t = time(0) + 3; time(0) < t; )
     MACRO_DIAL_C;
     
   sprintf(dial, DIAL_15);
   for(time_t t = time(0) + 3; time(0) < t; )
     MACRO_DIAL_S;
   
   GRRLIB_FreeTexture(codec1);
   GRRLIB_FreeTexture(codec2);
   #ifdef wii
     MP3Player_Stop();
   #endif
}

void Jeu::tuto()
{
   GRRLIB_texImg* tuto;
   tuto=GRRLIB_LoadTexture(tuto_png);
   for(time_t t = time(0) + 3; time(0) < t; ){
    GRRLIB_DrawImg(0,0,tuto,0,1,1,0xFFFFFFFF);
    GRRLIB_Render();
   }
   GRRLIB_FreeTexture(tuto);
}

void Jeu::about()
{
   GRRLIB_texImg* about;
   about=GRRLIB_LoadTexture(about_png);
   while(1)
   {
       WPAD_ScanPads();
       PUSH_ANY_BUTTON()
       GRRLIB_DrawImg(0,0,about,0,1,1,0xFFFFFFFF);
       GRRLIB_Render();
   }
   GRRLIB_FreeTexture(about);
}

void Jeu::play()
{
   Personnage Snake;
   Personnage Boss;
   Personnage Soldat;
   Ingame ingame;
   ingame.initSnake(Snake);
   ingame.initBoss(Boss);
   ingame.initSoldat(Soldat);
   vector<Balle> b;
   vector<Balle> bBoss;
   vector<Mine> m;
   ir_t irPointer;
   // mines
   Mine mine; mine.x=1000; mine.y=400; mine.plan=2;
   Mine mine2; mine2.x=600; mine2.y=400; mine2.plan=2;
   m.push_back(mine);
   m.push_back(mine2);
   // balle au départ pour éviter un bug
   Balle b1; b1.x = 275;b1.y=400;b1.xdir=TILE_RIGHT;
   Balle b2; b2.x = 275;b2.y=400;b2.xdir=TILE_RIGHT;
   b.push_back(b1);
   bBoss.push_back(b2);
   b.erase(b.begin());
   bBoss.erase(b.begin());

   GRRLIB_texImg * texFont = GRRLIB_LoadTexture(font_png);
   GRRLIB_InitTileSet(texFont, 8, 16, 0);
   bool finProgramme = false;
   
   #ifdef wii
     MP3Player_PlayBuffer(music02_mp3,music02_mp3_size,NULL);
   #endif

   while(!finProgramme){

     WPAD_ScanPads();
     WPAD_IR(WPAD_CHAN_0, &irPointer);
     if(WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) finProgramme = true;
     if(ingame.gameover==false)
     {
        ingame.moveSnake(Snake,b,m,irPointer);
	       ingame.updateBoss(Boss,Snake,bBoss);
        ingame.drawDecor(Snake);
        ingame.drawMines(Snake, m);
        ingame.drawProjectiles(Snake, b, Boss);
       	ingame.drawBoss(Snake,Boss, bBoss);
       	ingame.drawProjBoss(Snake, Boss, bBoss);
	       if(Snake.plan >= Soldat.plan){
	         ingame.drawSoldat(Soldat, Snake);
	         ingame.drawPlayer(Snake);
	       }
	      else{
	        ingame.drawPlayer(Snake);
	        ingame.drawSoldat(Soldat, Snake);
	      }
     }
     if(ingame.gameover==true)
     {
        #ifdef wii
          MP3Player_Stop();
        #endif
        ingame.gameOver();
        ingame.gameover=false;
        #ifdef wii
          MP3Player_PlayBuffer(music02_mp3,music02_mp3_size,NULL);
        #endif
        ingame.initSnake(Snake);
	       ingame.initBoss(Boss);
        // reset des mines
        int n = (int)m.size();
        int i=0;
        while(i<n)
        {
           m.at(i).exploded=false;
           i++; 
        }
        //reset des listes de balles
        while(b.size() > 0){
          b.erase(b.begin());
        }
        while(bBoss.size() > 0){
          bBoss.erase(bBoss.begin());
        }
     }
     if(ingame.endOfLevel1==true)
     {
        end();
        finProgramme = true;
        // reset des mines
        int n = (int)m.size();
        int i=0;
        while(i<n)
        {
           m.at(i).exploded=false;
           i++; 
        }
        //reset des listes de balles
        while(b.size() > 0){
          b.erase(b.begin());
        }
        while(bBoss.size() > 0){
          bBoss.erase(bBoss.begin());
        }
     }

     //---------------------- TEST ----------------------------
     char* posX =(char*)malloc(sizeof(char));
     char* posY =(char*)malloc(sizeof(char));
     sprintf(posX,"VISIBLE %d",Snake.visible);
     sprintf(posY,"LIFE : %d",Snake.life);
     GRRLIB_Printf(64, 16 + 15, texFont, 0x000FFF, 2, posY);
     //GRRLIB_Printf(64, 16 + 60, texFont, 0x000FFF, 2, posX);
     
     /*char* nb =(char*)malloc(sizeof(char));
     sprintf(nb,"%.d",(int)Soldat.frame);
     GRRLIB_Printf(64, 150, texFont, 0x000FFF, 2, nb);
     char* nb2 =(char*)malloc(sizeof(char));
     sprintf(nb2,"%.d",(int)Soldat.direction);
     GRRLIB_Printf(64, 170, texFont, 0x000FFF, 2, nb2);
     char* nb3 =(char*)malloc(sizeof(char));
     sprintf(nb3,"%.d",(int)Soldat.direction_new);
     GRRLIB_Printf(64, 190, texFont, 0x000FFF, 2, nb3);*/



     /*char* nb4 =(char*)malloc(sizeof(char));
     sprintf(nb4,"%.d",left);
     GRRLIB_Printf(64, 210, texFont, 0x000FFF, 2, nb4);*/
     //-------------------- END TEST -------------------------
     


     GRRLIB_Render();
   }
   #ifdef wii
     MP3Player_Stop();
   #endif
   b.clear();
   ingame.destructeur();
}

void Jeu::end()
{
   GRRLIB_texImg* end;
   end=GRRLIB_LoadTexture(end_png);
   for(time_t t = time(0) + 4; time(0) < t; )
   {
      GRRLIB_DrawImg(0,0,end,0,1,1,CLR_WHITE);
      GRRLIB_Render();
   }
   GRRLIB_FreeTexture(end);
   return;
}



    
     

