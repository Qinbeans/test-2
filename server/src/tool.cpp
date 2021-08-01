#include "tool.h"
#include <sys/stat.h>
#include <unistd.h>

#define NUM_CH 255

//fix io
string read(string file_loc, string filename){
   string data_loc = file_loc + filename;
   string content = "";
   FILE* fp;
   #if defined(unix) || defined(__unix__) || defined(__unix) || defined(__MACH__)
      mkdir(file_loc.c_str(),0744);
   #else
      mkdir(file_loc.c_str());
   #endif
   fp = fopen(data_loc.c_str(),"r+");

   if(access(data_loc.c_str(), F_OK) == 0){
      // content <- fill server data of user
      fputs(data_loc.c_str(),fp);
   }else{
      char temp[NUM_CH];
      fgets(temp,NUM_CH,fp);
      content = temp;
   }
   return content;
}

void write(string file_loc, string filename, string message){
   string data_loc = file_loc + filename;
   FILE* fp;
   #if defined(unix) || defined(__unix__) || defined(__unix) || defined(__MACH__)
      mkdir(file_loc.c_str(),0744);
   #else
      mkdir(file_loc.c_str());
   #endif
   fp = fopen(data_loc.c_str(),"w");
   fputs(message.c_str(),fp);
   fclose(fp);
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