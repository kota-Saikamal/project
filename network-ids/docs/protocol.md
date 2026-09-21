# Protocol Parsing Specification

## Supported Protocols

Initial protocol support:

    Ethernet II
       |
       +-- IPv4
       |    +-- TCP
       |    +-- UDP
       |    +-- ICMP
       |
       +-- IPv6
            +-- TCP
            +-- UDP
            +-- ICMPv6

DNS is parsed when carried over UDP or TCP.

## Ethernet

The parser must extract:

- Source MAC
- Destination MAC
- EtherType

Supported EtherTypes initially:

- IPv4
- IPv6

Unknown EtherTypes must be handled without crashing.

## IPv4

The parser must validate:

- Minimum header length
- IHL
- Total length
- Packet boundary
- Protocol field

The parser must extract:

- Source address
- Destination address
- TTL
- Protocol
- Total length
- Identification
- Fragmentation flags
- Fragment offset

## IPv6

The parser must extract:

- Source address
- Destination address
- Traffic class
- Flow label
- Payload length
- Next-header
- Hop limit

The parser must safely handle IPv6 extension headers.

## TCP

The parser must validate:

- Minimum TCP header length
- Data offset
- Packet boundary

The parser must extract:

- Source port
- Destination port
- Sequence number
- Acknowledgment number
- Flags
- Window size
- Payload length

TCP flags:

- FIN
- SYN
- RST
- PSH
- ACK
- URG
- ECE
- CWR

## UDP

The parser must validate:

- UDP header length
- UDP length
- Packet boundary

The parser must extract:

- Source port
- Destination port
- Length
- Payload

## ICMP

The parser must extract:

- Type
- Code
- Checksum

ICMP echo request/reply must be recognized.

## ICMPv6

The parser must recognize:

- Echo request
- Echo reply
- Neighbor discovery messages

Additional message types may be added later.

## DNS

DNS parsing initially focuses on metadata rather than complete semantic interpretation.

Extract:

- Transaction ID
- Flags
- Question count
- Answer count
- Query name
- Query type
- Query class

The parser must safely handle:

- Compressed names
- Truncated packets
- Invalid labels
- Excessive label lengths
- Out-of-bounds offsets

## Malformed Packets

Malformed packets must result in a parser error or ignored packet.

They must never cause:

- Buffer over-read
- Buffer over-write
- Use-after-free
- Undefined behavior
- Process termination

## Fragmentation

Fragment handling must be explicitly defined before detection logic relies on transport-layer information.

Initial policy:

- Track fragments safely.
- Do not attempt unsafe transport parsing when the required bytes are unavailable.