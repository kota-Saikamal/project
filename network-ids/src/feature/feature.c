#include "feature.h"

void ids_extract_features(
	const ids_packet_t *packet,
	const ids_flow_t *flow,
	const ids_flow_table_t *table,
	ids_packet_features_t *packet_features,
	ids_flow_features_t *flow_features,
	ids_rate_features_t *rate_features
)
	{
		if( packet == NULL || 
			flow  == NULL ||
			table == NULL ||
			flow_features == NULL ||
			packet_features == NULL ||
			rate_features == NULL ) {
			
			return;
		}

		ids_extract_packet_features(
			packet,
			packet_features
		);
		
		ids_extract_flow_features(
			flow,
			table,
			flow_features
		);

		ids_extract_rate_features(
			flow,
			table,
			rate_features
		);		

}
