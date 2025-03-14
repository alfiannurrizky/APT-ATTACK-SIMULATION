# APT Simulator Project

## Introduction

This project is an **Advanced Persistent Threat (APT) Simulator** designed for **educational and security research purposes**. It replicates the attack chain of a real-world APT, from **initial phishing** to **document exfiltration** and **persistence mechanisms**.

**⚠ Disclaimer:** This project is strictly for **educational** and **research** purposes. Running these scripts outside a controlled environment is illegal.

---

## Architecture

The attack follows these stages:

1. **Phishing Attack** – A **Word document (DOCX)** containing a fake job description and a **malicious link**.
2. **HTML Smuggling** – When the link is clicked, it downloads `dropper.exe` without raising suspicion.
3. **Execution of Dropper** – When executed, the dropper:
   - **Downloads & executes a shellcode (reverse shell)** from the attacker's server.
   - **Executes a PowerShell script for persistence & data exfiltration**.
4. **Data Exfiltration** – The PowerShell script collects **document files** (`.txt`, `.pdf`, `.xlsx`, etc.) and uploads them to the attacker's PHP web server.
5. **Persistence** – Hijacks file associations to maintain access.

---

## Components

### 1. **Dropper (C Language)**

- Downloads and executes shellcode (reverse shell) from an external server.

### 2. **PowerShell Script**

- Searches for **sensitive documents** on the victim's machine.
- Uploads collected files to the attacker's server.
- Implements **persistence** using **Hijacking File Associations**.

### 3. **HTML Smuggling Page**

- Designed to **silently download** the dropper when opened in a browser.

### 4. **Phishing Document (DOCX)**

- A fake **job portal description** that tricks users into clicking the HTML Smuggling link.

### 5. **PHP Web Server**

- Acts as a **C2 server** to receive exfiltrated documents.

---

## Installation & Setup

### **1. Virtual Environment**

To ensure safety, run the simulator inside **VirtualBox** with:

- **1x Windows VM (Target)** – Victim machine.
- **1x Linux VM (Attacker)** – Hosting the C2 server & shellcode.

### **2. Setting Up the Web Server**

1. Install Apache & PHP on Linux:
   ```bash
   sudo apt update && sudo apt install apache2 php -y
   sudo systemctl start apache2
   sudo systemctl enable apache2
   ```
2. Deploy the PHP upload server:
   - Copy `index.php` to `/var/www/html/upload/`
   - Ensure `/upload/` directory has write permissions.

### **3. Running the Attack**

1. Send the phishing **DOCX** to the target.
2. Wait for the victim to click the link.
3. The dropper gets executed.
4. Reverse shell is established & documents get uploaded.

---

## Security & Ethical Considerations

- This project is meant for **ethical hacking**, **cybersecurity training**, and **malware research**.
- Never deploy this outside a **controlled lab environment**.
- Ensure all VMs are **isolated from real networks**.

---

## Future Improvements

- Implement **better encryption** for exfiltrated data.
- Enhance **stealth techniques** to bypass AV detections.

If you have suggestions or improvements, feel free to contribute! 🚀
