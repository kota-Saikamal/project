#include "ids_types.h"
#include "udp.h"

#include <stdint.h>
#include <stdio.h>


static void test_null_data() 
{
	ids_udp_t udp;

	ids_parse_result_t result = ids_parse_udp(
									NULL,
									8,
									&udp
								);

	if(result != IDS_PARSE_INVALID_ARGUMENT) {
	     printf("FAIL: NULL data test\n");
	     return;
	 }

	 printf("PASS: NULL data test\n");
	 	 
}

static void test_null_output() 
{
	uint8_t data[8] = {0};
    
	ids_parse_result_t result = ids_parse_udp(
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
 	uint8_t data[7] = {0};
    ids_udp_t udp;
 	
 	ids_parse_result_t result = ids_parse_udp(
 									data,
 									sizeof(data),
 									&udp
 								);



    if( result != IDS_PARSE_TRUNCATED) {
    	printf("FAIL: truncated UDP header test\n");
    	return;
    }

    printf("PASS: truncated UDP header test\n");
}


    

static void test_valid_udp()
{
	uint8_t data[8] = {
	 0x30,0x39,

	 0x00,0x35,
	 
	 0x00, 0x08,
	 
	 0x00, 0x00
   };

   ids_udp_t udp;

   ids_parse_result_t result =  ids_parse_udp(
   							data,
   							sizeof(data),
   							&udp
   						);

       if(result != IDS_PARSE_OK) {
       		printf("FAIL; valid UDP packet\n");
       		return;
       	}

       	if(udp.source_port != 12345) {
       		printf("FAIL: incorrect source port\n");
       		return;
       	}

       	if(udp.destination_port != 53) {
       		printf("FAIL: incorrect destination port\n");
       		return;
       	}

        if(udp.length != 8) {
       		printf("FAIL: incorrect UDP length\n");
       		return;
       	}
     	
  
        printf("PASS: valid UDP packet\n");

}

static void test_udp_length_greater_than_data()
{
  	uint8_t data[8] = {
  	 0x30, 0x39,
  	 0x00, 0x35,
  	 0x00, 0x10,
  	 0x00, 0x00
  	};

  	ids_udp_t udp;

  	ids_parse_result_t result = 
  		ids_parse_udp(
  			data,
  			sizeof(data),
  			&udp
  		);

  	if( result != IDS_PARSE_TRUNCATED) {
  		printf("FAIL: UDP length greater than data test\n");
  		return;
  	}

  	printf("PASS: UDP length greater than data test\n");
 }

 static void test_invalid_udp_length()
 {
 	uint8_t data[8] = {
 	  0x30, 0x39,
 	  0x00, 0x35,
 	  0x00, 0x07,
 	  0x00, 0x00
 	 };

 	ids_udp_t udp;

 	ids_parse_result_t result =
 			  ids_parse_udp(
 					data,
 					sizeof(data),
 					&udp
 				);

 	if( result != IDS_PARSE_MALFORMED) {
 		printf("FAILL: invalid UDP length test\n");
 		return;
 	}

 	printf("PASS: invalid UDP length test\n");

}

int  main() 
{

  printf("Running udp parser tests...\n\n");

  test_valid_udp();
  test_null_data();
  test_null_output();
  test_truncated_header();
  test_invalid_udp_length();
  test_udp_length_greater_than_data();

  printf("\nudp parser tests complete.\n");

  return 0;

 }
