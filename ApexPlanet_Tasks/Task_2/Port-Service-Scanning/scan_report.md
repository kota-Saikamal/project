# Nmap Scan Report

## Target Information
- **Target Name:** Metasploitable2
- **IP Address:** 192.168.56.108
- **Environment:** Local lab (Kali Linux → Metasploitable2)

---

## Scan Objective
To identify live hosts, open ports, running services, and operating system details on the target system using Nmap.

---

## Scan Types Performed

### 1. Ping Sweep
**Command Used:** netdiscover


 Currently scanning: 192.168.0.0/16   |   Screen View: Unique Hosts                                               
                                                                                                                  
 3 Captured ARP Req/Rep packets, from 3 hosts.   Total size: 180                                                  
 _____________________________________________________________________________
   IP            At MAC Address     Count     Len  MAC Vendor / Hostname      
 -----------------------------------------------------------------------------
 192.168.56.1    0a:00:27:00:00:0a      1      60  Unknown vendor                                                 
 192.168.56.100  08:00:27:80:38:fa      1      60  PCS Systemtechnik GmbH                                         
 192.168.56.108  08:00:27:0e:ac:a3      1      60  PCS Systemtechnik GmbH


**Result:**
- Target host was reachable and responding to ICMP requests.
---

### 2. TCP SYN Scan
**Command Used:**nmap -sS 192.168.56.108

Starting Nmap 7.95 ( https://nmap.org ) at 2026-01-28 20:57 IST
Nmap scan report for 192.168.56.108
Host is up (0.025s latency).
Not shown: 989 open|filtered udp ports (no-response), 977 closed tcp ports (reset), 7 closed udp ports (port-unreach)
PORT     STATE SERVICE
21/tcp   open  ftp
22/tcp   open  ssh
23/tcp   open  telnet
25/tcp   open  smtp
53/tcp   open  domain
80/tcp   open  http
111/tcp  open  rpcbind
139/tcp  open  netbios-ssn
445/tcp  open  microsoft-ds
512/tcp  open  exec
513/tcp  open  login
514/tcp  open  shell
1099/tcp open  rmiregistry
1524/tcp open  ingreslock
2049/tcp open  nfs
2121/tcp open  ccproxy-ftp
3306/tcp open  mysql
5432/tcp open  postgresql
5900/tcp open  vnc
6000/tcp open  X11
6667/tcp open  irc
8009/tcp open  ajp13
8180/tcp open  unknown

**Key Findings:**
- Multiple TCP ports found open
- Services such as FTP, SSH, HTTP detected

---

### 3. UDP Scan
**Command Used:** nmap -sS -sU 192.168.56.108
Starting Nmap 7.95 ( https://nmap.org ) at 2026-01-28 20:57 IST
Nmap scan report for 192.168.56.108
Host is up (0.025s latency).
Not shown: 989 open|filtered udp ports (no-response), 977 closed tcp ports (reset), 7 closed udp ports (port-unreach)
PORT     STATE SERVICE
21/tcp   open  ftp
22/tcp   open  ssh
23/tcp   open  telnet
25/tcp   open  smtp
53/tcp   open  domain
80/tcp   open  http
111/tcp  open  rpcbind
139/tcp  open  netbios-ssn
445/tcp  open  microsoft-ds
512/tcp  open  exec
513/tcp  open  login
514/tcp  open  shell
1099/tcp open  rmiregistry
1524/tcp open  ingreslock
2049/tcp open  nfs
2121/tcp open  ccproxy-ftp
3306/tcp open  mysql
5432/tcp open  postgresql
5900/tcp open  vnc
6000/tcp open  X11
6667/tcp open  irc
8009/tcp open  ajp13
8180/tcp open  unknown
53/udp   open  domain
111/udp  open  rpcbind
137/udp  open  netbios-ns
2049/udp open  nfs
MAC Address: 08:00:27:0E:AC:A3 (PCS Systemtechnik/Oracle VirtualBox virtual NIC)

Nmap done: 1 IP address (1 host up) scanned in 20.62 seconds


**Key Findings:**
- UDP services identified on common ports
- Potential exposure of legacy services

---

### 4. Service Version Detection
**Command Used:**nmap -sV 192.168.56.108
Starting Nmap 7.95 ( https://nmap.org ) at 2026-01-28 20:31 IST
Stats: 0:00:02 elapsed; 0 hosts completed (0 up), 1 undergoing ARP Ping Scan
Parallel DNS resolution of 1 host. Timing: About 0.00% done
Stats: 0:00:05 elapsed; 0 hosts completed (0 up), 1 undergoing ARP Ping Scan
Parallel DNS resolution of 1 host. Timing: About 0.00% done
Stats: 0:00:13 elapsed; 0 hosts completed (0 up), 1 undergoing ARP Ping Scan
Parallel DNS resolution of 1 host. Timing: About 0.00% done
Stats: 0:00:22 elapsed; 0 hosts completed (1 up), 1 undergoing Service Scan
Service scan Timing: About 43.48% done; ETC: 20:32 (0:00:08 remaining)
Nmap scan report for 192.168.56.108
Host is up (0.014s latency).
Not shown: 977 closed tcp ports (reset)
PORT     STATE SERVICE      VERSION
21/tcp   open  ftp          vsftpd 2.3.4
22/tcp   open  ssh          OpenSSH 4.7p1 Debian 8ubuntu1 (protocol 2.0)
23/tcp   open  telnet       Linux telnetd
25/tcp   open  smtp         Postfix smtpd
53/tcp   open  domain       ISC BIND 9.4.2
80/tcp   open  http         Apache httpd 2.2.8 ((Ubuntu) DAV/2)
111/tcp  open  rpcbind      2 (RPC #100000)
139/tcp  open  netbios-ssn  Samba smbd 3.X - 4.X (workgroup: WORKGROUP)
445/tcp  open  netbios-ssn  Samba smbd 3.X - 4.X (workgroup: WORKGROUP)
512/tcp  open  exec         netkit-rsh rexecd
513/tcp  open  login        OpenBSD or Solaris rlogind
514/tcp  open  shell        Netkit rshd
1099/tcp open  java-rmi     GNU Classpath grmiregistry
1524/tcp open  bindshell    Metasploitable root shell
2049/tcp open  nfs          2-4 (RPC #100003)
2121/tcp open  ccproxy-ftp?
3306/tcp open  mysql        MySQL 5.0.51a-3ubuntu5
5432/tcp open  postgresql   PostgreSQL DB 8.3.0 - 8.3.7
5900/tcp open  vnc          VNC (protocol 3.3)
6000/tcp open  X11          (access denied)
6667/tcp open  irc          UnrealIRCd
8009/tcp open  ajp13        Apache Jserv (Protocol v1.3)
8180/tcp open  http         Apache Tomcat/Coyote JSP engine 1.1
MAC Address: 08:00:27:0E:AC:A3 (PCS Systemtechnik/Oracle VirtualBox virtual NIC)
Service Info: Hosts:  metasploitable.localdomain, irc.Metasploitable.LAN; OSs: Unix, Linux; CPE: cpe:/o:linux:linux_kernel

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 178.57 second


**Key Findings:**
- Outdated service versions detected
- Services running with known vulnerabilities

---

### 5. OS Detection
**Command Used:** nmap -O 192.168.56.108
Starting Nmap 7.95 ( https://nmap.org ) at 2026-01-28 20:39 IST
Nmap scan report for 192.168.56.108
Host is up (0.022s latency).
Not shown: 977 closed tcp ports (reset)
PORT     STATE SERVICE
21/tcp   open  ftp
22/tcp   open  ssh
23/tcp   open  telnet
25/tcp   open  smtp
53/tcp   open  domain
80/tcp   open  http
111/tcp  open  rpcbind
139/tcp  open  netbios-ssn
445/tcp  open  microsoft-ds
512/tcp  open  exec
513/tcp  open  login
514/tcp  open  shell
1099/tcp open  rmiregistry
1524/tcp open  ingreslock
2049/tcp open  nfs
2121/tcp open  ccproxy-ftp
3306/tcp open  mysql
5432/tcp open  postgresql
5900/tcp open  vnc
6000/tcp open  X11
6667/tcp open  irc
8009/tcp open  ajp13
8180/tcp open  unknown
MAC Address: 08:00:27:0E:AC:A3 (PCS Systemtechnik/Oracle VirtualBox virtual NIC)
Device type: general purpose
Running: Linux 2.6.X
OS CPE: cpe:/o:linux:linux_kernel:2.6
OS details: Linux 2.6.9 - 2.6.33
Network Distance: 1 hop

OS detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 15.89 seconds


**Key Findings:**
- Target operating system fingerprinted successfully
- OS identified as a Linux-based system

---

## Security Observations
- Presence of multiple open and unnecessary ports increases attack surface
- Outdated services may be vulnerable to known exploits
- Lack of proper service hardening observed

---

## Conclusion
The Nmap scans revealed that the target system exposes several open ports and outdated services, making it vulnerable to further exploitation. These findings were used as input for vulnerability scanning using OpenVAS.

---
