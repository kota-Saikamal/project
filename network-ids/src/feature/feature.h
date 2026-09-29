#ifndef FEATURES_H
#define FEATURES_H

#include "ids_types.h"

void ids_extract_packet_features(
	const ids_packet_t *packet,
	ids_packet_features_t *features
);

void ids_extract_flow_features(
	const ids_flow_t *flow,
	ids_flow_features_t *features
);

void ids_extract_rate_features(
	const ids_flow_t *flow,
	ids_rate_features_t *features
);

#endif
