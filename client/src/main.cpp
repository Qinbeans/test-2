#include "net.h"
#include "launcher_scene.h"


int main(){
   printf("<--Start-->\n");
   // network net("localhost",25570,1,2,0,0);
   // if(net.start()==EXIT_FAILURE){
   //    printf("<--FAILED-->\n");
   //    return EXIT_FAILURE;
   // }
   // if(net.connect("Hello There")==EXIT_FAILURE){
   //    printf("<--FAILED-->\n");
   //    return EXIT_FAILURE;
   // }
   // if(net.disconnect()==EXIT_FAILURE){
   //    printf("<--FAILED-->\n");
   //    return EXIT_FAILURE;
   // }
   launcher launchpage("Welcome",1920,1080,FLAG_WINDOW_RESIZABLE);
   printf("<--Done-->\n");
   return EXIT_SUCCESS;
}
