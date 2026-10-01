#include <stdio.h>
#include <stdbool.h>

#include "feature.h"

int main(void)
{
    ids_packet_t packet = {0};
    ids_packet_features_t features = {0};

    /* Demo packet */
    packet.packet_length = 1500;
    packet.payload_length = 1460;
    packet.protocol = IDS_PROTOCOL_TCP;
    packet.malformed = false;

    /* Extract features */
    ids_extract_packet_features(
        &packet,
        &features
    );

    /* Manual validation */
    if (features.packet_length == 1500) {
        printf("PASS: packet_length\n");
    } else {
        printf("FAIL: packet_length\n");
    }

    if (features.payload_length == 1460) {
        printf("PASS: payload_length\n");
    } else {
        printf("FAIL: payload_length\n");
    }

    if (features.protocol == IDS_PROTOCOL_TCP) {
        printf("PASS: protocol\n");
    } else {
        printf("FAIL: protocol\n");
    }

    if (features.malformed == false) {
        printf("PASS: malformed\n");
    } else {
        printf("FAIL: malformed\n");
    }

    return 0;
}