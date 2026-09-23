# Network IDS

A modular network intrusion detection system implemented primarily in C.

## Goals

The system is designed to:

* Capture network packets from a live interface or PCAP file.
* Parse Ethernet, IPv4, IPv6, TCP, UDP, ICMP, ICMPv6, and DNS traffic.
* Track bidirectional network flows.
* Calculate packet, flow, and rate-based features.
* Detect network activity such as:

  * TCP/SYN port scans
  * ICMP sweeps
  * Brute-force behavior
  * Network floods
  * Statistical anomalies
* Correlate related detection events.
* Generate structured alerts.
* Store alerts for later analysis.
* Provide data to analysis, reporting, and dashboard components.

## Architecture

The planned processing pipeline is:

```text
Capture
   ↓
Parsing
   ↓
Flow Tracking
   ↓
Feature Extraction
   ↓
Detection
   ↓
Correlation
   ↓
Alerting
   ↓
Storage / Analysis / Dashboard
```

The current implementation is focused on the **Capture and Parsing** stages.

### Current Parsing Pipeline

```text
Raw Packet
    ↓
Ethernet
    ↓
EtherType
    ├── IPv4
    │    └── Protocol
    │         ├── TCP
    │         ├── UDP
    │         └── ICMP
    │
    └── IPv6
         └── Next Header
              ├── TCP
              ├── UDP
              └── ICMPv6
```

The parser uses protocol-specific modules and validates packet/header lengths before accessing protocol fields.

## Current Project Status

**Stage: Initial packet capture and protocol parsing**

Currently implemented:

* Live packet capture using `libpcap`
* Graceful capture termination using `SIGINT`
* Ethernet II parsing
* EtherType identification
* IPv4 parsing
* IPv6 base-header parsing
* TCP parsing
* UDP parsing
* ICMP data structures
* ICMPv6 data structures
* Transport protocol dispatch
* Network-byte-order conversion using `ntohs()` / `ntohl()`
* Basic malformed/truncated packet validation

The current parser handles:

```text
Ethernet
├── IPv4
│   ├── TCP
│   ├── UDP
│   └── ICMP
└── IPv6
    ├── TCP
    ├── UDP
    └── ICMPv6
```

### Currently Under Development

The following components are planned but are not yet fully implemented:

* Complete ICMP/ICMPv6 parsing
* IPv6 extension-header processing
* DNS parsing
* Bidirectional flow tracking
* Feature extraction
* Detection engine
* Detection rules
* Event correlation
* Alert generation
* Alert storage
* Python analysis
* Database integration
* Dashboard/API
* Comprehensive automated testing

## Project Structure

```text
network-ids/
├── src/
│   ├── main.c
│   ├── capture/
│   │   ├── capture.c
│   │   └── capture.h
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
│   │   ├── icmp.h
│   │   ├── icmpv6.c
│   │   └── icmpv6.h
│   ├── flow/
│   ├── feature/
│   ├── detection/
│   ├── correlation/
│   ├── alert/
│   ├── config/
│   └── common/
├── include/
│   └── ids_types.h
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

## Requirements

### Target Platform

* Linux
* C compiler with C11 support
* `libpcap`
* POSIX-compatible environment
* Make

### Optional Components

* Python 3
* Database engine
* Dashboard runtime

## Build

The project uses a Makefile for compilation.

```bash
make
```

For a debug build with AddressSanitizer and UndefinedBehaviorSanitizer:

```bash
make debug
```

Clean build artifacts:

```bash
make clean
```

## Running

Live capture requires appropriate privileges.

Example:

```bash
sudo ./network-ids
```

The capture layer currently accepts a network interface and uses `libpcap` to retrieve packets.

## Packet Parsing

Captured packets are passed from the capture layer to the parser.

The parser first processes the Ethernet header and determines the network-layer protocol using EtherType.

Supported EtherTypes currently include:

```text
0x0800  IPv4
0x86DD  IPv6
```

The network-layer parser then determines the transport protocol using the IPv4 Protocol field or IPv6 Next Header field.

Relevant protocol numbers include:

```text
IPv4 Protocol / IPv6 Next Header

1    ICMP
6    TCP
17   UDP
58   ICMPv6
```

Protocol-specific parsers extract fields into strongly typed C structures defined in:

```text
include/ids_types.h
```

## Security Principles

The IDS treats all network input as untrusted.

The implementation should:

* Validate packet lengths before reading fields.
* Validate protocol header lengths.
* Validate protocol-specific length fields.
* Avoid buffer overflows.
* Avoid unsafe string operations.
* Handle malformed and truncated packets gracefully.
* Avoid crashing on corrupted traffic.
* Keep packet parsing separate from detection logic.
* Avoid assuming that captured packets are well formed.

## Testing

Testing will include:

* Unit tests
* Integration tests
* Detection tests
* Reproducible PCAP traffic
* Malformed packet tests
* Live traffic testing

Example traffic currently useful for parser testing includes:

```bash
ping 8.8.8.8
curl https://example.com
nslookup example.com
dig example.com
```

PCAP-based testing will eventually be organized under:

```text
tests/pcaps/
├── normal/
├── scans/
├── floods/
└── brute_force/
```

## Development Roadmap

### Phase 1 — Packet Capture and Parsing

* [x] Live packet capture
* [x] Ethernet parsing
* [x] IPv4 parsing
* [x] IPv6 base-header parsing
* [x] TCP parsing
* [x] UDP parsing
* [ ] Complete ICMP parsing
* [ ] Complete ICMPv6 parsing
* [ ] DNS parsing
* [ ] IPv6 extension-header parsing

### Phase 2 — Flow Tracking

* [ ] Flow keys
* [ ] Bidirectional flow tracking
* [ ] Flow table
* [ ] Flow expiration
* [ ] Flow statistics

### Phase 3 — Feature Extraction

* [ ] Packet-level features
* [ ] Flow-level features
* [ ] Rate-based features
* [ ] Host-level statistics

### Phase 4 — Detection

* [ ] TCP/SYN port scan detection
* [ ] ICMP sweep detection
* [ ] SYN flood detection
* [ ] UDP flood detection
* [ ] Brute-force detection
* [ ] Statistical anomaly detection

### Phase 5 — Correlation and Alerting

* [ ] Detection event correlation
* [ ] Severity classification
* [ ] Confidence scoring
* [ ] Structured alerts
* [ ] JSON output
* [ ] File output

### Phase 6 — Analysis and Visualization

* [ ] Python analysis
* [ ] Statistical reports
* [ ] Database storage
* [ ] API
* [ ] Dashboard

## License

TBD
