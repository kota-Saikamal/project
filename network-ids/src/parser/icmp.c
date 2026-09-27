#include "icmp.h"

#include <arpa/inet.h>
#include <string.h>

#define ICMP_HEADER_SIZE 4


ids_parse_result_t ids_parse_icmp(
	const uint8_t *data,
	size_t length,
	ids_icmp_t *icmp
)
 {
 	if( data == NULL || icmp == NULL ) {
 		return IDS_PARSE_INVALID_ARGUMENT;
 	}

 	if( length < ICMP_HEADER_SIZE) {
 		return IDS_PARSE_TRUNCATED;
 	}

 	icmp->type = data[0];
 	icmp->code = data[1];

 	memcpy(&icmp->checksum,data+2,sizeof(icmp->checksum));
 	icmp->checksum = ntohs(icmp->checksum);

    return IDS_PARSE_OK;
 }



ids_parse_result_t ids_parse_icmpv6(
	const uint8_t *data,
	size_t length,
	ids_icmpv6_t *icmpv6
)
 {
  	if( data == NULL || icmpv6 == NULL ) {
 		return IDS_PARSE_INVALID_ARGUMENT;
 	}

 	if( length < ICMP_HEADER_SIZE) {
 		return IDS_PARSE_TRUNCATED;
 	}

    
 	icmpv6->type = data[0];
 	icmpv6->code = data[1];

 	memcpy(&icmpv6->checksum,data+2,sizeof(icmpv6->checksum));
 	icmpv6->checksum = ntohs(icmpv6->checksum);

    return IDS_PARSE_OK;
 }
  	
