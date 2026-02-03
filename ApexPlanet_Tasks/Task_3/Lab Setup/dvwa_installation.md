# DVWA Installation Report

## System Information
- OS: Kali Linux
- Web Server: Apache2
- PHP Version: 8.x (Apache module)
- Database: MariaDB
- Application: DVWA (Damn Vulnerable Web Application)

## Installation Steps

1. Installed Apache
   ```bash
   sudo apt update
   sudo apt install apache2 -y

2. Installed PHP and required modules
   sudo apt install php libapache2-mod-php php-mysql -y
3. Installed MariaDB
   sudo apt install php libapache2-mod-php php-mysql -y
4. Started services 
   sudo systemctl start apache2
   sudo systemctl start MariaDB
5. Created DVWA database and user
   CREATE DATABASE dvwa;
   CREATE USER 'dvwa'@'127.0.0.1' IDENTIFIED BY 'p@ssw0rd';
   GRANT ALL PRIVILEGES ON dvwa.* TO 'dvwa'@'127.0.0.1';
   FLUSH PRIVILEGES;
6. Configured DVWA database settings
   cd /var/www/html/DVWA/config
   cp config.inc.php.dist config.inc.php
7. Fixed required permissions
   sudo chown -R www-data:www-data /var/www/html/DVWA
   sudo chmod 775 /var/www/html/DVWA/hackable/uploads
   sudo chmod 775 /var/www/html/DVWA/config
8. Completed setup
   Accessed: http://localhost/DVWA/setup.php
   Clicked: Create/Reset Database


