# Detection Specification

## Detection Model

Detectors consume normalized packets, flows, and/or features.

Detectors produce:

    detection_event_t

Detectors must not directly generate output files.

## Severity

Severity levels:

    0 = informational
    1 = low
    2 = medium
    3 = high
    4 = critical

Severity describes the configured significance of the detection and is not a probability.

## Port Scan

A port scan detector evaluates repeated connection attempts involving multiple destination ports.

Possible features:

- Unique destination ports
- Connection attempts
- SYN count
- Failed connections
- Time window
- Destination host count

Thresholds must be configurable.

## SYN Scan

A SYN scan detector focuses on repeated TCP SYN packets without corresponding completed connections.

Possible indicators:

- High SYN rate
- Many destination ports
- Low ACK completion rate
- Short observation window

## ICMP Sweep

An ICMP sweep detector identifies repeated ICMP echo requests directed toward multiple hosts.

Possible indicators:

- Source host
- Number of destination hosts
- Observation window
- Echo request count

## Brute Force

The brute-force detector identifies repeated authentication attempts.

The initial implementation should rely on network-visible indicators rather than attempting to inspect encrypted credentials.

Possible indicators:

- Repeated connections
- Same source
- Same destination
- Authentication-service port
- Failure-related application metadata where available
- Connection rate

## Flood

The flood detector identifies unusually high packet or byte rates.

Possible indicators:

- Packets per second
- Bytes per second
- SYN rate
- Destination concentration
- Source concentration

## Anomaly

The anomaly detector identifies statistically unusual behavior.

Initial implementation should be deterministic and configurable.

Potential features:

- Packet rate
- Byte rate
- Unique destinations
- Unique ports
- Protocol distribution
- Flow creation rate

Machine-learning detection is a later phase.

## Detection Event

Every detector must produce a normalized event containing:

- Detection type
- Severity
- Timestamp
- Source
- Destination
- Protocol
- Confidence if applicable
- Human-readable description

## False Positives

Detection thresholds must be configurable.

Detectors should avoid generating repeated identical alerts for the same underlying activity.

Correlation and alert suppression are responsible for reducing duplicate notifications.

## Rule Configuration

Detection thresholds should be loaded from the rules directory.

Hard-coded detection thresholds should be avoided.