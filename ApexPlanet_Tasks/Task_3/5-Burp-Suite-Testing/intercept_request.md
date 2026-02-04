## Steps to Intercept and Modify  Request

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

### 3. Submit Login Request 
- Open the browser
- Enter your desired content
- Click **enter**
---

### 4. Intercepted HTTP Request (Before Modification)

```http
GET /search?client=firefox-b-e&channel=entpr&q=Man+in+the+middle HTTP/1.1
Host: www.google.com
Cookie:
User-Agent:
....
```

### 5. modify Path
&q=Child+play

### 6. Forward Modified Request
- click Forward in burpsuite

Observation 
- final result in firefox was about Child play instead of Man in the middle

