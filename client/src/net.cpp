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
   client = enet_host_create(NULL,outgoing,channels,inbandwidth,outbandwidth);
   if(client == NULL){
      printf("<Could not create client>\n");
      return EXIT_FAILURE;
   }
   printf("<ENet client started>\n");
   return EXIT_SUCCESS;
}

network::network(){
   printf("<Default network>\n");
   addressName = "";
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

bool network::connect(string connectData){
   ENetPeer* workingServer;
   ENetHost* workingClient;
   ENetEvent netEvent;
   ENetAddress tempAdd;
   if(addressName != "" && port != 0){
      enet_address_set_host(&tempAdd, addressName.c_str());
      tempAdd.port = port;
      server = enet_host_connect((ENetHost*)client,&tempAdd,2,0);
      if((ENetPeer*)server==NULL){
         printf("<Connection impossible>\n");
         return EXIT_FAILURE;
      }
      //setup so we can easily work on networking without repetitive casting
      workingServer = (ENetPeer*)server;
      workingClient = (ENetHost*)client;
   }else{
      printf("<No address or port>\n");
      return EXIT_FAILURE;
   }
   printf("<Connection possible>\n");
   if(enet_host_service(workingClient, &netEvent,1000) > 0){
      switch(netEvent.type){
         case ENET_EVENT_TYPE_CONNECT:{
            printf("<Connected to %d:%d>\n",tempAdd.host,tempAdd.port);
            string data = "0 "+connectData;
            ENetPacket* user = enet_packet_create(data.c_str(), data.size()+1,ENET_PACKET_FLAG_RELIABLE);
            enet_peer_send(workingServer, 0, user);
            return EXIT_SUCCESS;
         }
         default:{
            enet_peer_reset(workingServer);
            printf("<Connection to %d:%d failed>\n",tempAdd.host,tempAdd.port);
            break;
         }
      }
   }
   printf("<Connection denied, no server>\n");
   enet_peer_disconnect(workingServer, 0);
   workingServer = NULL;
   workingClient = NULL;
   return EXIT_FAILURE;
}

void network::sendPacket(string data){
   ENetPacket* packet = enet_packet_create(data.c_str(), strlen(data.c_str())+1,ENET_PACKET_FLAG_RELIABLE);
   enet_peer_send((ENetPeer*)server, 0, packet);
}

bool network::disconnect(){
   ENetHost* workingClient = (ENetHost*) client;
   ENetEvent netEvent;
   if(workingClient==NULL){
      printf("<Client does not exist>\n");
      return EXIT_FAILURE;
   }
   while(enet_host_service(workingClient,&netEvent, 100) > 0){
      switch(netEvent.type){
         case ENET_EVENT_TYPE_RECEIVE:{
            enet_packet_destroy(netEvent.packet);
            break;
         }
         case ENET_EVENT_TYPE_DISCONNECT:{
            printf("<Disconnection Succeeded>");
            break;
         }
      }
   }
   enet_host_destroy(workingClient);
   return EXIT_SUCCESS;
}


//poll outside main loop
string network::poll(){
   ENetHost* workingClient = (ENetHost*) client;
   while(true){
      ENetEvent event;
      while(enet_host_service(workingClient,&event,100) > 0){
         switch(event.type){
            case ENET_EVENT_TYPE_RECEIVE:{
               printf("<A packet of length %u containing %s was received from %s on channel %u.>\n",
                  event.packet->dataLength,
                  event.packet->data,
                  event.peer->data,
                  event.channelID);
               enet_packet_destroy(event.packet);
               break;
            }
         }
      }
   }
}