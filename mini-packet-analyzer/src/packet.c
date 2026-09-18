#include "packet.h"
#include <stdio.h>
#include <string.h>
#include "input.h"
#include "validation.h"
#include "serialize.h"
#include "storage.h"
#define MAX_FILE 528
void packet_init(Packet *packet) 
{ 
   packet -> version =1;
   packet -> type=1;
   packet -> flags=0;
   packet -> length=0;
   packet -> sequence=1;
   packet -> payload[0]='\0';
}

void packet_display(const Packet *packet)
{ 
  printf("Version : %u\n",packet->version);
  switch (packet -> type) {
    case PACKET_DATA:
         printf("Type :DATA\n");
         break;
    case PACKET_ACK:
         printf("Type :ACK\n");
         break;
    case PACKET_ERROR:
         printf("Type :ERROR\n");
         break;
    default : 
         printf("Type: Unknown\n");
   }

   printf("Flag: ");
   if(packet_has_flag(packet,FLAG_ACK)) {
       printf("ACK ");
   }
   if(packet_has_flag(packet,FLAG_SYN)) {
       printf("SYN ");
   }
   if(packet_has_flag(packet,FLAG_ERROR)) {
       printf("ERROR ");
   }
   if(packet_has_flag(packet,FLAG_PRIORITY)) {
       printf("PRIORITY ");
   }

   if(!(packet->flags&FLAG_ACK) && !(packet->flags & FLAG_SYN) && !(packet->flags & FLAG_ERROR) && !(packet->flags & FLAG_PRIORITY)) {
      printf("NO ");
   }
   printf("\n");
   printf("Length: %u\n",packet->length);
   printf("Sequence: %u\n",packet->sequence);
   printf("Payload: %s\n",packet->payload);
}


int  packet_set_payload(Packet *packet, const char *new_payload) {
  size_t length = strlen(new_payload);
  if(length >= MAX_PAYLOAD_SIZE) {
      return 0;
   }
  strcpy(packet->payload,new_payload);
  packet->length = (uint16_t)length;
  return 1;
}


void packet_set_flag(Packet *packet,uint16_t flag) {
   packet -> flags |=flag;

}


void packet_clear_flag(Packet *packet,uint16_t flag) {
   packet -> flags &=(uint16_t)~flag;
 }

 int packet_has_flag(const Packet *packet,uint16_t flag) {
   return (packet -> flags & flag)!=0;
 }



void packet_build(Packet *packet,uint8_t *buffer,const char *filename) {
  
  char input[MAX_PAYLOAD_SIZE];

  packet_init(packet);

  input_get_flags(packet);
  packet->type = input_get_type();
  packet->version = input_get_version();
  packet->sequence = input_get_sequence();
  
  getchar();
  
  input_get_string("Enter payload: ",input,sizeof(input));
  
  if(!packet_set_payload(packet,input))
  {
    printf("Failed to set payload\n");
    return;
  }
  

  PacketError error = packet_validate(packet);
 
  if(error == ERROR_NONE )
  {
    printf("Packet is valid\n");
    packet_display(packet);
  }
  else 
  {
    printf("Packet is Invalid\n");
    error_display(error);
    return;
  }

  /* serializing */

  int bytes = packet_serialize(packet,buffer,sizeof(buffer));
  packet_save(buffer,(size_t)bytes,filename);
 
} 


void create_packet() 
{
   Packet new_packet;
   uint8_t buffer[MAX_PAYLOAD_SIZE];
   size_t size = sizeof(buffer);
   char filename[MAX_FILE];
   
   input_get_string("Enter your file path: ",filename,sizeof(filename));
    
   packet_build(&new_packet,buffer,filename);

}
