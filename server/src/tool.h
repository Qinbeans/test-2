#include <string>

using std::string;

#define MAX_INV_WIDTH 10
#define MAX_INV_HEIGHT 4
#define NUM_DATA 20
#define NUM_STATS 4

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
* |x|x|H|x|x| | | | | |
* |l|g|C|r|x| | | | | |
* |R|x|P|x|B| | | | | |
* |R|x|S|x|B| | | | | |
* 
*/

typedef struct item{//<- modibility says this should be read from file
    int x;
    int y;
    string name;
    float stats[NUM_STATS];
}item;//<- either copy relevant items to client or send it on spawn

typedef struct player{
   string id;
   string name;
   int xp;//xp
   int fhp;//full health
   int chp;//current health
   float def;//defense
   float dmg;//damage
   float rng;//range
   item inventory[31];
   int inv_width = MAX_INV_WIDTH;
   int inv_height = MAX_INV_HEIGHT;
   float x;
   float y;
   float z;
}player;//<- send relevant data


string read(string file_loc, string filename);

void write(string file_loc, string filename, string message);

void split(string strong_data[NUM_DATA], const char delim, string data);