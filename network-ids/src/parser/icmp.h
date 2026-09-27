#ifndef IDS_ICMP_H
#define IDS_ICMP_H

#include <stddef.h>
#include <stdint.h>

#include "ids_types.h"


ids_parse_result_t ids_parse_icmp(

  const uint8_t *data,
  size_t length,
  ids_icmp_t *icmp
 );

ids_parse_result_t ids_parse_icmpv6(

  const uint8_t *data,
  size_t length,
  ids_icmpv6_t *icmpv6
 );


 #endif
