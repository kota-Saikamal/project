#ifndef IDS_ETHERNET_H
#define IDS_ETHERNET_H

#include "ids_types.h"

ids_parse_result_t ids_parse_ethernet(
     const uint8_t *data,
     size_t length,
     ids_ethernet_t *ethernet
 );
 
#endif

