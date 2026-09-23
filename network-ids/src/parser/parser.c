#include "parser.h"
#include "ipv4.h"
#include "ipv6.h"
#include "ethernet.h"
#include "tcp.h"
#include "udp.h"

ids_parse_result_t ids_match_protocol(ids_packet_t *packet)
{
	switch(packet->protocol) {
		case IDS_PROTOCOL_TCP:
			return ids_parse_tcp(
				packet->payload,
				packet->payload_length,
				&packet->transport.tcp
			);
		case IDS_PROTOCOL_UDP:
			return ids_parse_udp(
				packet->payload,
				packet->payload_length,
				&packet->transport.udp
			);
			
		default:
			return IDS_PARSE_UNSUPPORTED;
	}
}

ids_parse_result_t ids_parse_packet(

    const uint8_t *data,
    size_t length,
    ids_packet_t *packet
 )
 {
    ids_parse_result_t ids_match_protocol(ids_packet_t *packet);
    
    if (data == NULL || packet == NULL ) {
           return IDS_PARSE_INVALID_ARGUMENT;
     }

     if(length == 0) {
           return IDS_PARSE_TRUNCATED;
     }

     ids_parse_result_t result = ids_parse_ethernet(data,length, &packet->ethernet);

     if(result != IDS_PARSE_OK) {
         return result;
     }


     if (packet->ethernet.ether_type == 0x800) {
          ids_parse_result_t result =  ids_parse_ipv4(data+14,length-14,packet);

          if( result != IDS_PARSE_OK) {
           		return result;
           	}

           return ids_match_protocol(packet);
     }

     if ( packet->ethernet.ether_type == 0x86DD) {
          ids_parse_result_t result =  ids_parse_ipv6(data+14, length-14, packet);

          if( result != IDS_PARSE_OK) {
          		return result;
          	}

          return ids_match_protocol(packet);
     }

     
     return IDS_PARSE_UNSUPPORTED;
 }
