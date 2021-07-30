#include "scene.h"
#include "tool.h"
#include "net.h"

#ifndef LAUNCHER_SCENE_H
#define LAUNCHER_SCENE_H

#define NUM_UI 8


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
      int status;
      bool was_pressed;
      short textbox;
      string validity;
      float spacing;
      float font;
      float bwidth;
      float bheight;
      float lwidth;
      float twidth;
      network* net;
      bool login_status;
      bool connection_status;
      string file_loc;
      string filename;
      void init();
      void update();
      void set_screen();
   public:
      launcher(string name, unsigned int width, unsigned int height, int resize);
};

#endif