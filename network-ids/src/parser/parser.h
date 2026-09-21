#ifndef IDS_PARSER_H
#define IDS_PARSER_H


#include "ids_types.h"

ids_parse_result_t ids_parse_packet(

   const uint8_t *data,
   size_t length,

   ids_packet_t *packet


);

#endif
