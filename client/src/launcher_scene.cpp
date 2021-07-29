#include "launcher_scene.h"
#include "raygui.h"

launcher::launcher(string name, unsigned int width, unsigned int height, int resize){
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
      if(IsWindowResized()){
         scale = GetScreenHeight()/CHUNK;
         this->width = GetScreenWidth();
         this->height = GetScreenHeight();
         init();
      }
      update();
      EndDrawing();
   }
   CloseWindow();
}

void launcher::update(){
   for(int i = 0; i < 4; i++){
      if(draw_lblb(UI[i],BLACK)){
         // printf("LBL %d Status: True\n",i);
         status = i;
      }
   }
   switch(status){
      case 0:{
         //Connect
         break;
      }
      case 1:{
         //Login
         break;
      }
      case 2:{
         //Play
         //Closes window
         break;
      }
      case 3:{
         printf("<--QUIT-->\n");
         CloseWindow();
         printf("<--Done-->\n");
         exit(EXIT_SUCCESS);
      }
   }
   for(int i = 4; i < 7; i++){
      draw_lbl(UI[i],BLACK);
   }
}

void launcher::init(){
   float bwidth = scale*10;
   float bheight = scale*3;
   float lwidth = scale*20;
   float font = scale*2;
   float spacing = scale/2;
   string names[7] = {"Connect","Login","Play","Quit","Name: ","ID: ","IP: "};
   //ADD TEST BOX FOR WHO THE USER IS AND WHAT SERVER THEY ARE CONNECTED TO
   for(int i = 0; i < 4; i++){
      lbl_style(UI[i],names[i],font,spacing,GUI_TEXT_ALIGN_CENTER,ColorToInt(BLUE),{scale,scale+scale*(i*6),bwidth,bheight});
      //debug
      // printStyle(buttons[i]);
   }
   for(int i = 4; i < 7; i++){
      lbl_style(UI[i],names[i],font,spacing,GUI_TEXT_ALIGN_LEFT,ColorToInt(WHITE),{width-(lwidth+scale),scale+scale*((i-4)*6),lwidth,bheight});
   }
}