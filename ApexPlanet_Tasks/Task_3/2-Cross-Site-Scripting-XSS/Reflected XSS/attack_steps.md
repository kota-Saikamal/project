# Reflected Cross-Site Scripting (XSS) – Attack Steps

## Target
DVWA – Reflected XSS Module

## Steps
1. Login to DVWA.
2. Set DVWA security level to Low.
3. Navigate to Reflected XSS page.
4. Enter payload in the input field or URL parameter.
5. Submit the request.
6. Observe immediate JavaScript execution in the response.

## Result
Injected script was reflected in the response and executed in the browser.
