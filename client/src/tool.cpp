#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "tool.h"

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