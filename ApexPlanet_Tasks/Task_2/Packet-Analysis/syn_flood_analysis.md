# SYN Flood Attack Analysis

## Objective

To simulate and analyze a TCP SYN flood attack and observe its impact on TCP connection establishment using packet-level analysis in Wireshark.

### Environment

Attacker Machine: Kali Linux

Target Machine: Test server / VM (HTTP service on port 80)

Network Mode: Bridged

Tools Used: hping3, Wireshark

### Attack Simulation

The SYN flood attack was generated using the following command:

sudo hping3 -S -p 80 --flood <target-ip>


Explanation:

-S sends TCP SYN packets.

--flood sends packets as fast as possible.

The attack attempts to exhaust the target’s connection table by creating half-open TCP connections.

### Packet Capture and Filtering

Wireshark was used to capture traffic during the attack.

Display Filter Used:

tcp.flags.syn == 1 && tcp.flags.ack == 0


This filter isolates TCP SYN packets that do not complete the handshake.

### Observations

A large volume of TCP SYN packets was observed within a short time interval.

Most SYN packets did not receive corresponding ACK packets.

The TCP three-way handshake remained incomplete, resulting in half-open connections.

The packet rate was significantly higher than normal network behavior.

### Impact Analysis

Excessive half-open connections can exhaust server resources.

Legitimate client connections may be delayed or dropped.

The attack demonstrates how TCP’s connection-oriented design can be abused.

### Detection Indicators

High frequency of SYN packets from a single source.

Incomplete TCP handshakes.

Abnormal increase in connection attempts without session completion.

### Conclusion

The SYN flood attack successfully demonstrated a Denial-of-Service condition by exploiting the TCP handshake mechanism. Packet analysis confirmed the presence of half-open connections, validating the effectiveness of the attack simulation.