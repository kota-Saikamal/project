#ifndef FLOW_H
#define FLOW_H

#include <stdbool.h>
#include <stdint.h>

#include "ids_types.h"

void ids_flow_init(
	 ids_flow_t *flow,
	 const ids_packet_t *packet
	);

ids_flow_key_t ids_flow_key_from_packet(const ids_packet_t *packet);

bool ids_flow_key_equal(
		const ids_flow_key_t *a,
		const ids_flow_key_t *b
		);

void ids_flow_update(
		ids_flow_t *flow,
		const ids_packet_t *packet
		);

#endif
