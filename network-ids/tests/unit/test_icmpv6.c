#include "icmpv6.h"
#include "ids_types.h"

#include <stdio.h>
#include <stdint.h>

static void test_null_data()
{
	ids_icmpv6_t icmpv6;

	ids_parse_result_t result = 
		ids_parse_icmpv6(
			NULL,
			4,
			&icmpv6
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
		ids_parse_icmpv6(
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
	ids_icmpv6_t icmpv6;

	ids_parse_result_t result = 
		ids_parse_icmpv6(
			data,
			sizeof(data),
			&icmpv6
		);

	if( result != IDS_PARSE_TRUNCATED) {
		printf("FAIL: truncated icmpv6 header test\n");
		return;
	}

	printf("PASS: truncated icmpv6 header test\n");
}

static void test_valid_icmpv6()
{
	uint8_t data[4]={
      0x08,
      0x00,
      0x12,0x34
	};
	ids_icmpv6_t icmpv6;

	ids_parse_result_t result = 
		ids_parse_icmpv6(
			data,
			sizeof(data),
			&icmpv6
		);
    if(result != IDS_PARSE_OK) {
    	printf("FAIL: valid icmpv6 packet\n");
    	return;
    }

	if(icmpv6.type != 8) {
		printf("FAIL: incorrect icmpv6 type\n");
		return;
	}

	if(icmpv6.code != 0) {
		printf("FAIL: incorrect icmpv6 code\n");
		return;
	}
    
	if(icmpv6.checksum != 0x1234) {
		printf("FAIL: incorrect icmpv6 checksum\n");
		return;
	}

	printf("PASS: valid icmpv6 packet\n");
}

int main()
{
	printf("Running icmpv6 parser tests...\n\n");

	test_null_data();
	test_null_output();
	test_truncated_header();
	test_valid_icmpv6();

	printf("\nicmpv6 parser tests complete.\n");

	return 0;
}
