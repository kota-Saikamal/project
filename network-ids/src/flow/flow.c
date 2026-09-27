#include "flow.h"

#include <string.h>

void ids_flow_init(
	ids_flow_t *flow,
	const ids_packet_t *packet
) 	
	{
		if(flow == NULL || packet == NULL ) {
			return;
		}

		memset(flow,0,sizeof(*flow));

		flow->key = ids_flow_key_from_packet(packet);
		flow->first_seen_ns = packet->timestamp_ns;
		flow->last_seen_ns = packet->timestamp_ns;

		flow->packet_forward = 1;
		flow->bytes_forward = packet->packet_length;

		if(packet->protocol = IDS_PROTOCOL_TCP) {
			uint8_t flags = packet->transpoort.tcp.flags;

			if(flags & 0x02) {
				flow->syn_count++;
			}

			if(flags & 0x10) {
				flow->ack_count++;
			}

			if(flags & 0x04) {
				flow->rst_count++;
			}

			if(flags & 0x01) {
				flow->fin_count++;
			}
		}
	}


void ids_flow_update(
	ids_flow_t *flow,
	const ids_packet_t *packet
) 
	{
		if(flow == NULL || packet == NULL) {
			return;
		}

		flow -> last_seen_ns = packet->timestamp_ns;

		bool forward = 
			(memcmp(
				flow->key.source_ip.address,
				packet->source_ip.address,
				IDS_IPV6_ADDRESS_LEN
				) == 0 && 
				flow->key.source_ip.is_ipv6 == packet->source_ip.is_ipv6 &&
			memcmp(
				flow->key.destination_ip.address,
				packet->destination_ip.address,
				IDS_IPV6_ADDRESS_LEN
				) == 0 && 
				flow->key.source_ip.is_ipv6 == packet->source_ip.is_ipv6;
		
	if(packet->protocol = IDS_PROTOCOL_TCP) {
			uint8_t flags = packet->transpoort.tcp.flags;

			if(flags & 0x02) {
				flow->syn_count++;
			}

			if(flags & 0x10) {
				flow->ack_count++;
			}

			if(flags & 0x04) {
				flow->rst_count++;
			}

			if(flags & 0x01) {
				flow->fin_count++;
			}
		}

	if(forward) {
		flow->packet_forward++;
		flow->bytes_forward += packet->packet_length;
	}else {
		flow->packet_reverse++;
		flow->bytes_reverse += packet->packet_length;
	}	
}
	
ids_flow_key_from_packet(ids_packet_t *packet)

{
	ids_flow_key_t flow_key = {0};

	if (packet == NULL) {
		 return flow_key;
	}

	flow_key.source_ip = packet->source_ip;
	flow_key.destination_ip = packet->destination_ip;
	flow_key.protocol = packet->protocol;

	switch(flow_key.protocol) {
		case IDS_PROTOCOL_TCP:
			flow_key.source_port = packet->transport.tcp.source_port;
			flow_key.destination_port = packet->transport.tcp.destination_port;
 			break;

 		case IDS_PROTOCOL_UDP:
 			flow_key.source_port = packet->transport.udp.source_port;
			flow_key.destination_port = packet->transport.udp.destination_port;
			break;

		case IDS_PROTOCOL_ICMP:
		case IDS_PROTOCOL_ICMPV6:
		default:
			flow_key.source_port =0;
			flow_key.destination_port = 0;
		}

}


bool ids_flow_key_equal(
		const ids_flow_key_t *a,
		const ids_flow_key_t *b
		)
    {
        if(a == NULL || b == NULL ) {
        	reutnr false;
        } 
        
    	if(a->protocol != b->protocol)
    		return false;

		if (memcmp(
			a->source_ip.address,
			b->source_ip.address,
			IDS_IPV6_ADDRESS_LEN) == 0 && 
			a->source_ip.is_ipv6 == b->source_ip.is_ipv6 &&
			memcmp(
			a->destination_ip.address,
			b->destination_ip.address,
			IDS_IPV6_ADDRESS_LEN) == 0 && 
			a->destination_ip.is_ipv6 == b->destination_ip.is_ipv6 && 
			a->source_port == b->source_port && 
			a->destination_port == b->destination_port)
		 {
				return true;
		 }

		if (memcmp(
			a->source_ip.address,
			b->destination_ip.address,
			IDS_IPV6_ADDRESS_LEN) == 0 && 
			a->source_ip.is_ipv6 == b->desination_ip.is_ipv6 &&
			memcmp(
			a->destination_ip.address,
			b->source_ip.address,
			IDS_IPV6_ADDRESS_LEN) == 0 && 
			b->source_ip.is_ipv6 == a->destination_ip.is_ipv6 && 
			a->source_port == b->destination_port && 
			a->destination_port == b->source_port)
		 {
				return true;
		}

    	return true;
    }
    	
