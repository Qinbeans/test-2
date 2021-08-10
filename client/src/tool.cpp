/**
 * @file tool.cpp
 * @author Ryan Fong (rybeats@live.com)
 * @brief Ambiguous code to help do small tasks.
 *    Created partly because the C libraries used
 *    were not very readable by themselves.
 * @version 0.1
 * @date 2021-08-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "tool.h"
#include "unistd.h"
#if defined(unix) || defined(__unix__) || defined(__unix) || defined(__MACH__)
#include <sys/stat.h>
#endif

#define DEFAULT_NAME "NULL"
#define DEFAULT_ID "NULL"
#define DEFAULT_IP "localhost"
#define DEFAULT_FULL 0
#define DEFAULT_FPS 60

void lbl_style(Style& style,string name, float font, float spacing,int align, int color, Rectangle frame){
   style = {name,font,spacing,align,color,frame};
}

bool draw_lblb(Style style, Color frame_color){
   DrawRectangleRec(style.frame, frame_color);
   GuiSetStyle(DEFAULT,TEXT_SIZE,style.font);
   GuiSetStyle(DEFAULT,TEXT_SPACING,style.spacing);
   GuiSetStyle(LABEL, TEXT_ALIGNMENT, style.align);
   GuiSetStyle(LABEL, TEXT + (guiState*3), style.color);
   return GuiLabelButton(style.frame, style.name.c_str());
}

void draw_lbl(Style style, Color frame_color){
   DrawRectangleRec(style.frame, frame_color);
   GuiSetStyle(DEFAULT,TEXT_SIZE,style.font);
   GuiSetStyle(DEFAULT,TEXT_SPACING,style.spacing);
   GuiSetStyle(LABEL, TEXT_ALIGNMENT, style.align);
   GuiSetStyle(LABEL, TEXT + (guiState*3), style.color);
   GuiLabel(style.frame,style.name.c_str());
}

void draw_txt(Style style, Color frame_color, char* text, int txt_len, bool edit_mode){
   DrawRectangleRec(style.frame, frame_color);
   GuiSetStyle(DEFAULT,TEXT_SIZE,style.font);
   GuiSetStyle(DEFAULT,TEXT_SPACING,style.spacing);
   GuiSetStyle(LABEL, TEXT_ALIGNMENT, style.align);
   GuiSetStyle(LABEL, TEXT + (guiState*3), style.color);
   GuiTextBox(style.frame,text,txt_len,edit_mode);
}

void printStyle(Style style){
   printf("Name: %s | Font: %f| Spacing: %f| Align: %d | Color: %d | Rectangle:\n\t{ X: %f| Y: %f | Width: %f | Height: %f }\n",style.name.c_str(),style.font,style.spacing,style.align,style.color,style.frame.x,style.frame.y,style.frame.width,style.frame.height);
}

void set_style_name(Style& style, string name){
   style.name = name;
}

void set_sty_font(Style& style, float font){
   style.font=font;
}

void set_sty_spacing(Style& style, float spacing){
   style.spacing=spacing;
}

void set_sty_rect(Style& style, Rectangle rect){
   style.frame=rect;
}

string read(string file_loc, string filename){
   string data_loc = file_loc + filename;
   string content = "";
   if(!DirectoryExists(file_loc.c_str())){
      #if defined(unix) || defined(__unix__) || defined(__unix) || defined(__MACH__)
         mkdir(file_loc.c_str(),0744);
      #else
         mkdir(file_loc.c_str());
      #endif
   }
   if(!FileExists(data_loc.c_str())){
      content = string(DEFAULT_NAME)+" "+string(DEFAULT_ID)+" "+string(DEFAULT_IP)+" "+std::to_string(DEFAULT_FPS)+" "+std::to_string(DEFAULT_FULL);
      SaveFileText(data_loc.c_str(),(char*)content.c_str());
   }else{
      content = LoadFileText(data_loc.c_str());
   }
   return content;
}

   // string base_dir = GAMEDIR;
   // string content = message;
   // if(OS == "win"){
   //    base_dir = getenv("USERPROFILE") + base_dir;
   // }else{
   //    base_dir = string(getenv("HOME"))+ "/" + base_dir;
   // }
   // string data_loc = base_dir + "/gamedata.inline";

void write(string file_loc, string filename, string message){
   string data_loc = file_loc + filename;
   if(!DirectoryExists(file_loc.c_str())){
      #if defined(unix) || defined(__unix__) || defined(__unix) || defined(__MACH__)
         mkdir(file_loc.c_str(),0744);
      #else
         mkdir(file_loc.c_str());
      #endif
   }
   if(!FileExists(data_loc.c_str())){
      printf("<File being created>\n");
   }
   SaveFileText(data_loc.c_str(),(char*)message.c_str());
}

void split(string strong_data[NUM_DATA], const char delim, string data){
   string temp;
   int out_index = 0;
   for(int i = 0; i < data.size(); i++){
      if(data[i] != delim){
         temp += data[i];
      }
      else{
         strong_data[out_index] = temp;
         out_index++;
         temp = "";
      }
   }
   strong_data[out_index] = temp;
}

string get_game_dir(){
   string base_dir = GAMEDIR;
   if(OS == "win"){
      base_dir = getenv("USERPROFILE") + base_dir;
   }else{
      base_dir = string(getenv("HOME"))+ "/" + base_dir;
   }
   return base_dir;
}

void set_obj(object& obj, string model, string texture, string animation){
   obj.model = LoadModel(model.c_str());
   obj.texture = LoadTexture(texture.c_str());
   SetMaterialTexture(&obj.model.materials[0],MAP_DIFFUSE,obj.texture);
   obj.count = 0;
   obj.animation = LoadModelAnimations(animation.c_str(),&obj.count);
   obj.frame_counter = 0;
}

void set_obj(object& obj, string model, string texture){
   obj.model = LoadModel(model.c_str());
   obj.texture = LoadTexture(texture.c_str());
   obj.count = 0;
   SetMaterialTexture(&obj.model.materials[0],MAP_DIFFUSE,obj.texture);
   obj.frame_counter = 0;
}

void print_obj(const object& obj){
   printf("<--Object-- Bone Count: %d, Count: %d, Frame Count: %d/%d, Pos X: %.2f Y: %.2f Z: %.2f>\n",obj.animation->boneCount,obj.count,obj.frame_counter,obj.animation->frameCount,obj.pos.x,obj.pos.y,obj.pos.z);
}