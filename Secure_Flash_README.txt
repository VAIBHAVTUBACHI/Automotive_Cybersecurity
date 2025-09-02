
# Secure Flashing with SHA256 Verification

This repository contains code for performing secure flashing of software onto a device by verifying its integrity using SHA256 hashing. It ensures that only the software with the correct hash is flashed onto the device, helping protect against tampered or corrupted firmware.

## Features
- **SHA256 Hashing**: Uses OpenSSL's `EVP` API to calculate SHA256 hashes of the software to verify its integrity.
- **Software Integrity Check**: Compares the hash of the incoming software against a stored hash value. If the hashes match, the software can be safely flashed; otherwise, it will reject the operation.
- **Prevention of Tampering**: Provides a simple mechanism to detect tampered firmware by comparing hashes before proceeding with any flash operation.

## How It Works
1. The software is first hashed using the SHA256 algorithm.
2. A comparison is made between the calculated hash of the software and the stored hash.
3. If the hashes match, the software is deemed secure, and the flash operation is allowed to proceed.
4. If there is a hash mismatch (indicating potential tampering), the flash process is aborted, and a warning is issued.

## Code Walkthrough

- **Hash Verification**: The `verify_sha256` function is used to compute the hash of the provided software (either the original or tampered version). This is done using OpenSSL's `EVP_Digest` functions.
  
- **Stored Hash**: The `stored_hash` represents a previously computed valid hash for the legitimate software. This hash is compared with the hash of the incoming firmware to ensure it hasn't been tampered with.

## Example Output
After running the code, the following output will be displayed, depending on whether the hashes match:
```
Calculated hash is: 
A3 7F 2C D9 4B 1E 88 6A F0 3D B7 5C 9A 0E 14 C2
6D E1 93 AF 78 05 39 CB 12 8F DA 47 60 BE 25 91
Stored hash is: 
A3 7F 2C D9 4B 1E 88 6A F0 3D B7 5C 9A 0E 14 C2
6D E1 93 AF 78 05 39 CB 12 8F DA 47 60 BE 25 91

HASH MATCHED PROCEEDING TO FLASH THE SOFTWARE .....
```

If the hashes do not match, the program will display:
```
HASH MISMATCHED XXXXXX SORRY PLEASE TRY AGAIN LATER!!
```

## Requirements
- **OpenSSL**: This code uses the OpenSSL library, which needs to be installed to handle cryptographic operations.
- **C Compiler**: A C compiler that supports OpenSSL is required to compile and run this code.

## Usage

2. **Install OpenSSL**:
    For Windows, you can follow these steps:
    - Download the OpenSSL installer from the [official OpenSSL website](https://slproweb.com/products/Win32OpenSSL.html).
    - Install OpenSSL using the installer, and make sure to add OpenSSL to your system's PATH during the installation process.
    - After installation, verify that OpenSSL is working by running `openssl version` in your command prompt.

3. **Compile the code**:
    ```bash
    gcc -o secure_flash secure_flash.c -lssl -lcrypto
    ```

4. **Run the program**:
    ```bash
    ./secure_flash
    ```


Feel free to modify the code as needed and ensure that your software integrity checks are robust for your deployment needs. Stay secure!
