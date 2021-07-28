#define RNET_IMPLEMENTATION
#include "tool.h"
#include "net.h"
#include "raylib.h"
#include <stdio.h>

int main(){
   printf("<--Start-->\n");
   network net("localhost",25570,1,2,0,0);
   net.start();
   net.connect();
   printf("<--Done-->\n");
}
