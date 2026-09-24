#include "ids_types.h"
#include "ipv4.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>


static void test_null_data() 
{
	ids_packet_t packet;

	ids_parse_result_t result = ids_parse_ipv4(
									NULL,
									40,
									&packet
								);

	if(result != IDS_PARSE_INVALID_ARGUMENT) {
	     printf("FAIL: NULL data test\n");
	     return;
	 }

	 printf("PASS: NULL data test\n");
	 	 
}

static void test_null_output() 
{
	uint8_t data[20] = {0};
    
	ids_parse_result_t result = ids_parse_ipv4(
									data,
								    sizeof(data),
									NULL
								);

	if(result != IDS_PARSE_INVALID_ARGUMENT) {
	     printf("FAIL: NULL output test\n");
	     return;
	 }

	 printf("PASS: NULL output test\n");
	 	 
}
    
static void test_truncated_header() 
{
 	uint8_t data[19] = {0};
    ids_packet_t packet;
 	
 	ids_parse_result_t result = ids_parse_ipv4(
 									data,
 									10,
 									&packet
 								);


    if( result != IDS_PARSE_TRUNCATED) {
    	printf("FAIL: truncated IPv4 header test\n");
    	return;
    }

    printf("PASS: truncated IPv4 header test\n");
}


    

static void test_valid_ipv4()
{
	uint8_t data[40] = {
	0x45,
	0x00,
	0x00, 0x28,
	0x12, 0x34,
	0x00, 0x00,
	0x40,
	0x06,
	0x00, 0x00,
	192,168,1,10,
	192,168,1,20,

	//20-byte payload
	0xaa, 0xbb, 0xcc, 0xdd,
	0xee, 0xff, 0x11, 0x22,
	0x33, 0x44, 0x55, 0x66,
	0x77, 0x88, 0x99, 0xaa,
	0xbb, 0xcc, 0xdd, 0xee
   };


   ids_packet_t packet;

   ids_parse_result_t result =  ids_parse_ipv4(
   							data,
   							sizeof(data),
   							&packet
   						);

       if(result != IDS_PARSE_OK) {
       		printf("FAIL; valid IPv4 packet\n");
       		return;
       	}

       	if(packet.source_ip.is_ipv6 != false) {
       		printf("FAIL: source IP marked as IPv6\n");
       		return;
       	}

       	if(packet.destination_ip.is_ipv6 != false) {
       		printf("FAIL: destination IP marked as IPv6\n");
       		return;
       	}

       	uint8_t expected_source[4] = {
       		192, 168, 1, 10
       	};

       	uint8_t expected_destination[4] = {
       		192, 168,1,20
       	};

       	if(memcmp(
       		packet.destination_ip.address,
       		expected_destination,
       		4
       	) != 0 ) {
       	printf("FAIL: incorrect destination IP\n");
       	return;
       }

       	if(memcmp(
       		packet.source_ip.address,
       		expected_source,
       		4
       	) != 0 ) {
       	printf("FAIL: incorrect source IP\n");
       	return;
       }

       if( packet.protocol != IDS_PROTOCOL_TCP) {
       		printf("FAIL: incorrect protocol\n");
       		return;
       	}

       	if( packet.packet_length != 40 ) {
       		printf("FAIL: incorrect packet length\n");
       		return;
       	}

       	if( packet.payload_length != 20 ) {
       		printf("FAIL: incorrect payload length\n");
       		return;
       	}


       	if( packet.payload != data + 20 ) {
       		printf("FAIL: incorrect payload pointer \n");
       		return;
       	}

        printf("PASS: valid IPv4 packet\n");

 }


 static void test_invalid_version()
 {
    uint8_t data[20] ={0};

    data[0] = 0x65;

    ids_packet_t packet;

    ids_parse_result_t result = 
    		ids_parse_ipv4(
    				data,
    				sizeof(data),
    				&packet
    		);

    if(result != IDS_PARSE_MALFORMED) {
    	printf("FAIL: invliad IPv4 version test\n");
    	return;
    }

    printf("PASS: invalid IPv4 version test\n");
}


static void test_invalid_header_length()
{

	uint8_t data[20] = {0};

	data[0] = 41;

	ids_packet_t packet;

	ids_parse_result_t result = 
			ids_parse_ipv4(
				data,
				sizeof(data),
				&packet
			);


    if( result != IDS_PARSE_MALFORMED) {
    	printf("FAIL: invalid IPv4 header length test\n");
    	return;
    }

    printf("PASS: invalid IPv4 header length test\n");
 }

 static void test_header_length_greater_than_data()
 {
  	uint8_t data[20] = {0};

  	data[0] = 0x4f;

  	ids_packet_t packet;

  	ids_parse_result_t result = 
  		ids_parse_ipv4(
  			data,
  			sizeof(data),
  			&packet
  		);

  	if( result != IDS_PARSE_TRUNCATED) {
  		printf("FAIL: header length greater than data test\n");
  		return;
  	}

  	printf("PASS: header length greater than data test\n");
 }

 static void test_total_length_smaller_than_header()
 {
 	uint8_t data[20] = {0};

 	data[0] = 0x45;
 	data[2] = 0x00;
 	data[3] = 0x13;

 	ids_packet_t packet;

 	ids_parse_result_t result =
 			  ids_parse_ipv4(
 					data,
 					sizeof(data),
 					&packet
 				);

 	if( result != IDS_PARSE_MALFORMED) {
 		printf("FAILL: header total length smaller than header length\n");
 		return;
 	}

 	printf("PASS: header total length smaller than header length\n");

}


static void test_total_length_greater_than_data()
{
	uint8_t data[20] = {0};

	data[0]=0x45;
	data[2] = 0x00;
	data[3] = 0x3c;

	ids_packet_t packet;

	ids_parse_result_t result = 
		ids_parse_ipv4(
			data,
			sizeof(data),
			&packet
		);

	if ( result != IDS_PARSE_TRUNCATED) {
		printf("FAIL: total length greater than data test\n");
		return;
	}

	printf("PASS: total length greater than data test\n");
}
int  main() 
{

  printf("Running IPv4 parser tests...\n\n");

  test_valid_ipv4();
  test_null_data();
  test_null_output();
  test_truncated_header();
  test_invalid_version();
  test_invalid_header_length();
  test_header_length_greater_than_data();
  test_total_length_smaller_than_header();
  test_total_length_greater_than_data();

  printf("\nIPv4 parser tests complete.\n");

  return 0;

 }
