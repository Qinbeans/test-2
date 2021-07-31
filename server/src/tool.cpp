#include "tool.h"


//fix io
string read(string file_loc, string filename){
   string data_loc = file_loc + filename;
   string content = "";
   if(!DirectoryExists(file_loc.c_str())){
      #if defined(unix) || defined(__unix__) || defined(__unix) || defined(__MACH__)
         mkdir(file_loc.c_str(),0744);
      #else
         mkdir(file_loc.c_str());
      #endif
   }
   if(!FileExists(data_loc.c_str())){
      // content <- fill server data of user
      SaveFileText(data_loc.c_str(),(char*)content.c_str());
   }else{
      content = LoadFileText(data_loc.c_str());
   }
   return content;
}

void write(string file_loc, string filename, string message){
   string data_loc = file_loc + filename;
   if(!DirectoryExists(file_loc.c_str())){
      #if defined(unix) || defined(__unix__) || defined(__unix) || defined(__MACH__)
         mkdir(file_loc.c_str(),0744);
      #else
         mkdir(file_loc.c_str());
      #endif
   }
   if(!FileExists(data_loc.c_str())){
      printf("<File being created>\n");
   }
   SaveFileText(data_loc.c_str(),(char*)message.c_str());
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