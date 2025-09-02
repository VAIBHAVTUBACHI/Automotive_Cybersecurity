
==============================================================
                      Secure CMAC with Freshness Value
==============================================================

This repository contains a C implementation of a secure message 
authentication code (CMAC) generation and verification process 
using the OpenSSL 3.0 EVP_MAC API. The CMAC generation includes 
a Freshness Value (FV) to enhance security by preventing replay 
attacks.

==============================================================
                         Features
==============================================================

→ **CMAC Generation**: Uses AES-128-CBC cipher to generate the CMAC.

→ **CMAC Verification**: Verifies the integrity of the received message.

→ **Freshness Value (FV)**: Implements a monotonic counter (FV) to prevent replay attacks.

→ **OpenSSL 3.0**: The implementation uses the OpenSSL 3.0 EVP_MAC API for cryptographic operations.

==============================================================
                        Files Overview
==============================================================

→ **SecOc.c**: The main C file that includes functions for CMAC 
  generation, verification, and Freshness Value (FV) management.

    → `GenerateCMAC`: Generates the CMAC using AES-128-CBC and Freshness Value.

    → `VerifyCMAC`: Verifies the integrity of the CMAC against the received message.

    → `generateFV`: Increments the Freshness Value (monotonic counter).

    → `verifyFV`: Verifies if the received Freshness Value is valid and hasn't been tampered with.

==============================================================
                         Dependencies
==============================================================

→ **OpenSSL 3.0**: This code relies on the OpenSSL 3.0 libraries for cryptographic operations. 
  Ensure that OpenSSL is properly installed and linked during the build process.

==============================================================
                    Compilation Instructions
==============================================================

To compile the code, ensure you have the OpenSSL development libraries installed on your system. 
You can install OpenSSL using the following command:

```bash
sudo apt-get install libssl-dev
```

To compile the code, run:

```bash
gcc SecOc.c -o SecOc -lssl -lcrypto
```

==============================================================
                           Usage
==============================================================

1. **Run the Program**: After compiling, run the executable:

```bash
./SecOc
```

2. **Program Output**: The program will generate and verify a CMAC for a predefined payload (`AUTOSAR_SECURE_PAYLOAD`) and display the Freshness Value (FV) along with the CMAC.

Example output:

```bash
Generated CMAC: 97A8A4F5B51F8D3BFC463F22D4A95BBF
Freshness value is  1
CMAC verification ✅ successful
```

3. **Tampered Payload Verification**: If the payload is tampered, the verification will fail.

Example output for a tampered payload:

```bash
Generated CMAC: 97A8A4F5B51F8D3BFC463F22D4A95BBF
Freshness value is  1
CMAC verification ❌ failed
```

==============================================================
                         Functions
==============================================================

→ **`GenerateCMAC`**: Takes a key, data, and generates the CMAC. It prepends the Freshness Value to the data before calculating the MAC.

→ **`VerifyCMAC`**: Verifies the CMAC by recalculating the expected MAC and comparing it with the received MAC.

→ **`generateFV`**: Increments the Freshness Value (FV) to ensure it is unique and not reused.

→ **`verifyFV`**: Verifies that the received Freshness Value is greater than the previously stored FV, ensuring no replay attacks.


Feel free to modify the code as needed and ensure that your software integrity checks are robust for your deployment needs. Stay secure!

