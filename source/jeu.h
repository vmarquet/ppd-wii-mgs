#ifndef JEU_H
#define JEU_H

#include <time.h>  // pour temporiser avec time();
#include <string.h>

#include "defjeu.h"

class Jeu
{
     public:  // méthodes
     Jeu();   // constructeur
     void intro();
     void menu();
     void codec();
     void tuto();
     void about();
     void play();
     void end();
     // void gameover();
     
     
};

#endif
