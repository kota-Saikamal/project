#ifndef SERIALIZE_H
#define SERIALIZE_H
#include <stddef.h>
#include <stdint.h>
#include "packet.h"

int packet_serialize(const Packet *packet,uint8_t *buffer, size_t buffer_size);

#endif
