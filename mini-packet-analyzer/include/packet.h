#ifndef PACKET_H
#define PACKET_H
#include<stdint.h>
#define FLAG_ACK (1u << 0)
#define FLAG_SYN (1u << 1)
#define FLAG_ERROR (1u << 2)
#define FLAG_PRIORITY (1u << 3)
#define MAX_PAYLOAD_SIZE 1024

typedef enum {
 PACKET_DATA=1,
 PACKET_ACK=2,
 PACKET_ERROR=3,
}PacketType;



typedef struct {
  uint8_t version;
  PacketType  type;
  uint16_t flags;
  uint16_t length;
  uint32_t sequence;
  char payload[MAX_PAYLOAD_SIZE];
}Packet;


void packet_init(Packet *packet);

void packet_display(const Packet *packet);

int packet_set_payload(Packet *packet,const char *new_payload);

void packet_set_flag(Packet *packet,uint16_t flag);

void packet_clear_flag(Packet *packet,uint16_t flag);

int packet_has_flag(const Packet *packet,uint16_t flag);

void packet_build(Packet *packet,uint8_t *buffer,const char *filename);

void create_packet();

#endif
