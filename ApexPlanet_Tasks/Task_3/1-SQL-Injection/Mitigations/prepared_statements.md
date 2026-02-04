# SQL Injection Mitigation – Prepared Statements

## Vulnerability Cause
The SQL Injection vulnerability occurs because user input is directly
concatenated into SQL queries without validation or parameterization.

Example of vulnerable query:
```php
$query = "SELECT * FROM users WHERE id = '$id'";
```
An attacker can inject SQL logic into the id parameter.

### Mitigation Technique: Prepared Statements

Prepared statements separate:

- SQL logic
- User-supplied data

This prevents user input from being interpreted as SQL code.

```
$stmt = $mysqli->prepare("SELECT * FROM users WHERE id = ?");
$stmt->bind_param("i", $id);
$stmt->execute();
$result = $stmt->get_result();
```

### Why This Works

Query is parsed before user input is applied

SQL injection payloads are neutralized

Database executes only intended logic

### Impact on DVWA

UNION-based SQL injection fails

Boolean and time-based injections fail

User input cannot modify query structure

### Conclusion

Prepared statements are the most effective and recommended defense
against SQL Injection vulnerabilities.