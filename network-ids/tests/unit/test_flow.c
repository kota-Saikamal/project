#include "flow.h"
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

        packet.destination_ip.address[0] = 10;
        packet.destination_ip.address[1] = 0;
        packet.destination_ip.address[2] = 0;
        packet.destination_ip.address[3] = destination_last;

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


   void test_flow_key_equal()
   	{
   		printf("\nTest: flow key equal\n");

   		ids_packet_t packet_a = 
   			create_tcp_packet(
   				10,
   				20,
   				50000,
   				80,
   				0x02,
   				100,
   				1000
   			);

   		ids_packet_t packet_b = 
   			create_tcp_packet(
   				10,
   				20,
   				50000,
   				80,
   				0x10,
   				100,
   				1100
   			);

        ids_flow_key_t key_a = 
        	ids_flow_key_from_packet(&packet_a);

        ids_flow_key_t key_b = 
        	ids_flow_key_from_packet(&packet_b);

		check(
			ids_flow_key_equal(&key_a,&key_b),
			"same direction should be equal"
		);

        
   		ids_packet_t packet_reverse = 
   			create_tcp_packet(
   				20,
   				10,
   				80,
   				50000,
   				0x10,
   				100,
   				1200
   			);

        ids_flow_key_t reverse_key = 
        	ids_flow_key_from_packet(&packet_reverse);

		check(
			ids_flow_key_equal(&key_a,&reverse_key),
			"reverse direction should be equal"
		);

		ids_flow_key_t different_protocol = key_a;

		different_protocol.protocol = IDS_PROTOCOL_UDP;

		check(
			!ids_flow_key_equal(&key_a,&different_protocol),
			"different protocol should not be equal"
		);		

		different_protocol.destination_port = 443;

		check(
			!ids_flow_key_equal(&key_a,&different_protocol),
			"different port should not be equal"
		);		

	    printf("PASS: flow key equal\n");
  }


  
 void test_flow_init()
 {
 	printf("\nTest: flow initialization\n");

    ids_packet_t packet = 
   			create_tcp_packet(
   				10,
   				20,
   				50000,
   				80,
   				0x02,
   				100,
   				1000
   			);

	ids_flow_t flow;

	ids_flow_init(&flow, &packet);

		check(
			flow.first_seen_ns == 1000,
			"first_seen_ns should equal first packet timestamp"
		);	

		check(
			flow.last_seen_ns == 1000,
			"last_seen_ns should equal first packet timestamp"
		);

		check(
			flow.packets_forward == 1,
			"initial forward packet count should be 1"
		);

		check(
			flow.bytes_forward  == 100,
			"initial forward bytes count should be 100"
		);

		check(
			flow.syn_count == 1,
			"SYN count should be 1"
		);

		check(
			flow.key.source_port == 50000,
			"flow source port should be 50000"
		);

		check(
			flow.key.destination_port == 80,
			"flow destination port should be 80"
		);

	    printf("PASS: flow initialization\n");
}

void test_flow_update()

{
	printf("\nTest: flow update\n");

    ids_packet_t first_packet = 
   			create_tcp_packet(
   				10,
   				20,
   				50000,
   				80,
   				0x02,
   				100,
   				1000
   			);

	ids_flow_t flow;

	ids_flow_init(&flow, &first_packet);	

    ids_packet_t forward_packet = 
   			create_tcp_packet(
   				10,
   				20,
   				50000,
   				80,
   				0x10,
   				200,
   				2000
   			);

	ids_flow_update(&flow, &forward_packet);

	
		check(
			flow.last_seen_ns == 2000,
			"last_seen_ns should update"
		);

		check(
			flow.packets_forward == 2,
			"forward packet count should become 2"
		);

		check(
			flow.bytes_forward == 300,
			"forward bytes  should become 300"
		);

		check(
			flow.ack_count == 1,
			"ACK count should be 1"
		);

    ids_packet_t reverse_packet = 
   			create_tcp_packet(
   				20,
   				10,
   				80,
   				50000,
   				0x10,
   				150,
   				3000
   			);

	ids_flow_update(&flow, &reverse_packet);

	
		check(
			flow.last_seen_ns == 3000,
			"last_seen_ns should update"
		);

		check(
			flow.packets_reverse == 1,
			"reverse packet count should become 1"
		);

		check(
			flow.bytes_reverse == 150,
			"reverse bytes  should become 150"
		);

		check(
			flow.ack_count == 2,
			"ACK count should be 2"
		);

	printf("PASS: flow update\n");
}

int main()
{
	test_flow_key_from_packet();
	test_flow_key_equal();
	test_flow_init();
	test_flow_update();

	printf("\n============================================\n");
	printf("Tests passed: %d\n", tests_passed);
	printf("Tests failed: %d\n", tests_failed);
	printf("\n============================================\n");

	return 0;
}
