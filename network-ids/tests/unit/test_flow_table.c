#include "flow.h"
#include "flow_table.h"
#include "ids_types.h"

#include <stdio.h>
#include <string.h>


static void test_ids_flow_table_init()
{
	ids_flow_table_t table;
	table.count = 999;

	ids_flow_table_init(&table);

	if(table.count !=0) {
		printf("FAIL: table count shoule be zero\n");
		return;
	}

	printf("PASS: table count should be zero\n");
}

static void test_ids_flow_table_create()
{
	ids_flow_table_t table;
	ids_packet_t packet = {0};

	packet.protocol = IDS_PROTOCOL_TCP;
	packet.packet_length = 100;
	
	
	ids_flow_table_init(&table);

	ids_flow_t *flow = ids_flow_table_get_or_create(&table, &packet);

	if(flow == NULL || table.count !=1)
	{
		printf("FAIL: flow table creation test\n");
		return;
	}
	printf("PASS: flow table creation test\n");
}

static void test_ids_flow_table_same_flow()
{
	ids_flow_table_t table;
	ids_packet_t packet = {0};

	packet.protocol = IDS_PROTOCOL_TCP;
	packet.packet_length = 100;
	
	ids_flow_table_init(&table);

	ids_flow_t *flow = ids_flow_table_get_or_create(&table, &packet);
	ids_flow_t *flow2 = ids_flow_table_get_or_create(&table, &packet);

	if(flow != flow2 || table.count !=1)
	{
		printf("FAIL: flow same packet test\n");
		return;
	}
	printf("PASS: flow same packet test\n");
}
	
static void test_ids_flow_table_reverse()
{
	ids_flow_table_t table;
	ids_packet_t packet1 = {0};
	ids_packet_t packet2 = {0};

	packet1.source_ip.is_ipv6 = false;
	packet1.destination_ip.is_ipv6 = false;

	packet1.source_ip.address[0]=192;
	packet1.source_ip.address[1]=168;
	packet1.source_ip.address[2]=1;
	packet1.source_ip.address[3]=10;

	packet1.destination_ip.address[0]=192;
	packet1.destination_ip.address[1]=168;
	packet1.destination_ip.address[2]=1;
	packet1.destination_ip.address[3]=20;


	packet1.protocol = IDS_PROTOCOL_TCP;
	packet1.transport.tcp.source_port = 5000;
	packet1.transport.tcp.destination_port = 80;

	packet2 = packet1;

	memcpy(packet2.source_ip.address,
			packet1.destination_ip.address,
			IDS_IPV6_ADDRESS_LEN);

	memcpy(packet2.destination_ip.address,
			packet1.source_ip.address,
			IDS_IPV6_ADDRESS_LEN);

	packet2.transport.tcp.source_port = 80;
	packet2.transport.tcp.destination_port = 5000;

	ids_flow_table_init(&table);

	ids_flow_t *flow1 = ids_flow_table_get_or_create(&table, &packet1);
	ids_flow_t *flow2 = ids_flow_table_get_or_create(&table, &packet2);

	if(flow1 !=flow2 && table.count !=1)
	{
		printf("FAIL: flow table reverse test\n");
		return;
	}

	printf("PASS: flow table reverse test\n");
}

static void test_ids_flow_table_different_flows()
{
	ids_flow_table_t table;
	ids_packet_t packet1 = {0};
	ids_packet_t packet2 = {0};

	packet1.protocol = IDS_PROTOCOL_TCP;

	packet1.source_ip.address[0] = 192;
	packet1.destination_ip.address[0] = 10;
	packet1.transport.tcp.source_port = 5000;
	packet1.transport.tcp.destination_port = 80;

	packet2 = packet1;
	
	packet2.transport.tcp.destination_port = 443;
	
	ids_flow_table_init(&table);

	ids_flow_t *flow1 = ids_flow_table_get_or_create(&table, &packet1);
	ids_flow_t *flow2 = ids_flow_table_get_or_create(&table, &packet2);

    
	if(flow1 == flow2 || table.count != 2)
	{
		printf("FAIL: different flows test\n");
		return;
	}

	printf("PASS: different flows test\n");

}

static void test_ids_flow_table_capacity()
{	
	ids_flow_table_t table;
	ids_packet_t packet = {0};

	packet.protocol = IDS_PROTOCOL_TCP;
	ids_flow_table_init(&table);

	for(size_t i=0;i< IDS_FLOW_TABLE_CAPACITY; i++) {
		
		packet.transport.tcp.destination_port = (uint16_t)(i+1);
			
		ids_flow_t *flow = ids_flow_table_get_or_create(&table, &packet);
		        
		if(flow == NULL) {

			printf("FAIL: capacity test\n");
			return;
		}
	}
	
	packet.transport.tcp.destination_port = 65535;

	ids_flow_t *flow = ids_flow_table_get_or_create(&table, &packet);
   
    if(flow != NULL || table.count != IDS_FLOW_TABLE_CAPACITY)
	{
		
		printf("FAIL: capacity test\n");
		return;
	}
	printf("PASS: capacity test\n");
}


int main()
{

	test_ids_flow_table_init();
	test_ids_flow_table_create();
	test_ids_flow_table_same_flow();
	test_ids_flow_table_reverse();
	test_ids_flow_table_different_flows();
	test_ids_flow_table_capacity();

	return 0;
}
