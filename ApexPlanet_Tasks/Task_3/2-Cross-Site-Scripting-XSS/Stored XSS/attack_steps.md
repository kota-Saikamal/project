# Stored Cross-Site Scripting (XSS) – Attack Steps

## Target
DVWA – Stored XSS Module

## Steps
1. Login to DVWA.
2. Set DVWA security level to Low.
3. Navigate to Stored XSS page.
4. Enter payload in the input field.
5. Submit the form.
6. Reload the page or revisit the stored content.
7. Observe JavaScript execution in the browser.

## Result
Injected script was stored on the server and executed whenever the page was loaded.
