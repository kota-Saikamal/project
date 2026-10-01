#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "feature.h"

int main(void)
{
    ids_packet_t packet = {0};
    ids_flow_t flow = {0};
    ids_flow_table_t table = {0};

    ids_packet_features_t packet_features = {0};
    ids_flow_features_t flow_features = {0};
    ids_rate_features_t rate_features = {0};

    /* Demo packet */
    packet.packet_length = 1500;
    packet.payload_length = 1460;
    packet.protocol = IDS_PROTOCOL_TCP;
    packet.malformed = false;

    /* Demo flow */
    flow.packets_forward = 10;
    flow.packets_reverse = 5;

    flow.bytes_forward = 10000;
    flow.bytes_reverse = 5000;

    flow.syn_count = 2;
    flow.ack_count = 8;
    flow.rst_count = 1;

    /* 2-second flow duration */
    flow.first_seen_ns = 1000000000ULL;
    flow.last_seen_ns = 3000000000ULL;

    /* Extract all features */
    ids_extract_features(
        &packet,
        &flow,
        &table,
        &packet_features,
        &flow_features,
        &rate_features
    );

    /* Packet feature checks */
    if (packet_features.packet_length == packet.packet_length)
        printf("PASS: packet_length\n");
    else
        printf("FAIL: packet_length\n");

    if (packet_features.payload_length == packet.payload_length)
        printf("PASS: payload_length\n");
    else
        printf("FAIL: payload_length\n");

    if (packet_features.protocol == packet.protocol)
        printf("PASS: protocol\n");
    else
        printf("FAIL: protocol\n");

    if (packet_features.malformed == packet.malformed)
        printf("PASS: malformed\n");
    else
        printf("FAIL: malformed\n");

    /* Flow feature checks */
    if (flow_features.packet_count == 15)
        printf("PASS: packet_count\n");
    else
        printf("FAIL: packet_count\n");

    if (flow_features.byte_count == 15000)
        printf("PASS: byte_count\n");
    else
        printf("FAIL: byte_count\n");

    if (flow_features.syn_count == 2)
        printf("PASS: syn_count\n");
    else
        printf("FAIL: syn_count\n");

    /* Rate feature checks */
    if (rate_features.packets_per_second == 7.5)
        printf("PASS: packets_per_second\n");
    else
        printf("FAIL: packets_per_second\n");

    if (rate_features.bytes_per_second == 7500.0)
        printf("PASS: bytes_per_second\n");
    else
        printf("FAIL: bytes_per_second\n");

    printf("\nFeature extraction test complete.\n");

    return 0;
}