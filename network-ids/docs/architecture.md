# Network IDS Architecture

## 1. Overview

The Network IDS is organized as a processing pipeline.

    Packet Source
          |
          v
       Capture
          |
          v
       Parser
          |
          v
    Flow Management
          |
          v
    Feature Extraction
          |
          v
       Detection
          |
          v
      Correlation
          |
          v
        Alert
          |
          +---------> File / JSON
          |
          +---------> Database
          |
          +---------> Analysis
          |
          +---------> Dashboard

## 2. Module Responsibilities

### Capture

Responsible for:
- Obtaining packets.
- Supporting live interfaces.
- Supporting PCAP replay.
- Provding packet timestamps.
- Passing packets to the parser.

Capture must not perform detection.

### Parser

Responsible for:

- Ethernet decoding.
- IPv4 decoding.
- IPv6 decoding.
- TCP decoding.
- UDP decoding.
- ICMP decoding.
- ICMPv6 decoding.
- DNS decoding.

Parser output must be normalized internal structures.

Parser must validate all packet boundaries before accessing fields.

### Flow 

Responsible for:

- Creating flow keys.
- Tracking bidirectional flows.
- Updating packet and byte counters.
- Tracking TCP state information.
- Tracking flow timestamps.
- Expiring inactive flows.

Flow management must not make detection decisions.

### Feature

Responsible for:

- Packet-level statistics.
- Flow-level statistics.
- Rate calculations.
- Unique host/port counts.
- TCP flag statistics.

Feature are consumed by detection modules.

### Detection

Responsible for identifying suspicious behavior.

Initial detectors: 

- Port scan
- SYN scan 
- ICMP sweep
- Brute force
- Flood 
- Statistical anomaly

Detectors produce normalized detection events.

### Correlation

Responsible for combining related detection events.

Correlation must not duplicate packet parsing or flow tracking.

### Alert

Responsible for:

- Formatiing alerts.
- Writing JSON output.
- writing file output.
- Managing alert destinations.

Alerts output must use the normalized detection event structure.

### Configuration

Reponsible for loading runtime configuration.

Modules must obtain configurable values from the configuration system rather than duplicating constants.

### Common 

Contains reusable infrastructure:

- Logging
- Hash map
- Queue
- Time utilities

## 3. Dependency Rules

Allowed dependency direction:
    main
      ↓
    capture
      ↓
    parser
      ↓
    flow
      ↓
    feature
      ↓
    detection
      ↓
    correlation
      ↓
    alert

Shared interfaces belong in `include/`.

Low-level modules must not depend on higher-level modules.

Detection modules must not depend directly on libpcap.

Alert modules must not perform packet parsing.

## 4. Data Flow

The fundamental data flow is:

    raw packet
        ↓
    packet_t
        ↓
    flow_t
        ↓
    flow_features_t
        ↓
    detection_event_t
        ↓
    alert

## 5. Error Handling

Malformed network input must not terminate the IDS.

Recoverable errors should be logged and processing should continue.

Fatal initialization errors should cause controlled shutdown.

## 6. Threading

The inital implementation should use a simple single-threaded processing model unless profiling demonstrates a need for concurrency.

Concurrency may be introduced later for:

- Packet capture
- Processing
- Alert output
- Database writes

Any future concurrent design must define ownership and synchronization explicitly.

## 7. Memory Ownership

Every dynamically allocated object must have a clearly defined owner.

Packet payload memory must not be referenced after the capture buffer becomes invalid unless explicitly copied.

Flow-table entries are owned by the flow table.

Detection events passed to asynchronous consumers must have well-defined lifetime semantics.

