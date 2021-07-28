#define RNET_IMPLEMENTATION
#include "tool.h"
#include "net.h"
#include "raylib.h"
#include <stdio.h>

int main(){
   int result = 1;
   printf("<--Start-->\n");
   network net("localhost",25570,1,2,0,0);
   if(net.start()==EXIT_FAILURE){
      printf("<--FAILED-->\n");
      return EXIT_FAILURE;
   }
   if(net.connect("Hello There")==EXIT_FAILURE){
      printf("<--FAILED-->\n");
      return EXIT_FAILURE;
   }
   if(net.disconnect()==EXIT_FAILURE){
      printf("<--FAILED-->\n");
      return EXIT_FAILURE;
   }
   printf("<--Done-->\n");
}
