#include "ethernet.h"
#include <arpa/inet.h>
#include <string.h>

#define ETHERNET_HEADER_SIZE 14

ids_parse_result_t ids_parse_ethernet(
    const uint8_t *data,
    size_t length,
    ids_ethernet_t *ethernet

)
 {
     if( data == NULL || ethernet == NULL) {
          return IDS_PARSE_INVALID_ARGUMENT;
      }


      if( length < ETHERNET_HEADER_SIZE) {
          return IDS_PARSE_TRUNCATED;
      }

      memcpy(ethernet->destination,data, IDS_MAC_ADDRESS_LEN);

      memcpy(
          ethernet->source,
          data+IDS_MAC_ADDRESS_LEN,
          IDS_MAC_ADDRESS_LEN
      );

      memcpy(
          &ethernet->ether_type,
          data + 12,
          sizeof(ethernet->ether_type)
      );

      ethernet->ether_type = ntohs(ethernet->ether_type);

      return IDS_PARSE_OK;
}


