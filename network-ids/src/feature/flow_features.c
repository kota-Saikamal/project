#include <string.h>

#include "feature.h"
#include "hashmap.h"

static uint64_t count_unique_destination_ports(
    const ids_flow_table_t *table
)
{
    if (table == NULL) {
        return 0;
    }

    ids_hashmap_t ports;

    ids_hashmap_init(&ports);

    for (size_t i = 0; i < table->count; i++) {

        uint16_t port =
            table->flows[i].key.destination_port;

        ids_hashmap_insert_uint64(
            &ports,
            port
        );
    }

    return (uint64_t)ids_hashmap_size(&ports);
}

static uint64_t count_unique_destination_hosts(
    const ids_flow_table_t *table
)
{
    if (table == NULL) {
        return 0;
    }

    ids_hashmap_t hosts;

    ids_hashmap_init(&hosts);

    for (size_t i = 0; i < table->count; i++) {

        ids_hashmap_insert_ip(
            &hosts,
            &table->flows[i].key.destination_ip
        );
    }

    return (uint64_t)ids_hashmap_size(&hosts);
}

void ids_extract_flow_features(
    const ids_flow_t *flow,
    const ids_flow_table_t *table,
    ids_flow_features_t *features
)
{
    if (flow == NULL ||
        table == NULL ||
        features == NULL) {
        return;
    }

    memset(features, 0, sizeof(*features));

    features->packet_count =
        flow->packets_forward +
        flow->packets_reverse;

    features->byte_count =
        flow->bytes_forward +
        flow->bytes_reverse;

    features->packets_forward =
        flow->packets_forward;

    features->packets_reverse =
        flow->packets_reverse;

    features->bytes_forward =
        flow->bytes_forward;

    features->bytes_reverse =
        flow->bytes_reverse;

    features->syn_count =
        flow->syn_count;

    features->ack_count =
        flow->ack_count;

    features->rst_count =
        flow->rst_count;

    features->unique_destination_ports =
        count_unique_destination_ports(table);

    features->unique_destination_hosts =
        count_unique_destination_hosts(table);
}