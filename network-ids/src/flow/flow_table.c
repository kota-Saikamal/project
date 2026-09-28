#include "flow_table.h"
#include "flow.h" 

#include <stdio.h>

void ids_flow_table_init(
	ids_flow_table_t *table
) 
	{
		if(table == NULL) {
			return;
		}

		table -> count =0;
	}

ids_flow_t *ids_flow_table_find(
	ids_flow_table_t *table,
	const ids_flow_key_t *key
)
	{
		if(table == NULL || key == NULL) {
			return NULL;
		}

		for(size_t i=0;i< table->count;i++) {
			if(ids_flow_key_equal(
				&table->flows[i].key,
				key)) {

				return &table->flows[i];
			}
		}

		return NULL;
 }

ids_flow_t *ids_flow_table_get_or_create(
	ids_flow_table_t *table,
	const ids_packet_t *packet
)
	{
		if(table == NULL || packet == NULL) 
		{
			return NULL;
		}

		ids_flow_key_t key = ids_flow_key_from_packet(packet);
		
		ids_flow_t *flow = ids_flow_table_find(table,&key);

		if(flow != NULL) {
			ids_flow_update(flow, packet);
			return flow;
		}

		if(table->count >= IDS_FLOW_TABLE_CAPACITY) {
			return NULL;
		}

		flow = &table->flows[table->count];

		ids_flow_init(flow,packet);
	
		table->count++;
		
	    return flow;
	}

