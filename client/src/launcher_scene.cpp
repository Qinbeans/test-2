#include "launcher_scene.h"
#include "raygui.h"

launcher::launcher(string name, unsigned int width, unsigned int height, int resize){
   this->name = name;
   this->width = width;
   this->height = height;
   scale = this->height/CHUNK;
   int flag=resize;
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
         init();
      }
      update();
      EndDrawing();
   }
   CloseWindow();
}

launcher::~launcher(){
   free(UI);
   free(gamefile);
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
         EndDrawing();
         CloseWindow();
         printf("<--Done-->\n");
         exit(EXIT_SUCCESS);
      }
   }
   for(int i = 4; i < 8; i++){
      draw_lbl(UI[i],BLACK);
   }
}

void launcher::init(){
   //read game file
   float bwidth = scale*10;
   float bheight = scale*3;
   float lwidth = scale*20;
   float font = scale*2;
   float spacing = scale/2;
   
   string base_dir = GAMEDIR;
   if(OS == "win"){
      base_dir = getenv("USERPROFILE") + base_dir;
   }else{
      base_dir = string(getenv("HOME"))+ "/" + base_dir;
   }
   string content = read(base_dir,"/gamedata.inline");

   //splits content by space which is ascii
   //number 32 into a list named gamefile
   split(gamefile,32,content);

   // printf("<0: %s, 1: %s, 2: %s, 3: %s>\n",gamefile[0].c_str(),gamefile[1].c_str(),gamefile[2].c_str(),gamefile[3].c_str());

   validity = (gamefile[1]=="NULL")?"INVALID":"VALID";

   string names[8] = {"Connect","Login","Play","Quit","Name: "+gamefile[0],"ID: "+gamefile[1],"IP: ",validity};
   //ADD TEST BOX FOR WHO THE USER IS AND WHAT SERVER THEY ARE CONNECTED TO
   for(int i = 0; i < 4; i++){
      lbl_style(UI[i],names[i],font,spacing,GUI_TEXT_ALIGN_CENTER,ColorToInt(BLUE),{scale,scale+scale*(i*6),bwidth,bheight});
      //debug
      // printStyle(buttons[i]);
   }
   for(int i = 4; i < 7; i++){
      lbl_style(UI[i],names[i],font,spacing,GUI_TEXT_ALIGN_LEFT,ColorToInt(WHITE),{width-(lwidth+scale),scale+scale*((i-4)*6),lwidth,bheight});
   }
   if(validity=="VALID"){
      lbl_style(UI[7],names[7],font,spacing,GUI_TEXT_ALIGN_LEFT,ColorToInt(GREEN),{width-(lwidth+scale),scale*19,bwidth,bheight});
   }else{
      lbl_style(UI[7],names[7],font,spacing,GUI_TEXT_ALIGN_LEFT,ColorToInt(RED),{width-(lwidth+scale),scale*19,bwidth,bheight});
   }
}