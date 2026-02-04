# HTTP Security Headers – Before and After Results

## Target
Apache Web Server (Local Test Site)

---

## BEFORE Hardening

### HTTP Response Headers
```
HTTP/1.1 200 OK
Date: Tue, 03 Feb 2026 16:14:31 GMT
Server: Apache/2.4.66 (Debian)
Last-Modified: Mon, 02 Feb 2026 12:19:46 GMT
ETag: "29cf-649d56ace158"
Accept-Ranges: bytes
Content-Length: 10703
Vary: Accept-Encoding
Content-Type: text/html
```

### Missing Security Headers
- Content-Security-Policy
- X-Frame-Options
- X-Content-Type-Options
- Referrer-Policy

---

## AFTER Hardening

### HTTP Response Headers
```
HTTP/1.1 200 OK
Date: Tue, 03 Feb 2026 16:14:31 GMT
Server: Apache/2.4.66 (Debian)
X-Content-Type-Options: nosniff
X-Frame-Options: DENY
Referrer-Policy: strict-origin-when-cross-origin
Content-Security-Policy: default-src 'self'
Last-Modified: Mon, 02 Feb 2026 12:19:46 GMT
ETag: "29cf-649d56ace158"
Accept-Ranges: bytes
Content-Length: 10703
Vary: Accept-Encoding
Content-Type: text/html
```

### Added Security Headers
- X-Content-Type-Options: nosniff
- X-Frame-Options: DENY
- Referrer-Policy: strict-origin-when-cross-origin
- Content-Security-Policy: default-src 'self'

---

## Final Result

HTTP security headers were successfully added at the Apache server level, enforcing browser-side security policies for all responses.
