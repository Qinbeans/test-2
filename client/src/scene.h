/**
 * @file scene.h
 * @author Ryan Fong (rybeats@live.com)
 * @brief The base class for all scenes
 * @version 0.1
 * @date 2021-08-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
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
      virtual void update(){};
      virtual void init(){};
   public:
      scene();
      scene(string name, unsigned int width, unsigned int height, int resize);
      void toggle_fullscreen();
      void toggle_resizable();
      void set_width(unsigned int width);
      void set_height(unsigned int height);
};

#endif