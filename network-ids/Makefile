CC := gcc

CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Iinclude
LDFLAGS :=
LDLIBS := -lpcap

TARGET := network-ids
BUILD_DIR := build

SOURCES := \
	src/main.c \
	src/capture/capture.c \
	src/parser/parser.c \
	src/parser/ethernet.c \
	src/parser/ipv4.c \
	src/parser/ipv6.c \
	src/parser/tcp.c \
	src/parser/udp.c \
	src/parser/icmp.c \
	src/flow/flow.c \
	src/flow/flow_table.c \
	src/feature/feature.c \
	src/feature/packet_features.c \
	src/feature/flow_features.c \
	src/feature/rate_features.c \
	src/detection/detector.c \
	src/detection/port_scan.c \
	src/detection/syn_scan.c \
	src/detection/icmp_sweep.c \
	src/detection/syn_flood.c \
	src/detection/udp_flood.c \
	src/detection/brute_force.c \
	src/detection/anomaly.c \
	src/correlation/correlator.c \
	src/alert/alert.c \
	src/alert/json_output.c \
	src/alert/file_output.c \
	src/config/config.c \
	src/common/logger.c \
	src/common/hashmap.c \
	src/common/queue.c \
	src/common/time.c

OBJECTS := $(SOURCES:%.c=$(BUILD_DIR)/%.o)

.PHONY: all clean debug test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -g -O0 -fsanitize=address,undefined
debug: LDFLAGS += -fsanitize=address,undefined
debug: clean all

test:
	./scripts/test.sh

clean:
	rm -rf $(BUILD_DIR) $(TARGET)