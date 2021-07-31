#include <string>

using std::string;

#define MAX_INV_WIDTH 10
#define MAX_INV_HEIGHT 4
#define NUM_DATA 20

typedef struct player{
   string id;
   string name;
   int xp;//xp
   int fhp;//full health
   int chp;//current health
   float def;//defense
   float dmg;//damage
   float rng;//range
   string inventory[MAX_INV_HEIGHT][MAX_INV_WIDTH];
   float x;
   float y;
   /**
    * r - right hand
    * l - left hand
    * g - glove
    * H - head
    * C - chest
    * P - pants
    * S - shoes
    * R - rings
    * B - books
    * <BLANK> - free inventory space
    * x - space cannot be used
    * 
    * |-|-|-|-|-|-|-|-|-|-|
    * |x|x|H|x|x| | | | | |
    * |-|-|-|-|-|-|-|-|-|-|
    * |l|g|C|r|x| | | | | |
    * |-|-|-|-|-|-|-|-|-|-|
    * |R|x|P|x|B| | | | | |
    * |-|-|-|-|-|-|-|-|-|-|
    * |R|x|S|x|B| | | | | |
    * |-|-|-|-|-|-|-|-|-|-|
    * 
    */
}player;

string read(string file_loc, string filename);

void write(string file_loc, string filename, string message);

void split(string strong_data[NUM_DATA], const char delim, string data);