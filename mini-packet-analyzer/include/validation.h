#ifndef VALIDATION_H
#define VALIDATION_H
#include "packet.h"
#include "error.h"


PacketError packet_validate(const Packet *packet);
int validate_extension(const char *filename);

#endif
