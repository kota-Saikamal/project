#include "ids_types.h"
#include "ipv6.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

static void test_null_data()
{
	ids_packet_t packet;

	ids_parse_result_t  result = 
		ids_parse_ipv6(
			NULL,
			40,
			&packet
		);

	if( result != IDS_PARSE_INVALID_ARGUMENT) {
		printf("FAIL: NULL  data test\n");
		return;
	}

	printf("PASS: NULL data test\n");
}

static void test_null_output()
{
	uint8_t data[40] = {0};

	ids_parse_result_t  result = 
		ids_parse_ipv6(
			data,
			sizeof(data),
			NULL
		);

	if( result != IDS_PARSE_INVALID_ARGUMENT) {
		printf("FAIL: NULL output test\n");
		return;
	}

	printf("PASS: NULL output test\n");
}

static void test_truncated_header()
{
	ids_packet_t packet;
	uint8_t data[39] = {0};

	ids_parse_result_t  result = 
		ids_parse_ipv6(
			data,
			sizeof(data),
			&packet
		);

	if( result != IDS_PARSE_TRUNCATED) {
		printf("FAIL: truncated IPv6 header test\n");
		return;
	}

	printf("PASS: truncated IPv6 header test\n");
}

static void test_version()
{
    uint8_t data[40] = {0};
	ids_packet_t packet;
	data[0] = 0x45;

	ids_parse_result_t  result = 
		ids_parse_ipv6(
			data,
			sizeof(data),
			&packet
		);

	if( result != IDS_PARSE_MALFORMED) {
		printf("FAIL: invalid IPv6 version test\n");
		return;
	}

	printf("PASS: invalid IPv6 version test\n");
}


static void test_payload_length()
{
	uint8_t data[40] = {0};

	data[0]= 0x60;
	data[4] = 0x00;
	data[5] = 0x14;
	
	ids_packet_t packet;
    
	ids_parse_result_t  result = 
		ids_parse_ipv6(
			data,
			sizeof(data),
			&packet
		);

	if( result != IDS_PARSE_TRUNCATED) {
		printf("FAIL: payload length validation test\n");
		return;
	}

	printf("PASS: payload length validation test\n");
}

static void test_valid_ipv6()
{
	
   uint8_t data[60] = {
   // version 
   	0x60,
   	// Traffic class + flow lable
   	0x00, 0x00, 0x00,
   	// payload length = 20 
   	0x00, 0x14,
   	//next header = tcp
   	0x06,
   	// hop limit = 64
   	0x40,

   	//source IPv6 address
   	0x20,0x01,0x0d,0xb8,
   	0x00, 0x00, 0x00, 0x00,
   	0x00, 0x00, 0x00, 0x00, 
   	0x00, 0x00, 0x00, 0x01,

   	//destination ipv6 address
   	0x20, 0x01, 0x0d, 0xb8,
   	0x00, 0x00, 0x00, 0x00, 
   	0x00, 0x00, 0x00, 0x00,
   	0x00, 0x00, 0x00, 0x02,

   	// 20 byte payload
   	0xaa,0xbb,0xcc,0xdd,
   	0xee,0xff,0x11,0x22,
   	0x33,0x44,0x55,0x66,
   	0x77,0x88,0x99,0xaa,
   	0xbb,0xcc,0xdd,0xee
   	};

   	ids_packet_t packet;

   	ids_parse_result_t result = 
   		ids_parse_ipv6(
   			data,
   			sizeof(data),
   			&packet
   		);

   	if( result != IDS_PARSE_OK) {
   		printf("FAIL: valid IPv6 packet\n");
   	    return;
   	 }

   	 if(packet.source_ip.is_ipv6 != true) {
   	 	printf("FAIL: source IP not marked as IPv6\n");
   	 	return;
   	 }

   	 if(packet.destination_ip.is_ipv6 != true) {
   	 	printf("FAIL: destination IP not marked as IPv6\n");
   	 	return;
   	 }

   	 uint8_t expected_source[16] = {
    	0x20,0x01,0x0d,0xb8,
    	0x00, 0x00, 0x00, 0x00,
    	0x00, 0x00, 0x00, 0x00, 
    	0x00, 0x00, 0x00, 0x01
	 };

   	 uint8_t expected_destination[16] = {
    	0x20,0x01,0x0d,0xb8,
    	0x00, 0x00, 0x00, 0x00,
    	0x00, 0x00, 0x00, 0x00, 
    	0x00, 0x00, 0x00, 0x02
	 };

  	 if( memcmp(
  	 		packet.source_ip.address,
  	 		expected_source,
  	 		16
  	 	) != 0) {
  	 	printf("FAIL: incorrect source IPv6 address\n");
  	 	return;
  	 }

  	 if( memcmp(
  	 		packet.destination_ip.address,
  	 		expected_destination,
  	 		16
  	 	) != 0) {
  	 	printf("FAIL: incorrect destination IPv6 address\n");
  	 	return;
  	 }

   	if( packet.protocol != IDS_PROTOCOL_TCP) {
   		printf("FAIL: incorrect IPv6 protocol\n");
   	    return;
   	 }

   	if( packet.payload != data + 40) {
   		printf("FAIL: incorrect payload pointer\n");
   	    return;
   	 }

   	if( packet.payload_length != 20) {
   		printf("FAIL: incorrect payload length\n");
   	    return;
   	 }

   	if( packet.packet_length != 60) {
   		printf("FAIL: incorrect packet length\n");
   	    return;
   	 }

     printf("PASS: valid IPv6 packet\n");
}

int main()
{
	printf("Running IPv6 parser tests...\n\n");

	test_null_data();
	test_null_output();
	test_truncated_header();
	test_version();
	test_payload_length();
	test_valid_ipv6();

	printf("\nIPv6 parser tests complete.\n");
	return 0;
}
