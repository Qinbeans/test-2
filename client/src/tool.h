
#include "raylib.h"
#include <string>

#ifndef TOOL_H
#define TOOL_H

#define CHUNK 50

using std::string;

typedef struct Style{
   string name;
   float font;
   float spacing;
   int align;
   int color;
   Rectangle frame;
}Style;

bool draw_lblb(Style style, Color frame_color);

void draw_lbl(Style style, Color frame_color);

void draw_txt(Style style, Color frame_color, char* text, int txt_len, bool edit_mode);

void printStyle(Style style);

void set_style_name(Style& style, string name);

void lbl_style(Style& style,string name, float font, float spacing,int align, int color, Rectangle frame);

void set_sty_font(Style& style, float font);

void set_sty_spacing(Style& style, float spacing);

void set_sty_rect(Style& style, Rectangle rect);

#endif