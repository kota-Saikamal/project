#include "ipv6.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

#define IPV6_HEADER_SIZE 40

ids_parse_result_t ids_parse_ipv6 (
 const uint8_t *data,
 size_t length,
 ids_packet_t *packet
 )
 {
   char src[INET6_ADDRSTRLEN];
   char dst[INET6_ADDRSTRLEN];

   if ( data == NULL || packet == NULL) {
      return IDS_PARSE_INVALID_ARGUMENT;
    }

    if (length < IPV6_HEADER_SIZE) {
      return IDS_PARSE_TRUNCATED;
    }

    uint8_t version = data[0] >> 4;
    
    if(version != 6) {
          return IDS_PARSE_MALFORMED;
     }

     uint16_t payload_length;

     memcpy(&payload_length, data+4,sizeof(payload_length));
     payload_length = ntohs(payload_length);

     if( payload_length > (length - IPV6_HEADER_SIZE) ) {
         return IDS_PARSE_TRUNCATED;
      }

      memcpy (
      		packet->source_ip.address,
      		data + 8,
      		16
      );

      packet->source_ip.is_ipv6 = true;

      memcpy (
      		packet->destination_ip.address,
      		data + 24,
      		16
      );
      
      packet->destination_ip.is_ipv6 = true;

      
     
     uint8_t next_header = data[6];

      switch(next_header) {

         case 6:
         	packet->protocol = IDS_PROTOCOL_TCP;
         	break;
         case 17:
         	packet->protocol = IDS_PROTOCOL_UDP;
         	break;
         case 58:
         	packet->protocol = IDS_PROTOCOL_ICMPV6;
         	break;
         default:
         	packet->protocol = IDS_PROTOCOL_UNKOWN;
         
      }

      packet->payload = data + IPV6_HEADER_SIZE;
      packet->payload_length = payload_length;
      packet->packet_length = length; 

      inet_ntop(
         AF_INET6,
         packet->source_ip.address,
         src,
         sizeof(src)
      );

      printf("Source: %s\n",src);

      inet_ntop(
      	 AF_INET6,
      	 packet->destination_ip.address,
      	 dst,
      	 sizeof(dst)
      );

      printf("Destination: %s\n",src);

       

     
   return IDS_PARSE_OK;
 }
