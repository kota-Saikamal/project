#ifndef IDS_FLOW_TABLE_H
#define IDS_FLOW_TABLE_H

#include <stddef.h>
#include <stdbool.h>

#include "ids_types.h"

#define IDS_FLOW_TABLE_CAPACITY 1024

typedef struct {
	ids_flow_t flows[IDS_FLOW_TABLE_CAPACITY];
	size_t count;
} ids_flow_table_t;

void ids_flow_table_init(
	ids_flow_table_t *table
);


ids_flow_t *ids_flow_table_find(
	ids_flow_table_t *table,
	const ids_flow_key_t *key
);

ids_flow_t *ids_flow_table_get_or_create(
	ids_flow_table_t *table,
	const ids_packet_t *packet
);

#endif


