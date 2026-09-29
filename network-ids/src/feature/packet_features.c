#include "feature.h"
#include <string.h>

void ids_extract_packet_features(
	const ids_packet_t *packet,
	ids_packet_features_t *features
)
	{
		if( packet == NULL || features == NULL) 
		{
			return;
		}

		features->packet_length = packet->packet_length;
		features->payload_length = packet->payload_length;
		features->protocol = packet->protocol;
		features->malformed = packet->malformed;

	}



	
