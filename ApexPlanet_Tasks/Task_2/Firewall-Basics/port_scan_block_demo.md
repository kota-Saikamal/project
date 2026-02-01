
# iptables Lab — Allow/Deny Ports and Block Port Scan

## Objective
- Create simple iptables rules to allow and deny specific ports
- Demonstrate how a port scan attempt can be blocked using iptables

---

## Environment
- OS: Kali Linux
- Firewall: iptables
- Testing tools: nc, nmap / hping3

---

## Step 1: Flush Existing Rules
```bash
sudo iptables -F
Purpose: Start with a clean firewall state.

Step 2: Set Default Policies
sudo iptables -P INPUT DROP
sudo iptables -P FORWARD DROP
sudo iptables -P OUTPUT ACCEPT
Purpose:

Block all incoming traffic by default

Allow outgoing traffic

Step 3: Allow Loopback Traffic
sudo iptables -A INPUT -i lo -j ACCEPT
Purpose: Allow internal system communication.

Step 4: Allow Established Connections
sudo iptables -A INPUT -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT
Purpose: Allow reply packets for outgoing connections.

Step 5: Allow Specific Ports
Allow SSH (Port 22)
sudo iptables -A INPUT -p tcp --dport 22 -j ACCEPT
Allow HTTP (Port 80)
sudo iptables -A INPUT -p tcp --dport 80 -j ACCEPT
Purpose: Permit essential services.

Step 6: Deny a Specific Port
Block FTP (Port 21)
sudo iptables -A INPUT -p tcp --dport 21 -j DROP
Purpose: Prevent access to FTP service.

Step 7: Demonstrate Port Scan Blocking
Block NULL Scan
sudo iptables -A INPUT -p tcp --tcp-flags ALL NONE -j DROP
Block XMAS Scan
sudo iptables -A INPUT -p tcp --tcp-flags ALL ALL -j DROP
Purpose: Drop stealth scan packets used by port scanners.

Step 8: Testing the Firewall
Test Blocked Port (FTP)
nc -zv 127.0.0.1 21
Expected Result: Connection timeout / blocked.

Test Allowed Port (HTTP)
nc -zv 127.0.0.1 80
Expected Result: Connection allowed (if service exists).

Port Scan Test
nmap -p 1-1000 127.0.0.1
Expected Result: Ports appear as filtered.

Step 9: Verify Rules
sudo iptables -L INPUT -v -n --line-numbers
Purpose: Confirm packets are being dropped or accepted.```
