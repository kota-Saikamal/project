## Steps to fuzzing using Intruder tool in Burpsuit


### 1. Configure Browser Proxy
- Set browser proxy:
  - IP: `127.0.0.1`
  - Port: `8080`
- Launch Burp Suite.

---

### 2. Enable Interception
- Open **Burp Suite**
- Navigate to **Proxy → Intercept**
- Turn **Intercept ON**

---

### 3. Setup PortSwigger Web Security Academy

1) Go to PortSwigger Web Security Academy

2) Open the lab named exactly: "SQL injection vulnerability in WHERE clause allowing retrieval of hidden data"

3) Click Access the lab
---

### 4. Trigger the vulnerable request

1) In lab page, click any product category (e.g. Gifts in my case)

2) This generates a request like:
    ```http
	GET /filter?category=Gifts HTTP/1.1
   ```
---

### 5. Send request to Intruder
1) In Proxy -> HTTP history
2) Locate the request 
```http
	GET /filter?category=Gifts
```
3) Right-click -> send to intruder
---

### 6.Configure Intruder positions (critical)
1) Go to Intruder -> Positions
2) Click Clear$ (mandatory)
3) Find this line:
```http
	category=Gifts
```
4) Highlight only:
```http
	Gifts
```
5) Click Add$

Result must be 
```http
category=$Gifts$
```
---

### 7 Select attack type
Still in Intruder -> Positions:
- Attack type: Sniper
Do not change anything else.
---

### 8 Add payloads (SQLi)
1) Go to intruder -> Payloads
2) Payload type: Simple list
3) Add these payloads exactly 
   - 'OR 1=1--
---

### 9 Start the attack
1) click start attack
2) Intruder window opens
3) Wait until all payloads are sent

---

### 10 analyze results
Look at the Length column 
What you will see
- ' OR 1=1-- larger response
---

### 11 Confirm in Repeater 
1) right-click the successful payload
2) send to repeater
3) Hit send
4) confirm response is consistent 


### Observation 
finally we can see in response in repeater and in render tab we can see all hidden products of the page