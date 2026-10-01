#include <stdio.h>
#include <stdint.h>

#include "feature.h"


int main(void)
{
    ids_flow_t flow = {0};
	ids_flow_table_t table = {0};
    ids_flow_features_t features = {0};

    /* Demo flow */
    flow.packets_forward = 10;
    flow.packets_reverse = 5;

    flow.bytes_forward = 10000;
    flow.bytes_reverse = 5000;

    flow.syn_count = 2;
    flow.ack_count = 8;
    flow.rst_count = 1;

    /* Extract features */
    ids_extract_flow_features(
        &flow,
        &table,
        &features
    );

    /* Manual validation */
    if (features.packet_count == 15)
        printf("PASS: packet_count\n");
    else
        printf("FAIL: packet_count\n");

    if (features.byte_count == 15000)
        printf("PASS: byte_count\n");
    else
        printf("FAIL: byte_count\n");

    if (features.packets_forward == 10)
        printf("PASS: packets_forward\n");
    else
        printf("FAIL: packets_forward\n");

    if (features.packets_reverse == 5)
        printf("PASS: packets_reverse\n");
    else
        printf("FAIL: packets_reverse\n");

    if (features.bytes_forward == 10000)
        printf("PASS: bytes_forward\n");
    else
        printf("FAIL: bytes_forward\n");

    if (features.bytes_reverse == 5000)
        printf("PASS: bytes_reverse\n");
    else
        printf("FAIL: bytes_reverse\n");

    if (features.syn_count == 2)
        printf("PASS: syn_count\n");
    else
        printf("FAIL: syn_count\n");

    if (features.ack_count == 8)
        printf("PASS: ack_count\n");
    else
        printf("FAIL: ack_count\n");

    if (features.rst_count == 1)
        printf("PASS: rst_count\n");
    else
        printf("FAIL: rst_count\n");

    return 0;
}
