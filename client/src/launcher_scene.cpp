/**
 * @file launcher_scene.cpp
 * @author Ryan Fong (rybeats@live.com)
 * @brief Derived class of scene to draw a launcher screen
 * @version 0.1
 * @date 2021-08-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "launcher_scene.h"
#include "raygui.h"
#include <future>



launcher::launcher(string name, unsigned int width, unsigned int height, int resize){
   this->name = name;
   this->width = width;
   this->height = height;
   scale = this->height/CHUNK;
   textbox = -1;
   status = -1;
   login_status = false;
   bwidth = scale*10;
   bheight = scale*3;
   twidth = scale*25;
   lwidth = scale*15;
   font = scale*2;
   spacing = scale/2;
   net = NULL;
   connection_status = false;
   file_loc = get_game_dir();
   filename = "/gamedata.inline";
   int flag = resize;
   SetConfigFlags(flag);
   InitWindow(width,height,name.c_str());
   init();
   while(!WindowShouldClose()){
      BeginDrawing();
      ClearBackground(GRAY);
      if(IsWindowResized()){
         scale = GetScreenHeight()/CHUNK;
         this->width = GetScreenWidth();
         this->height = GetScreenHeight();
         set_screen();
      }
      update();
      EndDrawing();
   }
   CloseWindow();
}

void launcher::update(){
   string concat_game;
   if(was_pressed){
      set_screen();
      was_pressed = false;
   }
   DrawFPS(0,height-scale*3);
   for(int i = 0; i < 4; i++){
      if(draw_lblb(UI[i],BLACK)){
         // printf("LBL %d Status: True\n",i);
         status = i;
      }
   }
   switch(status){
      //Connect(WIP)
      case 0:{
         //Connect use new thread
         string welcomeMSG = "Hello";
         bool ret;
         lwidth = scale*15;
         net = new network(gamefile[2],25570,1,2,0,0);
         connection_status = true;
         if(net->start()==EXIT_FAILURE){
            printf("<--FAILED-->\n");
            validity = "No Network";
            connection_status = false;
         }else{
            validity = "VALID";
         }
         if(net->connect(welcomeMSG)){
            printf("<--BAD CONNECTION TO: %s-->\n",gamefile[2].c_str());
            validity = "No Connection";
            lwidth = scale*20;
            connection_status = false;
         }else{
            validity = "VALID";
         }
         // if(net.disconnect()==EXIT_FAILURE){
         //    printf("<--FAILED-->\n");
         //    validity = "Disconnect Failed";
         // }
         if(connection_status){
            lbl_style(UI[7],validity,font,spacing,GUI_TEXT_ALIGN_CENTER,ColorToInt(GREEN),{width-(twidth+scale),scale*19,lwidth,bheight});
         }else{
            lbl_style(UI[7],validity,font,spacing,GUI_TEXT_ALIGN_CENTER,ColorToInt(RED),{width-(twidth+scale),scale*19,lwidth,bheight});
            delete net;
         }
         concat_game = gamefile[0]+" "+gamefile[1]+" "+gamefile[2]+" "+gamefile[3]+" "+gamefile[4];
         write(file_loc,filename,concat_game);
         break;
      }
      //Login(WIP)
      case 1:{
         if(!connection_status){
            validity = "Not Connected";
            lwidth = scale*22;
         }else{
            lwidth = scale*15;
            if(net->start()==EXIT_FAILURE){
               printf("<--FAILED-->\n");
               validity = "No Network";
               connection_status = false;
            }else{
               validity = "VALID";
            }
            if(net->connect("0 "+gamefile[2]+" "+gamefile[3])==EXIT_FAILURE){
               printf("<--BAD CONNECTION TO: %s-->\n",gamefile[2].c_str());
               validity = "No Connection";
               lwidth = scale*20;
               connection_status = false;
            }else{
               validity = "VALID";
            }
            //
            //
            //poll for response
            //
            //
         }
         if(validity=="VALID"){
            lbl_style(UI[7],validity,font,spacing,GUI_TEXT_ALIGN_CENTER,ColorToInt(GREEN),{width-(twidth+scale),scale*19,lwidth,bheight});
         }else{
            lbl_style(UI[7],validity,font,spacing,GUI_TEXT_ALIGN_CENTER,ColorToInt(RED),{width-(twidth+scale),scale*19,lwidth,bheight});
         }
         concat_game = gamefile[0]+" "+gamefile[1]+" "+gamefile[2]+" "+gamefile[3]+" "+gamefile[4];
         write(file_loc,filename,concat_game);
         break;
      }
      //Play(VERY WIP)
      case 2:{
         //Play
         if(!connection_status){
            validity = "Not Connected";
            lwidth = scale*22;
         }else if(!login_status){
            validity = "Not Logged in";
            lwidth = scale*22;
         }
         if(validity=="VALID"){
            lbl_style(UI[7],validity,font,spacing,GUI_TEXT_ALIGN_CENTER,ColorToInt(GREEN),{width-(twidth+scale),scale*19,lwidth,bheight});
         }else{
            lbl_style(UI[7],validity,font,spacing,GUI_TEXT_ALIGN_CENTER,ColorToInt(RED),{width-(twidth+scale),scale*19,lwidth,bheight});
         }
         //Closes window
         break;
      }
      //Close(complete)
      case 3:{
         printf("<--QUIT-->\n");
         EndDrawing();
         CloseWindow();
         printf("<--Done-->\n");
         exit(EXIT_SUCCESS);
      }
   }
   status = -1;
   for(int i = 4; i < 7; i++){
      Color choice = (i == textbox)?SKYBLUE:WHITE;
      if(draw_lblb(UI[i],choice)){
         textbox = i;
      }else if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
         textbox = -1;
      }
      if(i == textbox){
         short limit = 64;
         switch(textbox){
            case 4:{
               limit = 15;
               break;
            }
            case 5:{
               limit = 6;
               break;
            }
         }
         if(GetKeyPressed()){
            was_pressed=true;
            char cpressed = GetCharPressed();
            if(IsKeyPressed(KEY_BACKSPACE)){
               // printf("<Backspace %d > -1? %d %d>\n",5,5 >= 0,true);
               if(gamefile[i-4].size() >= 0){
                  string sub = gamefile[i-4].substr(0,gamefile[i-4].size()-1);
                  gamefile[i-4] = sub;
               }
            }else if(cpressed > 0){
               if(gamefile[i-4].size() < limit){
                  gamefile[i-4]+=cpressed;
               }
            }
         }
      }
   }
   draw_lbl(UI[7],BLACK);
}

void launcher::init(){
   //read game file

   string content = read(file_loc,filename);

   //splits content by space which is ascii
   //number 32 into a list named gamefile
   split(gamefile,32,content);

   // printf("<0: %s, 1: %s, 2: %s, 3: %s>\n",gamefile[0].c_str(),gamefile[1].c_str(),gamefile[2].c_str(),gamefile[3].c_str());

   validity = (gamefile[1]=="NULL")?"INVALID":"NO SERVER";
   SetTargetFPS(stoi(gamefile[3]));
   set_screen();
}

void launcher::set_screen(){
   string names[NUM_UI] = {"Connect","Login","Play","Quit","Name: "+gamefile[0],"ID: "+gamefile[1],"IP: "+gamefile[2],validity};
   //ADD TEST BOX FOR WHO THE USER IS AND WHAT SERVER THEY ARE CONNECTED TO
   for(int i = 0; i < 4; i++){
      lbl_style(UI[i],names[i],font,spacing,GUI_TEXT_ALIGN_CENTER,ColorToInt(BLUE),{scale,scale+scale*(i*6),bwidth,bheight});
      //debug
      // printStyle(buttons[i]);
   }
   for(int i = 4; i < 7; i++){
      lbl_style(UI[i],names[i],font,spacing,GUI_TEXT_ALIGN_LEFT,ColorToInt(BLACK),{width-(twidth+scale),scale+scale*((i-4)*6),twidth,bheight});
   }
   if(validity=="VALID"){
      lbl_style(UI[7],names[7],font,spacing,GUI_TEXT_ALIGN_CENTER,ColorToInt(GREEN),{width-(twidth+scale),scale*19,lwidth,bheight});
   }else{
      lbl_style(UI[7],names[7],font,spacing,GUI_TEXT_ALIGN_CENTER,ColorToInt(RED),{width-(twidth+scale),scale*19,lwidth,bheight});
   }
}