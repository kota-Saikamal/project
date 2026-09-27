#inlucde "flow.h"
#include "ids_types.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

static int tests_passed =0;
static int tests_failed =0;

static void check(int condition, const char *message)
{
	if(condition) {
		tests_passed++;
	}else {
		tests_failed++;
		printf("FAIL: %s\n",message);
	
	}
}

static ids_packet_t create_tcp_packet(
	uint8_t source_last,
	uint8_t destination_last,
	uint16_t source_port,
	uint16_t destination_port,
	uint8_t flags,
	uint32_t packet_length,
	uint64_t timestamp
)
 	{
 		ids_packet_t packet = {0};

 		packet.source_ip.is_ipv6 = false;
		packet.destination_ip.is_ipv6 = false;

        packet.source_ip.address[0] = 192;
        packet.source_ip.address[1] = 168;
        packet.source_ip.address[2] = 1;
        packet.source_ip.address[3] = source_last;

        packet.source_ip.address[0] = 10;
        packet.source_ip.address[1] = 0;
        packet.source_ip.address[2] = 0;
        packet.source_ip.address[3] = destination_last;

        packet.protocol = IDS_PROTOCOL_TCP;

        packet.transport.tcp.source_port = source_port;
        packet.transport.tcp.destination_port = destination_port;
        packet.transport.tcp.flags = flags;

        packet.packet_length = packet_length;
        packet.timestamp_ns = timestamp;


        return packet;
   }


   void test_flow_key_from_packet()
   {
   		printf("\nTest: flow key from packet\n");

   		ids_packet_t packet = create_tcp_packet(
   									10,
   									20,
   									50000,
   									80,
   									0x02,
   									100,
   									1000
   								);
   		ids_flow_key_t key = 
   			ids_flow_key_from_packet(&packet);

   		check(
   			key.protocol == IDS_PROTOCOL_TCP,
   			"protocol should be TCP"
   		);

   		check(
   			key.source_port == 50000,
   			"source port should be 50000"
   		);
   		
   		check(
   			key.destination_port == 80,
   			"destination port should be 80"
   		);   		

   		check(
   			key.source_ip.address[3] == 10,
   			"source IP should be 192.168.1.10"
   		);

   		check(
   			key.destination_ip.address[3] == 20,
   			"destination IP should be 10.0.0.20"
   		);

        printf("PASS: flow key from packet\n");
   }
