/**
 * @file net.h
 * @author Ryan Fong (rybeats@live.com)
 * @brief Enet wrapper to avoid collisions and keep things simple
 * @date 2021-07-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <string>

#ifndef _WIN32
#include <string.h>
#endif

using std::string;

#ifndef NET_H
#define NET_H

class network{
   private:
      void* client;
      void* peer;
   public:
      network();//default
      ~network();
      void poll();//[0] = status, [...] = actions
      int init();//check connection
      int disconnect();
      int connect(string domain,int port,string data);
      int send(string data);
};

#endif