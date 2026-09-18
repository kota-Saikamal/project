#ifndef STORAGE_H
#define STORAGE_H
#include "packet.h"
#include <stddef.h>

void packet_save(const uint8_t *buffer,size_t size,const char *filename);

int  packet_upload( uint8_t *buffer,size_t size,const char *filename);

#endif
