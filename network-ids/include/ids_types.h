#ifndef IDS_TYPES_H
#define IDS_TYPES_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define IDS_MAC_ADDRESS_LEN 6
#define IDS_IPV6_ADDRESS_LEN 16

#define IDS_DESCRIPTION_LEN 256

typedef enum {

  IDS_PROTOCOL_UNKOWN=0,
  IDS_PROTOCOL_TCP,
  IDS_PROTOCOL_UDP,
  IDS_PROTOCOL_ICMP,
  IDS_PROTOCOL_ICMPV6

}ids_protocol_t;


typedef struct {
  uint8_t address[IDS_IPV6_ADDRESS_LEN];
  bool is_ipv6;
}ids_ip_address_t;

typedef struct {
  uint8_t source[IDS_MAC_ADDRESS_LEN];
  uint8_t destination[IDS_MAC_ADDRESS_LEN];
  uint16_t ether_type;
}ids_ethernet_t;


typedef struct {
  uint16_t source_port;
  uint16_t destination_port;
  uint32_t sequence_number;
  uint32_t acknowledgment_number;
  uint8_t data_offset;
  uint8_t flags;

  uint16_t window_size;
}ids_tcp_t;

typedef struct {
  uint16_t source_port;
  uint16_t destination_port;
  uint16_t length;
}ids_udp_t;

typedef struct {
 uint8_t type;
 uint8_t code;
 uint16_t checksum;
}ids_icmp_t;


typedef struct {
  uint8_t type;
  uint8_t code;
  uint16_t checksum;
}ids_icmpv6_t;

typedef struct {
 ids_ethernet_t ethernet;
 ids_ip_address_t source_ip;
 ids_ip_address_t destination_ip;
 ids_protocol_t protocol;

 union {
  ids_tcp_t tcp;
  ids_udp_t udp;
  ids_icmp_t icmp;
  ids_icmpv6_t icmpv6;
 }transport;

 uint32_t packet_length;
 
 const uint8_t *payload;
 size_t payload_length;

 uint64_t timestamp_ns;

 bool malformed;

}ids_packet_t;


typedef struct {
 ids_ip_address_t source_ip;
 ids_ip_address_t destination_ip;
 uint16_t source_port;
 uint16_t destination_port;
 ids_protocol_t protocol;

}ids_flow_key_t;


typedef struct {
 ids_flow_key_t key;
 uint64_t first_seen_ns;
 uint64_t last_seen_ns;
 uint64_t packets_forward;
 uint64_t packets_reverse;
 uint64_t bytes_forward;
 uint64_t bytes_reverse;
 uint64_t syn_count;
 uint64_t ack_count;
 uint64_t rst_count;
 uint64_t fin_count;

 bool established;
}ids_flow_t;


typedef struct {
 uint64_t packet_count;
 uint64_t byte_count;
 uint64_t packets_forward;
 uint64_t packets_reverse;
 uint64_t bytes_forward;
 uint64_t bytes_reverse;

 uint64_t syn_count;
 uint64_t ack_count;
 uint64_t rst_count;

 uint64_t unique_destination_ports;
 uint64_t unique_destinationn_hosts;

 double packets_per_second;
 double bytes_per_second;

 double connection_rate;
 
}ids_flow_features_t;


typedef enum {
 IDS_DETECTION_NONE=0,
 IDS_DETECTION_PORT_SCAN,
 IDS_DETECTION_SYN_SCAN,
 IDS_DETECTION_ICMP_SWEEP,
 IDS_DETECTIN_SYN_FLOOD,
 IDS_DETECTION_UDP_FLOOD,
 IDS_DETECTION_BRUTE_FORCE,
 IDS_DETECTION_ANOMALY

} ids_detection_type_t;


typedef struct {

 ids_detection_type_t type;
 int severity;
 uint64_t timestamp_ns;
 ids_ip_address_t source_ip;
 ids_ip_address_t destination_ip;
 ids_protocol_t protocol;

 uint16_t source_port;
 uint16_t destination_port;

 double confidence;

 char description[IDS_DESCRIPTION_LEN];

}ids_detection_event_t;

typedef enum {

  IDS_PARSE_OK=0,
  IDS_PARSE_INVALID_ARGUMENT,
  IDS_PARSE_TRUNCATED,
  IDS_PARSE_MALFORMED,
  IDS_PARSE_UNSUPPORTED
 } ids_parse_result_t;


 typedef enum {
   IDS_SUCESS =0,
   IDS_ERROR= -1
 } ids_status_t;

 
#endif
