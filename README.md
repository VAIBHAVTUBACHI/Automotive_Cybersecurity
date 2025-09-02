# Automotive Cybersecurity

This repository focuses on enhancing cybersecurity within automotive systems, particularly in Electronic Control Units (ECUs). The main goal is to secure the communication and software integrity in these systems to prevent unauthorized access and tampering.

## Features

* **Secure Flashing**: Verifies the integrity of firmware before flashing to ensure that only authenticated software is installed on the ECU.
* **Secure Onboard Communication (SecOC)**: Implements secure communication protocols to protect data exchanged between ECUs in automotive systems.
* **Cryptographic Hashing**: Utilizes SHA256 hashing to validate software authenticity and secure communication channels.
* **Tamper Detection**: Identifies and prevents unauthorized changes to software and data during transmission.

## Files

* `Secure_flash.c`: Implements secure flashing with SHA256 verification to ensure the integrity of firmware before flashing.
* `SecOc.c`: Implements Secure Onboard Communication (SecOC) to ensure secure communication between ECUs.
* `SecOc_README.txt`: Provides documentation and details for the implementation of SecOC.
* `Secure_Flash_README.txt`: Provides documentation for the secure flashing implementation.

## Requirements

* **OpenSSL**: Required for cryptographic operations, specifically for hashing and securing communications.
* **C Compiler**: A C compiler that supports OpenSSL is needed to compile and run the code.

## Usage

1. **Install OpenSSL**:

   * **Windows**:

     * Download the OpenSSL installer from the [official OpenSSL website](https://slproweb.com/products/Win32OpenSSL.html).
     * Install OpenSSL using the installer, and make sure to add OpenSSL to your system's PATH during the installation process.
     * After installation, verify that OpenSSL is working by running `openssl version` in your command prompt.

2. **Compile the code**:

   ```bash
   gcc -o secure_flash Secure_flash.c -lssl -lcrypto
   ```

3. **Run the program**:

   ```bash
   ./secure_flash
   ```
---

Feel free to modify the code as needed to suit your specific automotive cybersecurity needs. Stay secure!

---
