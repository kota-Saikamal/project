#include "tcp.h"
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>

#define TCP_MIN_HEADER_SIZE 20

ids_parse_result_t ids_parse_tcp (
	const uint8_t *data,
	size_t length,
	ids_tcp_t *tcp
)
 {

    if( data == NULL || tcp == NULL) {
       return IDS_PARSE_INVALID_ARGUMENT;
    }

    if( length < TCP_MIN_HEADER_SIZE) {
       return IDS_PARSE_TRUNCATED;
    }

    memcpy (
    	&tcp->source_port,
    	data,
        sizeof(tcp->source_port)
    );
	tcp->source_port = ntohs(tcp->source_port);
    
    memcpy (
        &tcp->destination_port,
        data+2,
        sizeof(tcp->destination_port)
    );
    tcp->destination_port = ntohs(tcp->destination_port);

    memcpy (
    	&tcp->sequence_number,
    	data + 4,
    	sizeof(tcp -> sequence_number)
    );
    tcp -> sequence_number = ntohl(tcp -> sequence_number);

    memcpy (
    	&tcp->acknowledgment_number,
    	data + 8,
    	sizeof(tcp -> acknowledgment_number)
    );
    tcp->acknowledgment_number = ntohl(tcp->acknowledgment_number);

    tcp->data_offset = data[12] >> 4;

    if( tcp->data_offset < 5)
    	return IDS_PARSE_MALFORMED;

    size_t header_length = tcp->data_offset * 4;

    if ( header_length > length ) 
    	return IDS_PARSE_TRUNCATED;

    tcp->flags = data[13];
	
	memcpy (
		&tcp->window_size,
		data + 14,
		sizeof(tcp->window_size)
	); 
	tcp->window_size = ntohs(tcp->window_size);     

   printf("TCP source port: %u\n",tcp->source_port);
   printf("TCP destination port: %u\n",tcp->destination_port);
   printf("TCP sequence: %u\n",tcp->sequence_number);
   printf("TCP flags: 0x%02x\n",tcp->flags);
   
   return IDS_PARSE_OK;
 }
