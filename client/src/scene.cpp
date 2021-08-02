/**
 * @file scene.cpp
 * @author Ryan Fong (rybeats@live.com)
 * @brief The base class for all scenes
 * @version 0.1
 * @date 2021-08-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "scene.h"
#include "raylib.h"

#define CHUNK 50
scene::scene(){
   printf("<Entered Scene>\n");
   scale = height/CHUNK;
}

scene::scene(string name, unsigned int width, unsigned int height, int resize){
   this->name = name;
   this->width = width;
   this->height = height;
   scale = this->height/CHUNK;
   SetConfigFlags(resize);
   InitWindow(width,height,name.c_str());
   init();
   while(!WindowShouldClose()){
      BeginDrawing();
      ClearBackground(GRAY);
      update();
      EndDrawing();
   }
   CloseWindow();
}

void scene::toggle_fullscreen(){
   ToggleFullscreen();
   fscrn = IsWindowFullscreen();
}

void scene::set_height(unsigned int height){
   this->height = height;
   SetWindowSize(width,height);
}

void scene::set_width(unsigned int width){
   this->width = width;
   SetWindowSize(width,height);
}