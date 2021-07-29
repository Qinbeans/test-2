#include <string>

#ifndef SCENE_H
#define SCENE_H

using std::string;

class scene{
   protected:
      string name;
      unsigned int width;
      unsigned int height;
      bool fscrn;
      float scale;
   public:
      scene();
      scene(string name, unsigned int width, unsigned int height, int resize);
      virtual void update(){};
      virtual void init(){};
      void toggle_fullscreen();
      void toggle_resizable();
      void set_width(unsigned int width);
      void set_height(unsigned int height);
};

#endif