#ifndef PARSER_H
#define PARSER_H
#include "packet.h"
#include <stddef.h>

int packet_deserialize(const uint8_t *buffer,size_t buffer_size,Packet *packet);

void parse_packet();
#endif
