#include <stddef.h>

#include "feature.h"

static double calculate_duration_seconds(
	const ids_flow_t *flow
)
	{
		if (flow == NULL || flow->last_seen_ns <= flow->first_seen_ns) {
			return 0.0;
		}

		return (double)(flow->last_seen_ns - flow->first_seen_ns) /1000000000.0;
	}

void ids_extract_rate_features(
	const ids_flow_t *flow,
	const ids_flow_table_t *table,
	ids_rate_features_t *features
)
	{
		if( flow == NULL || table == NULL || features == NULL) {
			return;
		}

		features->packets_per_second = 0.0;
		features->bytes_per_second = 0.0;
		features->connection_rate = 0.0;


		double duration = calculate_duration_seconds(flow);

		if( duration > 0.0) {

			uint64_t packet_count =
				flow->packets_forward + flow->packets_reverse;
				
			uint64_t byte_count =
				flow->bytes_forward + flow->bytes_reverse;

			features->packets_per_second = (double)packet_count / duration;

			features->bytes_per_second = (double)byte_count / duration;

		}

		if(flow->first_seen_ns > 0) {
			uint64_t connection_count = table->count;

			double elapsed = (double)flow->first_seen_ns/1000000000.0;

			if(elapsed > 0.0) {
				features->connection_rate = (double) connection_count /elapsed;
			}
		}
	}
