# Threat Model

## Overview
This document defines the potential threats, attack scenarios, targets, and risks considered while designing the phishing simulation. The purpose is to create a realistic but controlled phishing scenario for educational and awareness evaluation.

## Assets (Targets)
- Test user email accounts
- Simulated login credentials (non-real)
- User interaction behavior data (clicks, opens, submissions)
- Email communication channel

## Threat Actors
- External attacker impersonating trusted services
- Social engineering attacker using phishing techniques

## Attack Vectors
- Phishing emails containing malicious links
- Fake login landing pages
- Urgent or persuasive messaging designed to trigger user action

## Threat Scenarios
- Credential harvesting via fake login page
- Link-click tracking for awareness measurement
- Email spoofing simulation

## Risk Assessment
- User susceptibility to phishing
- Lack of awareness about phishing indicators
- Trust in familiar branding or authority-based messaging

## Security Controls (Simulation Constraints)
- Controlled environment only
- Consent-based participants or test users
- No real credential storage or misuse
- Ethical and educational usage only

## Assumptions
- Participants understand this is a simulated environment.
- Infrastructure is isolated from production systems.
- Collected data is used only for analysis and reporting.

## Goals of Threat Modeling
- Design realistic phishing scenarios.
- Identify potential user risks.
- Support awareness improvement through analysis.
