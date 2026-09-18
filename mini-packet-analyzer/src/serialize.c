#include <string.h>
#include "serialize.h"

int packet_serialize(const Packet *packet,uint8_t *buffer,size_t buffer_size) 
{
  size_t offset=0;

  if(buffer_size >  sizeof(Packet)) 
    {
      return 0;
    }
  
  memcpy(buffer+offset, &packet->version,sizeof(packet->version));
  offset += sizeof(packet->version) ;

  uint8_t type = (uint8_t)packet->type;
  memcpy(buffer+offset, &type, sizeof(type));
  offset += sizeof(type);

  memcpy(buffer+offset, &packet->flags, sizeof(packet->flags));
  offset += sizeof(packet->flags);

  memcpy(buffer+offset, &packet->length, sizeof(packet->length));
  offset += sizeof(packet->length);

  memcpy(buffer+offset, &packet->sequence, sizeof(packet->sequence));
  offset += sizeof(packet->sequence);
  
  memcpy(buffer+offset, packet->payload, sizeof(packet->payload));
  offset += strlen(packet->payload);


  return (int)offset;
}
