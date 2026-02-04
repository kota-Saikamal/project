# Local File Inclusion (LFI) – Attack Steps

## Target
DVWA – File Inclusion Module

## Steps
1. Login to DVWA.
2. Set DVWA security level to Low.
3. Navigate to File Inclusion page.
4. Observe the file parameter in the URL.
5. Modify the file parameter to include system files.
6. Submit the request.
7. Observe file contents rendered in the browser.

## Result
Sensitive local files were included and displayed by the application.
