#ifndef IDS_IPV4_H
#define IDS_IPV4_H

#include "ids_types.h"

ids_parse_result_t ids_parse_ipv4(

  const uint8_t *data,
  size_t length,
  ids_packet_t *packet
 );

 #endif
