#ifndef IDS_UDP_H
#define IDS_UDP_H

#include "ids_types.h"


ids_parse_result_t ids_parse_udp(

  const uint8_t *data,
  size_t length,

  ids_udp_t *udp

);

#endif
