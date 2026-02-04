# XSS Mitigation – Input Validation

## Technique
- Validate all user input on the server side.
- Reject unexpected characters and tags.
- Apply allowlist-based validation where possible.

## Example
- Allow only alphanumeric characters for usernames.
- Strip or encode HTML tags before storage or output.

## Impact
Reduces the possibility of malicious script injection.
