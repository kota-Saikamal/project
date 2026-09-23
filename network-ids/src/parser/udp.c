#include "udp.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

#define UDP_HEADER_SIZE 8

ids_parse_result_t ids_parse_udp(

	const uint8_t *data,
	size_t length,

	ids_udp_t *udp
)
 {

  if( data == NULL || udp == NULL ) 
  { 
	 return IDS_PARSE_INVALID_ARGUMENT;
  }

  if( length < UDP_HEADER_SIZE) 
  { 
  	 return IDS_PARSE_TRUNCATED;
  }

  memcpy(
  	&udp->source_port,
  	data,
  	sizeof(udp->source_port)
  );
  udp->source_port = ntohs(udp->source_port);

  memcpy(
  	&udp->destination_port,
  	data+2,
  	sizeof(udp->destination_port)
  );
  udp->destination_port = ntohs(udp->destination_port);

  memcpy(
  	&udp->length,
  	data+4,
  	sizeof(udp->length)
  );
  udp->length = ntohs(udp->length);

  if(udp -> length < UDP_HEADER_SIZE) 
     return IDS_PARSE_MALFORMED;

  if( udp -> length > length ) {
     return IDS_PARSE_TRUNCATED;
  }

  printf("UDP source port: %u\n",udp->source_port);
  printf("UDP destination port: %u\n",udp->destination_port);
  printf("UDP length port: %u\n",udp->length);
  
  return IDS_PARSE_OK;

}

