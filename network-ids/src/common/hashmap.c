#include <string.h>

#include "hashmap.h"

static uint64_t ids_hash_uint64(uint64_t key)
{
    key ^= key >> 33;
    key *= 0xff51afd7ed558ccdULL;
    key ^= key >> 33;
    key *= 0xc4ceb9fe1a85ec53ULL;
    key ^= key >> 33;

    return key;
}

static uint64_t ids_hash_ip(
    const ids_ip_address_t *ip
)
{
    uint64_t hash = 14695981039346656037ULL;

    size_t length =
        ip->is_ipv6 ? IDS_IPV6_ADDRESS_LEN : 4;

    for (size_t i = 0; i < length; i++) {
        hash ^= ip->address[i];
        hash *= 1099511628211ULL;
    }

    hash ^= ip->is_ipv6 ? 1ULL : 0ULL;

    return ids_hash_uint64(hash);
}

static bool is_ip_equal(
    const ids_ip_address_t *a,
    const ids_ip_address_t *b
)
{
    if (a == NULL || b == NULL) {
        return false;
    }

    if (a->is_ipv6 != b->is_ipv6) {
        return false;
    }

    size_t length =
        a->is_ipv6 ? IDS_IPV6_ADDRESS_LEN : 4;

    return memcmp(a->address, b->address, length) == 0;
}

void ids_hashmap_init(
    ids_hashmap_t *map
)
{
    if (map == NULL) {
        return;
    }

    memset(map, 0, sizeof(*map));
}

bool ids_hashmap_insert_uint64(
    ids_hashmap_t *map,
    uint64_t key
)
{
    if (map == NULL ||
        map->count >= IDS_HASHMAP_CAPACITY) {
        return false;
    }

    size_t index =
        ids_hash_uint64(key) % IDS_HASHMAP_CAPACITY;

    for (size_t i = 0; i < IDS_HASHMAP_CAPACITY; i++) {

        size_t current =
            (index + i) % IDS_HASHMAP_CAPACITY;

        if (!map->entries[current].used) {

            map->entries[current].type =
                IDS_HASH_KEY_UINT64;

            map->entries[current].key.uint64_key =
                key;

            map->entries[current].used = true;
            map->count++;

            return true;
        }

        if (map->entries[current].type ==
                IDS_HASH_KEY_UINT64 &&
            map->entries[current].key.uint64_key == key) {

            return false;
        }
    }

    return false;
}

bool ids_hashmap_insert_ip(
    ids_hashmap_t *map,
    const ids_ip_address_t *key
)
{
    if (map == NULL ||
        key == NULL ||
        map->count >= IDS_HASHMAP_CAPACITY) {
        return false;
    }

    size_t index =
        ids_hash_ip(key) % IDS_HASHMAP_CAPACITY;

    for (size_t i = 0; i < IDS_HASHMAP_CAPACITY; i++) {

        size_t current =
            (index + i) % IDS_HASHMAP_CAPACITY;

        if (!map->entries[current].used) {

            map->entries[current].type =
                IDS_HASH_KEY_IP;

            map->entries[current].key.ip_key =
                *key;

            map->entries[current].used = true;
            map->count++;

            return true;
        }

        if (map->entries[current].type ==
                IDS_HASH_KEY_IP &&
            is_ip_equal(
                &map->entries[current].key.ip_key,
                key)) {

            return false;
        }
    }

    return false;
}

bool ids_hashmap_contains_uint64(
    const ids_hashmap_t *map,
    uint64_t key
)
{
    if (map == NULL) {
        return false;
    }

    size_t index =
        ids_hash_uint64(key) % IDS_HASHMAP_CAPACITY;

    for (size_t i = 0; i < IDS_HASHMAP_CAPACITY; i++) {

        size_t current =
            (index + i) % IDS_HASHMAP_CAPACITY;

        if (!map->entries[current].used) {
            return false;
        }

        if (map->entries[current].type ==
                IDS_HASH_KEY_UINT64 &&
            map->entries[current].key.uint64_key == key) {

            return true;
        }
    }

    return false;
}

bool ids_hashmap_contains_ip(
    const ids_hashmap_t *map,
    const ids_ip_address_t *key
)
{
    if (map == NULL || key == NULL) {
        return false;
    }

    size_t index =
        ids_hash_ip(key) % IDS_HASHMAP_CAPACITY;

    for (size_t i = 0; i < IDS_HASHMAP_CAPACITY; i++) {

        size_t current =
            (index + i) % IDS_HASHMAP_CAPACITY;

        if (!map->entries[current].used) {
            return false;
        }

        if (map->entries[current].type ==
                IDS_HASH_KEY_IP &&
            is_ip_equal(
                &map->entries[current].key.ip_key,
                key)) {

            return true;
        }
    }

    return false;
}

size_t ids_hashmap_size(
    const ids_hashmap_t *map
)
{
    if (map == NULL) {
        return 0;
    }

    return map->count;
}
