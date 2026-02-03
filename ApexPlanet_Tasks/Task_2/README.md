# Network Security Assessment & Traffic Analysis

## Objective
To perform an end-to-end network security assessment by conducting reconnaissance, port and service scanning, vulnerability analysis, network traffic inspection, and basic firewall defense in a controlled lab environment.

---

## Lab Environment
- **Attacker Machine:** Kali Linux  
- **Target Machine:** Metasploitable2  
- **Network Type:** Host-only / Internal lab network  

---

## Scope & Authorization
- All testing was performed **only on intentionally vulnerable systems**.
- No real-world or unauthorized targets were tested.
- Activities were conducted strictly for **educational and research purposes**.

---

## Methodology

### 1. Reconnaissance
- Passive reconnaissance using Whois, Nslookup, Google Dorking, and Shodan.
- Active reconnaissance using ping sweeps and banner grabbing.

### 2. Port & Service Scanning
- TCP SYN scan and UDP scan using Nmap.
- Service version detection and OS fingerprinting.

### 3. Vulnerability Scanning
- Vulnerability assessment performed using OpenVAS / Nessus Essentials.
- Analysis of vulnerabilities based on severity (Critical, High, Medium, Low).

### 4. Network Traffic Analysis
- Captured HTTP, FTP, and DNS traffic using Wireshark.
- Identified plaintext credentials transmitted over unencrypted FTP.
- Simulated and analyzed a SYN flood attack using hping3.

### 5. Firewall Defense
- Implemented iptables rules to allow and deny specific ports.
- Demonstrated blocking of port scan attempts.

---

## Tools & Technologies
- Nmap  
- Wireshark  
- OpenVAS / Nessus Essentials  
- hping3  
- iptables  
- Whois  
- Nslookup  
- Shodan  

---

## Key Outcomes
- Identified exposed services and vulnerable configurations on the target system.
- Analyzed insecure network protocols and demonstrated credential leakage risks.
- Gained hands-on experience in offensive and defensive network security techniques.
- Created structured scan and vulnerability reports with mitigation recommendations.

---

## Repository Structure
Task_2/
├── README.md
├── 1-Reconnaissance/
│   ├── Passive/
│   │   ├── whois.txt
│   │   ├── nslookup.txt
│   │   ├── google_dorks.txt
│   │   └── shodan.txt
│   │   └── dig.txt
│   │   └── Screenshots/
│   └── Active/
│       ├── ping_sweep.txt
│       ├── banner_grabbing.txt
│       └── Screenshots/
├── 2-Port-Service-Scanning/
│   ├── nmap_tcp_scan.txt
│   ├── nmap_udp_scan.txt
│   ├── service_version.txt
│   ├── os_detection.txt
│   ├── scan_report.md
│   └── Screenshots/
├── 3-Vulnerability-Scanning/
│   ├── openvas_report.pdf
│   ├── vulnerability_analysis.md
│   └── Screenshots/
├── 4-Packet-Analysis/
│   ├── pcaps/
│   │   ├── http.pcap
│   │   ├── ftp_credentials.pcap
│   │   └── dns.pcap
│   ├── wireshark_filters.txt
│   ├── syn_flood_analysis.md
│   └── Screenshots/
├── 5-Firewall-Basics/
│   ├── port_scan_block_demo.md
│   └── Screenshots/
├── Tools-Used.txt
└── Payloads/
    ├── recon_commands.txt
    ├── nmap_commands.txt
    ├── hping3_commands.txt
    └── iptables_commands.txt
