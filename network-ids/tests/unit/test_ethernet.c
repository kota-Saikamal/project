#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "ethernet.h"
#include "ids_types.h"

static void valid_ethernet_header() 
{
   uint8_t data[14] = {
      0x11, 0x22, 0x33, 0x44, 0x55, 0x66,
      0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
      0x08, 0x00
   };

   uint8_t expected_destination[6] = {
   	   0x11, 0x22, 0x33, 0x44, 0x55, 0x66
   	};

   	uint8_t expected_source[6] = {
   		0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
    };

    ids_ethernet_t ethernet;

    ids_parse_result_t result = ids_parse_ethernet (
    								data,
    								sizeof(data),
    								&ethernet
    								);

    if(result != IDS_PARSE_OK) {
    	printf("FAIL: valid Ethernet packet returned wrong result\n");
        return;
     }

     if(ethernet.ether_type != 0x0800) {
     	printf("FAIL: incorrect EtherType\n");
     	return;
      }

      if(memcmp( 
      		ethernet.destination,
      		expected_destination,
      		sizeof(expected_destination)
      	) != 0) {
      	printf("FAIL: incorrect destination MAC\n");
      	return;
      }

      if(memcmp(
      		ethernet.source,
      		expected_source,
      		sizeof(expected_source)
        ) != 0) {
        printf("FAIL: incorrect source MAC\n");
        return;
       }

       printf("PASS: valid Ethernet packet\n");
 }


 static void valid_truncated_ethernet() 
 {
     uint8_t data[13] = {0};

     ids_ethernet_t ethernet;

     ids_parse_result_t result = 
     	ids_parse_ethernet(
     		data,
     		sizeof(data),
     		&ethernet
     	   );

      if(result != IDS_PARSE_TRUNCATED) {
      		printf("FAIL: truncated Ethernet packet\n");
      		return;
      }

      printf("PASS: truncated Ethernet packet\n");
   }

   static void valid_input_null() 
   {
       ids_ethernet_t ethernet;

       ids_parse_result_t result = 
       		ids_parse_ethernet(
       			NULL,
       			14,
       			&ethernet
       			);
       	if(result != IDS_PARSE_INVALID_ARGUMENT) {
       		printf("FAIL: NULL data test\n");
       		return;
        }

        printf("PASS: NULL data test\n");
    }

   static void valid_output_null() 
   {
       uint8_t data[14] = {0};
      
       

       ids_parse_result_t result = 
       		ids_parse_ethernet(
       			data,
       			sizeof(data),
       			NULL
       			);
       	if(result != IDS_PARSE_INVALID_ARGUMENT) {
       		printf("FAIL: NULL output  test\n");
       		return;
        }

        printf("PASS: NULL output test\n");
    }

    int main()
  {

    printf("Running Ethernet parser tests...\n");

    valid_ethernet_header();
    valid_truncated_ethernet();
    valid_input_null();
    valid_output_null();

   printf("\nEthernet parser tests complete. \n");

   return 0;
 }
