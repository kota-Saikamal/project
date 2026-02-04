# File Inclusion Mitigation – Allowlist Validation

## Description
Allowlist validation restricts file inclusion to predefined, trusted files only.

## Example
- Allow only specific filenames such as:
  - home.php
  - about.php
  - contact.php

## Security Benefit
- Prevents directory traversal
- Blocks arbitrary file inclusion
- Eliminates LFI and RFI risks
