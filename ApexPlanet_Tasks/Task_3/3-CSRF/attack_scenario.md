# CSRF Attack Scenario

## Target
DVWA – CSRF Module

## Scenario
An authenticated user is logged into the DVWA application. An attacker tricks the user into visiting a malicious webpage that silently sends a forged request to the DVWA server.

## Steps
1. Victim logs into DVWA.
2. Victim remains authenticated (active session).
3. Victim visits attacker-controlled page.
4. Malicious page sends a crafted request to DVWA.
5. Server processes the request as if it came from the victim.

## Impact
- Password change without user consent
- Account takeover risk
- Unauthorized actions performed
