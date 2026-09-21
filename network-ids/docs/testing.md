# Testing

## Purpose

Define how the Network IDS is verified for correctness, reliability, security, and detection accuracy.

## Testing Levels

### Unit Tests

Test individual modules independently.

Examples:

- Ethernet parsing
- IPv4 parsing
- IPv6 parsing
- TCP parsing
- UDP parsing
- Flow creation
- Flow updates
- Feature calculations
- Hashmap operations
- Queue operations

### Integration Tests

Verify communication between modules.

Examples:

- Capture → Parser
- Parser → Flow
- Flow → Features
- Features → Detection
- Detection → Correlation
- Detection → Alert

### Detection Tests

Verify that known traffic patterns produce the expected detection events.

Initial detection tests:

- Port scan
- SYN scan
- ICMP sweep
- SYN flood
- UDP flood
- Brute force
- Anomaly

### PCAP Tests

Use reproducible PCAP files stored under:

    tests/pcaps/

Categories:

- normal/
- scans/
- floods/
- brute_force/

PCAP replay must produce predictable detection results.

### Malformed Packet Tests

The parser must safely handle:

- Truncated packets
- Invalid Ethernet headers
- Invalid IP headers
- Invalid TCP headers
- Invalid UDP lengths
- Invalid ICMP packets
- Invalid IPv6 extension headers

Malformed input must not crash the IDS.

### Regression Tests

Previously fixed bugs must have corresponding tests.

Every significant bug fix should add or update a test.

## Debug Testing

Use sanitizers during development:

    make debug

AddressSanitizer and UndefinedBehaviorSanitizer should be used to detect memory and undefined-behavior problems.

## Test Requirements

A test should provide:

1. Input
2. Expected behavior
3. Actual behavior
4. Pass/fail result

## Testing Goal

The IDS must correctly process valid traffic, safely reject malformed traffic, and produce reproducible detection results.