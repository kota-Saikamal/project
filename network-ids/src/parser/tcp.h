#ifndef IDS_TCP_H
#define IDS_TCP_H

#include "ids_types.h"


ids_parse_result_t ids_parse_tcp(

  const uint8_t *data,
  size_t length,
  ids_tcp_t *tcp
);


#endif

  
