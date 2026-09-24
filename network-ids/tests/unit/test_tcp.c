#include "ids_types.h"
#include "tcp.h"

#include <stdint.h>
#include <stdio.h>


static void test_null_data() 
{
	ids_tcp_t tcp;

	ids_parse_result_t result = ids_parse_tcp(
									NULL,
									20,
									&tcp
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
    
	ids_parse_result_t result = ids_parse_tcp(
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
    ids_tcp_t tcp;
 	
 	ids_parse_result_t result = ids_parse_tcp(
 									data,
 									10,
 									&tcp
 								);



    if( result != IDS_PARSE_TRUNCATED) {
    	printf("FAIL: truncated tcp header test\n");
    	return;
    }

    printf("PASS: truncated tcp header test\n");
}


    

static void test_valid_tcp()
{
	uint8_t data[20] = {
	 0x30,0x39,

	 0x01,0xbb,

	 0x11, 0x22, 0x33, 0x44,
	 0x55, 0x66, 0x77, 0x88,
	 0x50,
	 0x02,
	 0x10, 0x00,
	 0x00, 0x00,
	 0x00, 0x00
   };

   ids_tcp_t tcp;

   ids_parse_result_t result =  ids_parse_tcp(
   							data,
   							sizeof(data),
   							&tcp
   						);

       if(result != IDS_PARSE_OK) {
       		printf("FAIL; valid tcp packet\n");
       		return;
       	}

       	if(tcp.source_port != 12345) {
       		printf("FAIL: incorrect source port\n");
       		return;
       	}

       	if(tcp.destination_port != 443) {
       		printf("FAIL: incorrect destination port\n");
       		return;
       	}

        if(tcp.sequence_number != 0x11223344) {
       		printf("FAIL: incorrect acknowledgment number\n");
       		return;
       	}

       	if(tcp.acknowledgment_number != 0x55667788) {
       		printf("FAIL: incorrect acknowledgment number\n");
       		return;
       	}

       	if(tcp.data_offset != 5) {
       		printf("FAIL: incorrect data offset\n");
       		return;
       	}

       	if(tcp.flags != 0x02) {
       		printf("FAIL: incorrect tcp flags\n");
       		return;
       	}

       	if(tcp.window_size != 4096) {
       		printf("FAIL: incorrect window size\n");
       	}

        printf("PASS: valid tcp packet\n");

}

static void test_header_length_greater_than_data()
{
  	uint8_t data[20] = {0};

  	data[12] = 0xf0;

  	ids_tcp_t tcp;

  	ids_parse_result_t result = 
  		ids_parse_tcp(
  			data,
  			sizeof(data),
  			&tcp
  		);

  	if( result != IDS_PARSE_TRUNCATED) {
  		printf("FAIL: header length greater than data test\n");
  		return;
  	}

  	printf("PASS: header length greater than data test\n");
 }

 static void test_invalid_data_offset()
 {
 	uint8_t data[20] = {0};

 	data[12] = 0x40;

 	ids_tcp_t tcp;

 	ids_parse_result_t result =
 			  ids_parse_tcp(
 					data,
 					sizeof(data),
 					&tcp
 				);

 	if( result != IDS_PARSE_MALFORMED) {
 		printf("FAILL: invalid tcp data offset test\n");
 		return;
 	}

 	printf("PASS: invalid tcp data offset test\n");

}

int  main() 
{

  printf("Running tcp parser tests...\n\n");

  test_valid_tcp();
  test_null_data();
  test_null_output();
  test_truncated_header();
  test_invalid_data_offset();
  test_header_length_greater_than_data();

  printf("\ntcp parser tests complete.\n");

  return 0;

 }
