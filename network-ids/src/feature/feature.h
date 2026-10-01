#ifndef FEATURES_H
#define FEATURES_H

#include "flow_table.h"
#include "ids_types.h"

void ids_extract_features(
	const ids_packet_t *packet,
	const ids_flow_t *flow,
	const ids_flow_table_t *table,
	ids_packet_features_t *packet_features,
	ids_flow_features_t *flow_features,
	ids_rate_features_t *rate_features
);



void ids_extract_packet_features(
	const ids_packet_t *packet,
	ids_packet_features_t *features
);

void ids_extract_flow_features(
	const ids_flow_t *flow,
	const ids_flow_table_t *table,
	ids_flow_features_t *features
);

void ids_extract_rate_features(
	const ids_flow_t *flow,
	const ids_flow_table_t *table,
	ids_rate_features_t *features
);

#endif
