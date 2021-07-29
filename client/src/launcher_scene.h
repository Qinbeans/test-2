#include "scene.h"
#include "tool.h"

#ifndef LAUNCHER_SCENE_H
#define LAUNCHER_SCENE_H

#define NUM_UI 7
/**
 * 0 - Server
 * 1 - Login
 * 2 - Play
 * 3 - Quit 
 */

class launcher: public scene{
   private:
      Style UI[NUM_UI];
      int status = -1;
   public:
      launcher(string name, unsigned int width, unsigned int height, int resize);
      void init();
      void update();
};

#endif