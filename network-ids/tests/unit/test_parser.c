#include "parser.h"
#include "ids_types.h"

#include <stdio.h>
#include <stdint.h>


static void test_null_data()
{
	ids_packet_t packet;

	ids_parse_result_t result =
		ids_parse_packet(
			NULL,
			14,
			&packet
		);

	if( result != IDS_PARSE_INVALID_ARGUMENT) {
		printf("FAIL: NULL data test\n");
		return;
	}

	printf("PASS: NULL data test\n");
}

static void test_null_output()
{
	uint8_t data[14] = {0};

	ids_parse_result_t result =
		ids_parse_packet(
			data,
			sizeof(data),
			NULL
		);

	if( result != IDS_PARSE_INVALID_ARGUMENT) {
		printf("FAIL: NULL output  test\n");
		return;
	}

	printf("PASS: NULL output test\n");
}

static void test_empty_packet()
{
   uint8_t data[1] = {0};
   
	ids_packet_t packet;

	ids_parse_result_t result =
		ids_parse_packet(
			data,
			0,
			&packet
		);

	if( result != IDS_PARSE_TRUNCATED) {
		printf("FAIL: empty packet test\n");
		return;
	}

	printf("PASS: empty packet test\n");
}

static void test_truncated_ethernet()
{
   uint8_t data[13] = {0};
   
	ids_packet_t packet;

	ids_parse_result_t result =
		ids_parse_packet(
			data,
			sizeof(data),
			&packet
		);

	if( result != IDS_PARSE_TRUNCATED) {
		printf("FAIL: truncated Ethernet test\n");
		return;
	}

	printf("PASS: truncated Ethernet test\n");
}

static void test_unsupported_ethertype()
{
	uint8_t data[14] = {
		0x11, 0x22, 0x33, 0x44, 0x55, 0x66,
		0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,

		0x08, 0x06
	};

	ids_packet_t packet;

	ids_parse_result_t result =
		ids_parse_packet(
			data,
			sizeof(data),
			&packet
		);

	if( result != IDS_PARSE_UNSUPPORTED) {
		printf("FAIL: unsupported EtherType test\n");
		return;
	}

	printf("PASS: unsupported EtherType test\n");
}


static void test_ipv4_tcp()
{
	uint8_t data[54] = {
	0x11, 0x22, 0x33, 0x44, 0x55, 0x66,
	0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
	0x08, 0x00,

	0x45,
	0x00,
	0x00,0x28,
	0x00, 0x01,
	0x00, 0x00,
	0x40,
	0x06,
	0x00, 0x00,

	192,168,1,10,
	192,168,1,20,

	0x30, 0x39,
	0x01, 0xbb,
	0x11, 0x22, 0x33, 0x44,
	0x55, 0x66, 0x77, 0x88,
	0x50, 
	0x02,
	0x10, 0x00, 
	0x00, 0x00,
	0x00, 0x00
  };

  	ids_packet_t packet;

	ids_parse_result_t result =
		ids_parse_packet(
			data,
			sizeof(data),
			&packet
		);

	if( result != IDS_PARSE_OK) {
		printf("FAIL: IPv4 TCP routing port\n");
		return;
	}

	if( packet.protocol != IDS_PROTOCOL_TCP) {
		printf("FAIL: IPv4 TCP protocol port\n");
		return;
	}

	if( packet.transport.tcp.source_port != 12345) {
		printf("FAIL: IPv4 TCP source  port\n");
		return;
	}

	if( packet.transport.tcp.destination_port != 443) {
		printf("FAIL: IPv4 TCP destination port\n");
		return;
	}	
  
    printf("PASS: IPv4 TCP routing test\n");
 }

static void test_ipv4_udp()
{
	uint8_t data[42] = {

	0x11, 0x22, 0x33, 0x44, 0x55, 0x66,
	0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
	0x08, 0x00,

	0x45,
	0x00,
	0x00,0x1c,
	0x00, 0x01,
	0x00, 0x00,
	0x40,
	0x11,
	0x00, 0x00,

	192,168,1,10,
	192,168,1,20,

	0x30, 0x39,
	0x00, 0X35, 
	0x00, 0x08,
	0x00, 0x00
  };

  	ids_packet_t packet;

	ids_parse_result_t result =
		ids_parse_packet(
			data,
			sizeof(data),
			&packet
		);

	if( result != IDS_PARSE_OK) {
		printf("FAIL: IPv4 UDP routing port\n");
		return;
	}

	if( packet.protocol != IDS_PROTOCOL_UDP) {
		printf("FAIL: IPv4 UDP protocol port\n");
		return;
	}

	if( packet.transport.udp.source_port != 12345) {
		printf("FAIL: IPv4 UDP source  port\n");
		return;
	}

	if( packet.transport.udp.destination_port != 53) {
		printf("FAIL: IPv4 UDP destination port\n");
		return;
	}	
  
    printf("PASS: IPv4 UDP routing test\n");
 }
 
static void test_ipv4_unknown_protocol()
{
	uint8_t data[34] = {

	0x11, 0x22, 0x33, 0x44, 0x55, 0x66,
	0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
	0x08, 0x00,

	0x45,
	0x00,
	0x00,0x14,
	0x00, 0x01,
	0x00, 0x00,
	0x40,
	0x99,
	0x00, 0x00,

	192,168,1,10,
	192,168,1,20,
  };

  	ids_packet_t packet;

	ids_parse_result_t result =
		ids_parse_packet(
			data,
			sizeof(data),
			&packet
		);

	if( result != IDS_PARSE_UNSUPPORTED) {
		printf("FAIL: IPv4 unkown protocol port\n");
		return;
	}

    printf("PASS: IPv4 unkown protocol test\n");
}


static void test_ipv6_tcp()
{
	uint8_t data[74] = {

	0x11, 0x22, 0x33, 0x44, 0x55, 0x66,
	0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
	0x86, 0xdd,

	0x60,
	0x00,0x00,0x00,
	0x00, 0x014,
	0x06,
	0x40,
   //source IPv6
   0x20, 0x01, 0x0d, 0xb8,
   0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x01,

   //desstination IPv6
   0x20, 0x01, 0x0d, 0xb8,
   0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x02,
   
	0x30, 0x39,
	0x01, 0xbb,
	0x11, 0x22, 0x33, 0x44,
	0x55, 0x66, 0x77, 0x88,
	0x50, 
	0x02,
	0x10, 0x00, 
	0x00, 0x00,
	0x00, 0x00
  };

  	ids_packet_t packet;

	ids_parse_result_t result =
		ids_parse_packet(
			data,
			sizeof(data),
			&packet
		);

	if( result != IDS_PARSE_OK) {
		printf("FAIL: IPv6 TCP routing port\n");
		return;
	}

	if( packet.protocol != IDS_PROTOCOL_TCP) {
		printf("FAIL: IPv6 TCP protocol port\n");
		return;
	}

	if( packet.transport.tcp.source_port != 12345) {
		printf("FAIL: IPv6 TCP source  port\n");
		return;
	}

	if( packet.transport.tcp.destination_port != 443) {
		printf("FAIL: IPv6 TCP destination port\n");
		return;
	}	
  
    printf("PASS: IPv6 TCP routing test\n");
 }

static void test_ipv6_udp()
{
	uint8_t data[62] = {

	0x11, 0x22, 0x33, 0x44, 0x55, 0x66,
	0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
	0x86, 0xdd,

	0x60,
	0x00,0x00,0x00,
	0x00, 0x08,
	0x11,
	0x40,

   //source IPv6
   0x20, 0x01, 0x0d, 0xb8,
   0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x01,

   //desstination IPv6
   0x20, 0x01, 0x0d, 0xb8,
   0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x02,
   
	0x30, 0x39,
	0x00, 0X35, 
	0x00, 0x08,
	0x00, 0x00
  };

  	ids_packet_t packet;

	ids_parse_result_t result =
		ids_parse_packet(
			data,
			sizeof(data),
			&packet
		);

	if( result != IDS_PARSE_OK) {
		printf("FAIL: IPv6 UDP routing port\n");
		return;
	}

	if( packet.protocol != IDS_PROTOCOL_UDP) {
		printf("FAIL: IPv6 UDP protocol port\n");
		return;
	}

	if( packet.transport.udp.source_port != 12345) {
		printf("FAIL: IPv6 UDP source  port\n");
		return;
	}

	if( packet.transport.udp.destination_port != 53) {
		printf("FAIL: IPv6 UDP destination port\n");
		return;
	}	
  
    printf("PASS: IPv6 UDP routing test\n");
 }

static void test_ipv6_unknown_protocol()
{
	uint8_t data[54] = {

	0x11, 0x22, 0x33, 0x44, 0x55, 0x66,
	0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
	0x86, 0xdd,

	0x60,
	0x00,0x00,0x00,
	0x00, 0x00,
	0x99,
	0x40,

    //source IPv6
   0x20, 0x01, 0x0d, 0xb8,
   0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x01,

   //desstination IPv6
   0x20, 0x01, 0x0d, 0xb8,
   0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x02,
   
	
  };

  	ids_packet_t packet;

	ids_parse_result_t result =
		ids_parse_packet(
			data,
			sizeof(data),
			&packet
		);

	if( result != IDS_PARSE_UNSUPPORTED) {
		printf("FAIL: IPv6 unkown protocol port\n");
		return;
	}

    printf("PASS: IPv6 unkown protocol test\n");
}


int main()
{
	printf("Running parser tests...\n\n");

	test_null_data();
	test_null_output();
	test_empty_packet();
	test_truncated_ethernet();

	test_unsupported_ethertype();

	test_ipv4_tcp();
	test_ipv4_udp();
	test_ipv4_unknown_protocol();

	test_ipv6_tcp();
	test_ipv6_udp();
    test_ipv6_unknown_protocol();
    
	printf("\nParser tests complete.\n");

	return 0;

}
