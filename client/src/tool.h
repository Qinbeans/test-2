#include "raylib.h"
#include <string>

#ifndef TOOL_H
#define TOOL_H

#define CHUNK 50
#define NUM_DATA 5

using std::string;

#if defined(__APPLE__)
#define GAMEDIR ".EON"
const string OS = "mac";
#elif defined(_WIN32)
#define GAMEDIR "/AppData/LocalLow/EON"
const string OS = "win";
#else
#define GAMEDIR ".EON"
const string OS = "uni";
#endif

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

string read(string file_loc, string filename);

void write(string file_loc, string filename, string message);

void split(string strong_data[NUM_DATA], const char delim, string data);

string get_game_dir();

#endif