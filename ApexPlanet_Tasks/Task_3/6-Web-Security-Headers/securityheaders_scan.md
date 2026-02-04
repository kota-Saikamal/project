# Security Headers Scan Report

## Tool Used
securityheaders.com (by Snyk)

## Target Site
https://portswigger.net/web-security

## Scan Details
- Scan Date: 03 Feb 2026
- Scan Time: 16:10:08 UTC
- IP Address: 18.66.171.50

## Overall Grade
**A**

---

## Implemented Security Headers (Present)

- Content-Security-Policy 
- Strict-Transport-Security (HSTS) 
- X-Content-Type-Options 
- X-Frame-Options 

---

## Missing / Not Implemented Headers

- Referrer-Policy 
- Permissions-Policy 

---

## Observations

- The website enforces strong transport security using HSTS.
- A Content Security Policy (CSP) is implemented, reducing XSS risk.
- Clickjacking protection is enabled via X-Frame-Options.
- MIME sniffing is disabled using X-Content-Type-Options.
- Referrer information is not explicitly controlled.
- Browser feature permissions are not restricted due to missing Permissions-Policy.

---

## Conclusion

The target site demonstrates **strong baseline security header implementation** and achieves an **A grade**.  
However, adding **Referrer-Policy** and **Permissions-Policy** headers would further harden the browser security posture and move closer to a fully comprehensive configuration.
