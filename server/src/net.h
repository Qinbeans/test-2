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
      void* server;
      string addressName;
      unsigned short port;
      int outgoing;
      int channels;
      int inbandwidth;
      int outbandwidth;
   public:
      network();//default
      network(string address, unsigned short port, int outgoing, int channels, int inbandwidth, int outbandwidth);
      ~network();
      void poll(string&);//[0] = status, [...] = actions
      bool start();//check connection
      bool disconnect();
      bool connect(string connectData);
      void sendPacket(string data);
};

#endif