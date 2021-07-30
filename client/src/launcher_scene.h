#include "scene.h"
#include "tool.h"

#ifndef LAUNCHER_SCENE_H
#define LAUNCHER_SCENE_H

#define NUM_UI 8
#define NUM_DATA 4

/**
 * UI Map
 * 0 - Server
 * 1 - Login
 * 2 - Play
 * 3 - Quit 
 * 4 - Name
 * 5 - ID
 * 6 - IP
 * 7 - Validity 
 */

class launcher: public scene{
   protected:
      Style UI[NUM_UI];
      string gamefile[NUM_DATA];
      int status = -1;
      string validity;
      void init();
      void update();
   public:
      launcher(string name, unsigned int width, unsigned int height, int resize);
      ~launcher();
};

#endif