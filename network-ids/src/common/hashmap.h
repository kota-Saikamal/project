#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define IDS_HASHMAP_CAPACITY 1024

typedef enum {
	IDS_HASH_KEY_UINT64,
	IDS_HASH_KEY_IP
} ids_hash_key_type_t;

typedef struct {
	ids_hash_key_type_t type;
	union {
		uint64_t uint64_key;
		ids_ip_address_t ip_key;
	}key;
	
	bool used;
}ids_hashmap_entry_t;

typedef struct {
	ids_hasmap_entry_t entries[IDS_HASHMAP_CAPACITY];
	size_t count;
}ids_hashmap_t;


void ids_hashmap_init(
	ids_hashmap_t *map
);

bool is_hashmap_insert_uint64(
	ids_hashmap_t *map,
	uint64_t key
);

bool is_hashmap_insert_ip(
	ids_hashmap_t *map,
	const ids_ip_address_t *key
);

void is_hashmap_contains_uint64(
	const ids_hashmap_t *map,
	uint64_t key
);

void is_hashmap_contains_ip(
	const ids_hashmap_t *map,
	const ids_ip_address_t *key
);
size_t ids_hashmap_size(
	const ids_hashmap_t *map
);

#endif


