#include "parser.h"

#include "ethernet.h"

ids_parse_result_t ids_parse_packet(

    const uint8_t *data,
    size_t length,
    ids_packet_t *packet
 )
 {

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

     return IDS_PARSE_OK;
 }
