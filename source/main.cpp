
/*===========================================
                    MGS
============================================*/


#include "jeu.h"
#include "personnage.h"

// very important: the Wii version and the Dolphin version (emulator) are incompatibles
// Dolphin does not support music, and the ratio of the images is not the same
// so we will use different code sources (depends on the defined variable)
#define dolphin   // define "dolphin" or "wii" depending on where you want to run the game



GXRModeObj* IR_Init() {  // IR pointer
    GXRModeObj *rmode = NULL;
    rmode = VIDEO_GetPreferredMode(NULL);
    return rmode;
}

int main(int argc, char **argv) {
    
    GRRLIB_Init(); // Initialise the Graphics & Video subsystem
    WPAD_Init(); // Initialise the Wiimotes
    //rmode = VIDEO_GetPreferredMode(NULL);
    GXRModeObj *rmode = IR_Init();  // IR init
    WPAD_SetVRes(WPAD_CHAN_ALL,rmode->fbWidth,rmode->xfbHeight);  // set Xmax, Ymax
    //WPAD_SetVRes(WPAD_CHAN_ALL,640,480);  // set Xmax, Ymax
    WPAD_SetDataFormat(WPAD_CHAN_0,WPAD_FMT_BTNS_ACC_IR);  // active capteur IR
    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);
    VIDEO_WaitVSync();
    
    #ifdef wii  // if it's for the Wii, we can use MP3 musics
      ASND_Init(); //On initialise le systeme de sons
      MP3Player_Init(); //On initialise le lecteur MP3
    #endif
    
    Jeu jeu;  // Création d'un objet jeu de classe Jeu
    jeu.intro();  // Lance "Esiea production"
    
    
    while(1)
    {
      jeu.menu();   // Lance menu du jeu
      jeu.codec();
      jeu.tuto();
      jeu.play();
    }
    
    
    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB
    exit(0);  // Use exit() to exit a program, do not use 'return' from main()
}
