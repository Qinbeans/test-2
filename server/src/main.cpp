/**
 * @file main.cpp
 * @author Ryan Fong (rybeats@live.com)
 * @brief (HEAVILY WIP) Interacts with clients
 *    and does a majority of the interactions
 *    between players to prevent hacking.
 * @version 0.1
 * @date 2021-08-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "net.h"
// #include <enet/enet.h>
#define NUM_CLIENTS 32

int main(){
   string packet;
   network net("",25570,NUM_CLIENTS,2,0,0);
   net.start();
   net.poll(packet);
   
   // if (enet_initialize())
   // {
   //    printf ("<An error occurred while initializing ENet.>\n");
   //    return EXIT_FAILURE;
   // }
   // atexit (enet_deinitialize);

   // ENetAddress address;
   // ENetHost* server;
   // ENetEvent event;
   // address.host = ENET_HOST_ANY;
   // address.port = 25570;

   // server = enet_host_create(&address,NUM_CLIENTS,2,0,0);
   // if(server == NULL){
   //    printf ("<Server Could Not Be Made>\n");
   //    return EXIT_FAILURE;
   // }

   // while(true){
   //    while(enet_host_service(server,&event,10)>0){
   //       switch (event.type)
   //       {
   //       case ENET_EVENT_TYPE_CONNECT:
   //          printf ("A new client connected from %x:%u.\n", 
   //             event.peer -> address.host,
   //             event.peer -> address.port);
   //          /* Store any relevant client information here. */
   //          // event.peer -> data = "Client information";
   //          break;
   //       case ENET_EVENT_TYPE_RECEIVE:
   //          printf ("A packet of length %u containing %s was received from %s on channel %u.\n",
   //             event.packet -> dataLength,
   //             event.packet -> data,
   //             (char*)event.peer -> data,
   //             event.channelID);
   //          /* Clean up the packet now that we're done using it. */
   //          enet_packet_destroy (event.packet);
   //          break;
   //       case ENET_EVENT_TYPE_DISCONNECT:
   //          printf ("%s disconnected.\n", (char*)event.peer -> data);
   //          /* Reset the peer's client information. */
   //          event.peer -> data = NULL;
   //       }
   //    }
   // }

   // enet_host_destroy(server);
}