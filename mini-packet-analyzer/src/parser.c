#include "parser.h"
#include "storage.h"
#include "input.h"
#include "error.h"
#include "validation.h"
#include <string.h>
#include <stdio.h>
#define MAX_FILE 528
int packet_deserialize(const uint8_t *buffer, size_t buffer_size, Packet *packet)
{
  size_t  offset=0;

  if(buffer_size < 10 ) {
     
     return 0;
  }

  memcpy(&packet->version,buffer+offset,sizeof(packet->version));
  offset += sizeof(packet->version);

  uint8_t type;
  memcpy(&type,buffer+offset,sizeof(type));
  packet->type = (PacketType)type;
  offset += sizeof(type);

  memcpy(&packet->flags,buffer+offset,sizeof(packet->flags));
  offset += sizeof(packet->flags);

  memcpy(&packet->length,buffer+offset,sizeof(packet->length));
  offset += sizeof(packet->length);

  memcpy(&packet->sequence,buffer+offset,sizeof(packet->sequence));
  offset += sizeof(packet->sequence);


  if(packet->length >=MAX_PAYLOAD_SIZE || ((size_t)packet->length +offset > buffer_size))
  {
     return 0;
  }
   
  memcpy(packet->payload, buffer+offset, packet->length);     
  packet->payload[packet->length] = '\0';

  return 1;
 
}

void parse_packet() 
{
   Packet reversed;
   uint8_t buffer[MAX_PAYLOAD_SIZE];
   size_t size = sizeof(buffer);

   char filename[MAX_FILE];

   input_get_string("Enter your file path: ",filename,sizeof(filename));
  
   int bytes = packet_upload(buffer,size,filename);
  
   PacketError error;   
   if(packet_deserialize(buffer,(size_t)bytes,&reversed))
    {  error = packet_validate(&reversed);
       if(error== ERROR_NONE)
         packet_display(&reversed);
       else
         error_display(error);
     }
     else {
        printf("Deserialization failed\n");
     }
       
}
   
