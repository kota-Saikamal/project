#ifndef INPUT_H
#define INPUT_H
#include <stddef.h> 
#include "packet.h"


int input_get_integer(const char *prompt);

void input_get_string(const char *prompt,char *buffer, size_t size);

void input_get_flags(Packet *packet);

PacketType input_get_type();

uint8_t input_get_version();

uint32_t input_get_sequence();



#endif
