/**
 * @file net.cpp
 * @author Ryan Fong (rybeats@live.com)
 * @brief A wrapper for ENet to do two things:
 *    avoid conflicts with Raylib and to simplify ENet
 * @version 0.1
 * @date 2021-07-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <enet/enet.h>
#include "net.h"

bool network::start(){
   if(enet_initialize() != 0){
      printf("<Could not start ENet>\n");
      return EXIT_FAILURE;
   }
   atexit(enet_deinitialize);
   if(addressName == ""){
      ENetAddress temp;
      temp.host=ENET_HOST_ANY;
      temp.port=port;
      client = enet_host_create(&temp,outgoing,channels,inbandwidth,outbandwidth);
   }else{
      client = enet_host_create(NULL,outgoing,channels,inbandwidth,outbandwidth);
   }
   if(client == NULL){
      printf("<Could not create Server>\n");
      return EXIT_FAILURE;
   }
   printf("<ENet Server started>\n");
   return EXIT_SUCCESS;
}

network::network(){
   printf("<Default network>\n");
   addressName = std::to_string(ENET_HOST_ANY);
   port = 0;
   //number of outbound connections
   outgoing = 1;
   //in and out channels
   channels = 2;
   //bandwidth is how many lanes of information we can use for a task
   inbandwidth = 0;//assumes any amount in bandwidth
   outbandwidth = 0;//assume any amount out bandwidth
}

network::~network(){
   delete (ENetHost*)client;
   delete (ENetPeer*)server;
}

network::network(string address, unsigned short port, int outgoing, int channels, int inbandwidth, int outbandwidth){
   addressName = address;
   this->port = port;
   this->outgoing = outgoing;
   this->channels = channels;
   this->inbandwidth = inbandwidth;
   this->outbandwidth = outbandwidth;
}

void network::sendPacket(string data){
   ENetPacket* packet = enet_packet_create(data.c_str(), strlen(data.c_str())+1,ENET_PACKET_FLAG_RELIABLE);
   enet_peer_send((ENetPeer*)server, 0, packet);
}

void network::poll(string& data){
   ENetHost* me = (ENetHost*) client;
   printf("<Polling network: %x:%d>\n",me->address.host,me->address.port);
   if(me == NULL){
      printf("<Empty Client>\n");
      data = "";
      return;
   }
   string out;
   ENetEvent event;
   while(true){
      while(enet_host_service(me,&event,10) > 0){
         printf("<STAT: %d>\n",event.type);
         switch(event.type){
            case ENET_EVENT_TYPE_CONNECT:{
               printf("<Connected from %x:%d>\n",event.peer->address.host,event.peer->address.port);
               break;
            }
            case ENET_EVENT_TYPE_RECEIVE:{
               printf("<A packet of length %u containing %s was received from %x.>\n",
                  event.packet->dataLength,
                  event.packet->data,
                  event.peer->address.host);
               // event.peer->address.host;
               // out = (char*)event.packet->data;
               enet_packet_destroy(event.packet);
               break;
            }
            case ENET_EVENT_TYPE_DISCONNECT:{
               printf("<%x:%d disconnected...>\n",event.peer->address.host,event.peer->address.port);
               event.peer->data = NULL;
               break;
            }
            case ENET_EVENT_TYPE_NONE:{
               printf("<Nani?>\n");
               break;
            }
         }
      }
   }
}