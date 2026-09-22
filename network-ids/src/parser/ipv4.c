#include "ipv4.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

#define IPV4_MIN_HEADER_SIZE 20


ids_parse_result_t ids_parse_ipv4(
	const uint8_t *data,
	size_t length,
	ids_packet_t *packet
)
{
   char src[INET_ADDRSTRLEN];
   char dst[INET_ADDRSTRLEN];

   

   
   if (data == NULL || packet == NULL ) {
        return IDS_PARSE_INVALID_ARGUMENT;
    }


    if (length < IPV4_MIN_HEADER_SIZE) {
         return IDS_PARSE_TRUNCATED;
     }


     uint8_t version = data[0] >> 4;
     uint8_t ihl = data[0] & 0x0F;


     if(version != 4) {
         return IDS_PARSE_MALFORMED;
     }

     size_t header_length = ihl * 4;

     if(header_length < IPV4_MIN_HEADER_SIZE) {
          return IDS_PARSE_MALFORMED;
     }

     if(header_length > length) {
          return IDS_PARSE_TRUNCATED;
      }


     uint16_t total_length;

     memcpy(&total_length, data + 2, sizeof(total_length));

     total_length = ntohs(total_length);

     if(total_length < header_length) {
        return  IDS_PARSE_MALFORMED;
      }

      if (total_length > length ) {
         return IDS_PARSE_TRUNCATED;
      }


      memcpy(
          packet->source_ip.address,
          data + 12,
          4
      );

      packet->source_ip.is_ipv6 = false;


      memcpy(
          packet->destination_ip.address,
          data+16,
          4
       );

       packet->destination_ip.is_ipv6 = false;


       uint8_t protocol = data[9];

       
        switch(protocol) {
           case 6:
           	   packet->protocol = IDS_PROTOCOL_TCP;
           	   break;
           	   
           case 17:
           	   packet->protocol = IDS_PROTOCOL_UDP;
           	   break;
           	   
           case 1:
           	   packet->protocol = IDS_PROTOCOL_ICMP;
           	   break;
           	   
           default:
           	   packet->protocol = IDS_PROTOCOL_UNKOWN;
           	   break;
       }


	 packet->payload = data + header_length;
	 packet->payload_length = total_length - header_length;

	 packet->packet_length = total_length;
    
    
     printf("IPv4 packet\n");
     printf("Protocol: %d\n",protocol);
     printf("Header length: %zu\n", header_length);
     printf("Total length: %u\n",total_length);

     inet_ntop(AF_INET, packet->source_ip.address, src, sizeof(src));
     inet_ntop(AF_INET, packet->destination_ip.address, dst, sizeof(dst));

     printf("Source: %s\n",src);
     printf("Destination: %s\n",dst);
         
	 return IDS_PARSE_OK;
}
