# Network IDS

A modular network intrusion detection system implemented primarily in C.

## Goals

The system will:

- Capture network packets from a live interface or PCAP file.
- Parse Ethernet, IPv4, IPv6, TCP, UDP, ICMP, ICMPv6, and DNS traffic.
- Track bidirectional network flows.
- Calculate packet, flow, and rate-based features.
- Detect network activity such as:
  - TCP/SYN port scans
  - ICMP sweeps
  - Brute-force behavior
  - Network floods
  - Statistical anomalies
- Correlate related detection events.
- Generate structured alerts.
- Store alerts for later analysis.
- Provide data to analysis, reporting, and dashboard components.

## Architecture

The processing pipeline is:

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

## Project Status

Initial development.

## Requirements

Target platform:

- Linux
- C compiler with C11 support
- libpcap
- POSIX-compatible environment
- Make

Optional components:

- Python 3
- Database engine
- Dashboard runtime

## Security Principles

The IDS must treat all network input as untrusted.

The implementation should:

- Validate packet lengths before reading fields.
- Validate protocol header lengths.
- Avoid buffer overflows.
- Avoid unsafe string operations.
- Handle malformed packets gracefully.
- Avoid crashing on corrupted traffic.
- Keep packet parsing separate from detection logic.

## Testing

Testing will include:

- Unit tests
- Integration tests
- Detection tests
- Reproducible PCAP traffic
- Malformed packet tests

## License

TBD