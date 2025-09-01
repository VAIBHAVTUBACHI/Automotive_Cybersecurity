#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/core_names.h>

#define AES_KEY_LEN 16
#define CMAC_LEN    16
static uint32_t FV=1,stored_FV=0;
uint32_t generateFV(uint32_t *currentFV);
uint8_t verifyFV(uint32_t *currentFV);
// 1. Generate CMAC using OpenSSL 3.0 EVP_MAC API
int GenerateCMAC(
    const unsigned char *key, size_t key_len,
    const unsigned char *data, size_t data_len,
    unsigned char *mac, size_t *mac_len
){
    EVP_MAC *mac_algo = NULL;
    EVP_MAC_CTX *ctx = NULL;
    OSSL_PARAM params[2];
    int success = 0;
    // Fetch CMAC algorithm (replaces CMAC_CTX_new)
    mac_algo = EVP_MAC_fetch(NULL, "CMAC", NULL);
    if (!mac_algo) return 0;
    // freshness value + data to calculate MAC
    uint8_t buffer[data_len+4];
    memcpy(buffer,&FV,4);
    memcpy(buffer+4,data,data_len);
 
     
    // Create MAC context
    ctx = EVP_MAC_CTX_new(mac_algo);
    if (!ctx) goto cleanup;

    // Set algorithm parameters: cipher = AES-128-CBC
    params[0] = OSSL_PARAM_construct_utf8_string("cipher", "AES-128-CBC", 0);
    params[1] = OSSL_PARAM_construct_end();

    // Init with key
    if (!EVP_MAC_init(ctx, key, key_len, params)) goto cleanup;

    // Update with Fv + data
    if (!EVP_MAC_update(ctx, buffer, data_len+4)) goto cleanup;

    // Finalize
    if (!EVP_MAC_final(ctx, mac, mac_len, CMAC_LEN)) goto cleanup;

    success = 1;

cleanup:
    EVP_MAC_CTX_free(ctx);
    EVP_MAC_free(mac_algo);
    return success;
}

// 2️. Verify CMAC
int VerifyCMAC(
    const unsigned char *key, size_t key_len,
    const unsigned char *data, size_t data_len,
    const unsigned char *recv_mac, size_t recv_mac_len
) {
    unsigned char expected_mac[CMAC_LEN];
    size_t expected_mac_len;

    if (!GenerateCMAC(key, key_len, data, data_len, expected_mac, &expected_mac_len))
        return 0;

    if (recv_mac_len != expected_mac_len)
        return 0;

    return memcmp(recv_mac, expected_mac, recv_mac_len) == 0;
}
// 3. Generate freshness (montonic counter) 
uint32_t generateFV(uint32_t *currentFV)
{
    (*currentFV)++;
    return *currentFV;
}
// 4. Verify freshness (montonic counter) 
uint8_t verifyFV(uint32_t *currentFV)
{
    if (*currentFV > stored_FV)
    {
        stored_FV=*currentFV;
        return 0;
    }
    return 1;
}
// 5. Main Function
int main() {
    const unsigned char aes_key[AES_KEY_LEN] = {
        0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe,
        0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81
    };

    const unsigned char payload[] = "AUTOSAR_SECURE_PAYLOAD";
    const unsigned char tampered_payload[]="AUTOSAR_SECURED_PAYLOAD";
    unsigned char mac[CMAC_LEN];
    size_t mac_len;
    
    // Generate CMAC
    if (!GenerateCMAC(aes_key, AES_KEY_LEN, payload, strlen((char *)payload), mac, &mac_len)) {
        printf("MAC generation failed\n");
        return 1;
    }
    else{
       //Fetches the FV from SWC
        FV = generateFV(&FV);
    }

    printf("Generated CMAC: ");
    for (size_t i = 0; i < mac_len; ++i)
        printf("%02X", mac[i]);
    printf("\n");
     printf("Freshness value is  %d\n: ",FV);
    // Verify CMAC
    if (VerifyCMAC(aes_key, AES_KEY_LEN, payload, strlen((char *)payload), mac, mac_len))
    {
     if(!verifyFV(&FV))
     {
        printf("CMAC verification ✅ successful\n");
     }
    else
    {
        printf("CMAC verification ❌ failed\n");
     }
    }
    return 0;
}
