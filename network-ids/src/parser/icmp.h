#ifndef IDS_ICMP_H
#define IDS_ICMP_H

#include "ids_types.h"


ids_parse_result_t ids_parse_icmp(

  const uint8_t *data,
  size_t length,
  ids_icmp_t *icmp
 );


 #endif
