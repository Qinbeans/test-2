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

network::network(){
   printf("<ENET START>\n");
   client = nullptr;
   peer = nullptr;
}

network::~network(){
   delete (ENetHost*)client;
   delete (ENetPeer*) peer;
}

network::network(string address, unsigned short port, int outgoing, int channels, int inbandwidth, int outbandwidth){
   addressName = address;
   this->port = port;
   this->outgoing = outgoing;
   this->channels = channels;
   this->inbandwidth = inbandwidth;
   this->outbandwidth = outbandwidth;
}

int network::init(){
   printf("<ENET INIT>\n");
   if (enet_initialize() != 0) {
      printf("An error occured while initializing ENet.\n");
      return EXIT_FAILURE;
   }
   atexit(enet_deinitialize);
   return EXIT_SUCCESS;
}

int network::connect(string domain,int port,string data){
   printf("<ENET CONNECT>\n");
   ENetAddress address;
   ENetEvent event;

   client = enet_host_create(NULL, 1, 2, 0, 0);
   if (client == NULL) {
      fprintf(stderr, "An error occured while trying to create an ENet server host\n");
      return EXIT_FAILURE;
   }
   enet_address_set_host(&address, domain.c_str());
   address.port = port;

   peer = enet_host_connect((ENetHost*)client, &address, 2, 0);

   if (peer == NULL) {
      fprintf(stderr, "No available peers for initializing an ENet connection");
      return EXIT_FAILURE;
   }
   if(enet_host_service((ENetHost*)client, &event, 100) > 0) {
      switch(event.type) {
         case ENET_EVENT_TYPE_CONNECT:{
            printf("(Client) We got a new connection from %x\n",event.peer->address.host);
            send(data);
            break;
         }
         case ENET_EVENT_TYPE_DISCONNECT:{
            printf("(Client) %s disconnected.\n", event.peer->data);
            // Reset client's information
            event.peer->data = NULL;
            break;
         }
      }
   }
   return EXIT_SUCCESS;
}

int network::send(string data){
   printf("<ENET SEND>\n");
   int ret;
   ENetPacket* packet = enet_packet_create(data.c_str(), data.size()+1,ENET_PACKET_FLAG_RELIABLE);
   ret = enet_peer_send((ENetPeer*)peer, 0, packet);
   printf("<Send Stat: %d>\n",ret);
   return ret;
}

int network::disconnect(){
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

string network::poll(){
   ENetHost* workingClient = (ENetHost*) client;
   ENetEvent event;
   while(true){
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