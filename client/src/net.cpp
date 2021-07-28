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

network::network(string address, unsigned short port, int outgoing, int channels, int inbandwidth, int outbandwidth){
   addressName = address;
   this->port = port;
   this->outgoing = outgoing;
   this->channels = channels;
   this->inbandwidth = inbandwidth;
   this->outbandwidth = outbandwidth;
}

bool network::connect(){
   ENetPeer* workingServer;
   ENetHost* workingClient;
   ENetEvent netEvent;
   ENetAddress tempAdd;
   if(addressName != "" && port != 0){
      enet_address_set_host(&tempAdd, addressName.c_str());
      tempAdd.port = port;
      server = enet_host_connect((ENetHost*)client,&tempAdd,2,0);
      if((ENetPeer*)server==NULL){
         printf("<ENet Bad Client>\n");
         return EXIT_FAILURE;
      }
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
            // string data = "0 "+me->get_packet();
            // ENetPacket* user = enet_packet_create(data.c_str(), data.size()+1,ENET_PACKET_FLAG_RELIABLE);
            // enet_peer_send(peer, 0, user);
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
void network::clean(){
   printf("<Cleaning Memory>\n");
   free((ENetHost*)client);
   free((ENetPeer*)server);
}

