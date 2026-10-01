#include <stdio.h>
#include <stdint.h>

#include "feature.h"

int main(void)
{
	ids_flow_t flow = {0};
    ids_flow_table_t table = {0};
    ids_rate_features_t features = {0};

    /* Demo flow: duration = 2 seconds */
    flow.first_seen_ns = 1000000000ULL;
    flow.last_seen_ns  = 3000000000ULL;

    flow.packets_forward = 100;
    flow.packets_reverse = 50;

    flow.bytes_forward = 10000;
    flow.bytes_reverse = 5000;

    /* Extract features */
    ids_extract_rate_features(
    	&flow,
        &table,
        &features
    );

    /* Manual validation */
    if (features.packets_per_second == 75.0)
        printf("PASS: packets_per_second\n");
    else
        printf("FAIL: packets_per_second\n");

    if (features.bytes_per_second == 7500.0)
        printf("PASS: bytes_per_second\n");
    else
        printf("FAIL: bytes_per_second\n");

    return 0;
}
