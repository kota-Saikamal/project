#include "icmp.h"
#include "ids_types.h"

#include <stdio.h>
#include <stdint.h>

static void test_null_data()
{
	ids_icmp_t icmp;

	ids_parse_result_t result = 
		ids_parse_icmp(
			NULL,
			4,
			&icmp
		);

	if( result != IDS_PARSE_INVALID_ARGUMENT) {
		printf("FAIL: NULL data test\n");
		return;
	}

	printf("PASS: NULL data test\n");
}

static void test_null_output()
{
	uint8_t data[4]={0};

	ids_parse_result_t result = 
		ids_parse_icmp(
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
	uint8_t data[3]={0};
	ids_icmp_t icmp;

	ids_parse_result_t result = 
		ids_parse_icmp(
			data,
			sizeof(data),
			&icmp
		);

	if( result != IDS_PARSE_TRUNCATED) {
		printf("FAIL: truncated ICMP header test\n");
		return;
	}

	printf("PASS: truncated ICMP header test\n");
}

static void test_valid_icmp()
{
	uint8_t data[4]={
      0x08,
      0x00,
      0x12,0x34
	};
	ids_icmp_t icmp;

	ids_parse_result_t result = 
		ids_parse_icmp(
			data,
			sizeof(data),
			&icmp
		);
    if(result != IDS_PARSE_OK) {
    	printf("FAIL: valid ICMP packet\n");
    	return;
    }

	if(icmp.type != 8) {
		printf("FAIL: incorrect ICMP type\n");
		return;
	}

	if(icmp.code != 0) {
		printf("FAIL: incorrect ICMP code\n");
		return;
	}
    
	if(icmp.checksum != 0x1234) {
		printf("FAIL: incorrect ICMP checksum\n");
		return;
	}

	printf("PASS: valid ICMP packet\n");
}

int main()
{
	printf("Running ICMP parser tests...\n\n");

	test_null_data();
	test_null_output();
	test_truncated_header();
	test_valid_icmp();

	printf("\nICMP parser tests complete.\n");

	return 0;
}
