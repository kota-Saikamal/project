# XSS Mitigation – Content Security Policy (CSP)

## Purpose
Restrict the execution of scripts to trusted sources.

## Example Policy
Content-Security-Policy: default-src 'self';

## Effect
- Blocks inline JavaScript execution.
- Prevents loading scripts from untrusted domains.
