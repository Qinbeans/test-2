/**
 * @file main.cpp
 * @author Ryan Fong (rybeats@live.com)
 * @brief Just a main function to start everything
 * @version 0.1
 * @date 2021-07-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "launcher_scene.h"

int main(int argc, char* argv[]){
   printf("<Path: %s>\n",argv[0]);
   printf("<--Start-->\n");
   launcher launchpage("Welcome",argv[0],960,540,FLAG_WINDOW_RESIZABLE);
   printf("<--Done-->\n");
   return EXIT_SUCCESS;
}
