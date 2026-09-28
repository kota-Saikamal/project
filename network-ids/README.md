Yes. Here is the **current project-status `README.md`**, reflecting what we have actually completed so far and what remains.

# Network IDS

A C-based Network Intrusion Detection System (IDS) designed to capture network traffic, parse packets, track bidirectional flows, extract detection-oriented features, detect suspicious activity, correlate events, and generate alerts.

## Project Status

**Current stage:** Flow management completed → Feature extraction in progress.

### Completed

* [x] Project architecture defined
* [x] Ethernet parsing
* [x] IPv4 parsing
* [x] IPv6 parsing
* [x] TCP parsing
* [x] UDP parsing
* [x] ICMP parsing
* [x] ICMPv6 parsing
* [x] Parser integration
* [x] Packet capture using libpcap
* [x] Bidirectional flow design
* [x] Flow key generation
* [x] Flow equality / reverse-flow matching
* [x] Flow initialization
* [x] Flow updates
* [x] Flow table
* [x] Flow table lookup
* [x] Flow creation
* [x] Flow table capacity handling
* [x] Unit tests for parser and flow components
* [x] Unit tests for flow table

## Current Architecture

```text
Network Interface
       │
       ▼
   libpcap Capture
       │
       ▼
     Parser
       │
       ├── Ethernet
       ├── IPv4
       ├── IPv6
       ├── TCP
       ├── UDP
       ├── ICMP
       └── ICMPv6
       │
       ▼
   Flow Management
       │
       ├── Flow Key
       ├── Flow State
       └── Flow Table
       │
       ▼
 Feature Extraction        ← CURRENT STAGE
       │
       ▼
    Detection
       │
       ▼
   Correlation
       │
       ▼
     Alerts
```

## Repository Structure

```text
network-ids/
├── src/
│   ├── main.c
│   ├── capture/
│   ├── parser/
│   │   ├── parser.c
│   │   ├── parser.h
│   │   ├── ethernet.c
│   │   ├── ethernet.h
│   │   ├── ipv4.c
│   │   ├── ipv4.h
│   │   ├── ipv6.c
│   │   ├── ipv6.h
│   │   ├── tcp.c
│   │   ├── tcp.h
│   │   ├── udp.c
│   │   ├── udp.h
│   │   ├── icmp.c
│   │   └── icmp.h
│   ├── flow/
│   │   ├── flow.c
│   │   ├── flow.h
│   │   ├── flow_table.c
│   │   └── flow_table.h
│   ├── feature/
│   │   ├── feature.c
│   │   └── feature.h
│   ├── detection/
│   ├── correlation/
│   ├── alert/
│   ├── config/
│   └── common/
│
├── include/
│   └── ids_types.h
│
├── rules/
├── configs/
├── python/
├── database/
├── dashboard/
├── scripts/
├── tests/
├── docs/
├── Makefile
└── README.md
```

## Packet Processing

Captured packets are passed through the parser and converted into an `ids_packet_t`.

The packet currently contains information such as:

* Ethernet information
* Source IP
* Destination IP
* Protocol
* Source port
* Destination port
* TCP state information
* UDP information
* ICMP / ICMPv6 information
* Packet length
* Payload information
* Timestamp
* Malformed-packet status

## Flow Management

The IDS uses **bidirectional flows**.

A flow is identified using:

```text
Source IP
Destination IP
Source Port
Destination Port
Protocol
```

The flow layer also recognizes the reverse direction as belonging to the same flow.

Example:

```text
192.168.1.10:5000 → 192.168.1.20:80
192.168.1.20:80   → 192.168.1.10:5000
```

Both packets belong to the same bidirectional flow.

Each flow currently tracks:

* First-seen timestamp
* Last-seen timestamp
* Forward packet count
* Reverse packet count
* Forward byte count
* Reverse byte count
* SYN count
* ACK count
* RST count
* FIN count
* Established state

## Flow Table

The current flow table is a fixed-capacity table:

```c
#define IDS_FLOW_TABLE_CAPACITY 1024
```

The table:

1. Generates a flow key from the packet.
2. Searches for an existing flow.
3. Updates the flow if found.
4. Creates a new flow if not found.
5. Rejects new flows when capacity is reached.

The flow-table unit tests currently cover:

* Initialization
* Flow creation
* Same-flow detection
* Reverse-flow detection
* Different-flow detection
* Capacity handling

All current flow-table tests pass.

## Feature Extraction

**Current development stage.**

The feature layer is currently being designed around features that are useful to the detection engine.

The current `ids_flow_features_t` contains:

```text
packet_count
byte_count
packets_forward
packets_reverse
bytes_forward
bytes_reverse
syn_count
ack_count
rst_count
unique_destination_ports
unique_destination_hosts
packets_per_second
bytes_per_second
connection_rate
```

The current approach is to avoid unnecessarily duplicating packet information. Features should be derived from the packet and flow state where appropriate.

### Feature Architecture

Currently:

```text
feature/
├── feature.c
└── feature.h
```

`feature.h` acts as the public API.

`feature.c` acts as the initial feature-extraction orchestrator.

Additional files such as:

```text
packet_features.c
flow_features.c
rate_features.c
```

will only be introduced if the feature implementation becomes large enough to justify splitting it.

## Unique Destination Features

`unique_destination_ports` represents the number of distinct destination ports across the flows being analyzed.

Example:

```text
Flow 1 → port 80
Flow 2 → port 80
Flow 3 → port 443
Flow 4 → port 22
```

Result:

```text
unique_destination_ports = 3
```

Similarly, `unique_destination_hosts` represents the number of distinct destination IP addresses across the relevant flows.

A hash-based structure may be used later to efficiently track unique ports and hosts.

## Common Utilities

The project currently has a planned `common/` layer:

```text
common/
├── logger.c
├── logger.h
├── hashmap.c
├── hashmap.h
├── queue.c
├── queue.h
├── time.c
└── time.h
```

These utilities will be implemented when required.

Potential uses:

* `hashmap` → efficient flow/host/port lookup
* `time` → rate and time-window calculations
* `logger` → IDS runtime and diagnostic logging
* `queue` → future packet/event processing pipelines

## Detection

Planned detection modules:

```text
detection/
├── detector.c
├── detector.h
├── port_scan.c
├── syn_scan.c
├── icmp_sweep.c
├── syn_flood.c
├── udp_flood.c
├── brute_force.c
└── anomaly.c
```

Planned detections include:

* Port scanning
* SYN scanning
* ICMP sweeps
* SYN floods
* UDP floods
* Brute-force activity
* General traffic anomalies

Detection implementation has **not started yet**.

## Correlation

Planned correlation layer:

```text
correlation/
├── correlator.c
└── correlator.h
```

Its purpose is to combine related detection events into higher-level security incidents.

Correlation implementation has **not started yet**.

## Alerting

Planned alert layer:

```text
alert/
├── alert.c
├── alert.h
├── json_output.c
└── file_output.c
```

The alert layer will be responsible for producing structured IDS alerts and writing them to configured outputs.

Alert implementation has **not started yet**.

## Configuration

Planned configuration layer:

```text
config/
├── config.c
└── config.h
```

Configuration will eventually contain items such as:

* Capture interface
* Detection thresholds
* Flow limits
* Detection rules
* Alert configuration

Configuration implementation has **not started yet**.

## Database

The current database directory is SQL-oriented:

```text
database/
├── schema.sql
├── indexes.sql
└── queries.sql
```

A NoSQL storage layer has **not been implemented yet**.

If a NoSQL database is added later, it should be treated as a separate storage/integration layer rather than mixing it directly into the existing SQL files.

## Testing

Testing is being done incrementally with manually validated unit tests.

Current test areas include:

```text
tests/
├── unit/
├── integration/
├── detection/
└── pcaps/
```

Completed unit-test coverage includes the packet parser and flow-management components.

The project currently favors explicit manual test checks rather than relying exclusively on `assert()`.

## Next Development Step

The next task is to complete the **feature extraction layer**.

The immediate goals are:

1. Derive basic flow features from `ids_flow_t`.
2. Design efficient tracking for unique destination ports.
3. Design efficient tracking for unique destination hosts.
4. Add timestamp-based rate calculations.
5. Write feature unit tests.
6. Pass the resulting features into the detection layer.

After feature extraction is stable, development will move to the detection engine.
