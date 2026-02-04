# Remote File Inclusion (RFI) – Attack Steps

## Target
DVWA – File Inclusion Module

## Steps
1. Login to DVWA.
2. Set DVWA security level to Low.
3. Navigate to File Inclusion page.
4. Host a malicious PHP file on an attacker-controlled server.
5. Supply the remote file URL as the file parameter.
6. Submit the request.
7. Observe remote code execution on the server.

## Result
Remote PHP code was executed on the vulnerable server.
