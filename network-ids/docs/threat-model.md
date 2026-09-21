# Threat Model

## Purpose

This document defines the threats the IDS is intended to detect and the limitations of the system.

## Assets

The system is intended to help monitor:

- Network services
- Internal network segments
- Servers
- Workstations
- Network infrastructure
- Network traffic metadata

## Threat Categories

### Reconnaissance

- TCP port scanning
- SYN scanning
- ICMP host sweeps
- UDP scanning

### Credential Attacks

- Repeated authentication attempts
- Brute-force behavior against network services

### Availability Attacks

- Packet floods
- SYN floods
- Excessive connection creation

### Anomalous Activity

- Unusual traffic rates
- Unusual destination diversity
- Unusual protocol distributions
- Unusual flow creation rates

## Assumptions

- The IDS can observe the relevant network traffic.
- Packet timestamps are sufficiently accurate.
- Network traffic is not intentionally hidden from the monitoring point.
- The host running the IDS is trusted.

## Limitations

The initial system does not provide:

- Endpoint malware detection
- Host-based intrusion detection
- Inline packet blocking
- Full payload inspection of encrypted traffic
- Guaranteed exploit identification
- Guaranteed attack attribution

## Security Boundaries

Network packets are untrusted input.

Configuration files are trusted administrative input.

Rule files are trusted administrative input.

Generated alerts must not be interpreted as proof of malicious intent without appropriate investigation.

## Failure Modes

The IDS may experience:

- Packet loss
- Capture-buffer overflow
- Parser rejection
- Flow-table exhaustion
- High CPU usage
- High memory usage
- Alert overload

The system should report operational failures separately from security detections.