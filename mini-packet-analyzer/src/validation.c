#include <string.h>
#include <stdio.h>
#include "validation.h"
#include "error.h"

PacketError packet_validate(const Packet *packet)
{
    /* Version */ 
    if(packet -> version != 1)
      { return ERROR_INVALID_VERSION; }

    /* Type */
    if(packet->type !=PACKET_DATA && packet->type !=PACKET_ACK && packet->type !=PACKET_ERROR)

       { return ERROR_INVALID_TYPE; }

    /* Sequence */
    if(packet -> sequence ==0)
      return ERROR_INVALID_SEQUENCE; 

  

   /* Flags */

   if( !(packet-> flags))
       return ERROR_NO_FLAG;
   
   if((packet->type == PACKET_ACK) && (!(packet->flags & FLAG_ACK) || (packet->flags & FLAG_SYN) || (packet -> flags & FLAG_ERROR))) 
       return ERROR_ACK_FLAG;

   
   if((!(packet->flags & FLAG_ACK) || !(packet->flags & FLAG_SYN) || (packet->flags & FLAG_ERROR)) && (packet->type == PACKET_DATA))
       return ERROR_DATA_FLAG;
 
    
   if((packet->type == PACKET_ERROR) && (!(packet->flags & FLAG_ERROR) || (packet->flags & FLAG_ACK) || (packet->flags & FLAG_SYN)))
       return ERROR_ERROR_FLAG;

  /* Payload length */
   if(packet->length >= MAX_PAYLOAD_SIZE)
       return ERROR_INVALID_PAYLOAD;

   if(packet->length != strlen(packet->payload))
      return ERROR_INVALID_LENGTH;
 

   return ERROR_NONE;
}
    
int validate_extension(const char *filename)
{
   FILE *fd = fopen(filename,"rb");
   if(fd==NULL){
      return 0;
    }
   const char *ext = strrchr(filename,'.');
   return (ext!=NULL && strcmp(ext,".bin")==0);
}

