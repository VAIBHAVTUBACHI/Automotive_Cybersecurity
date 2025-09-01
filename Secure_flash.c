#include<stdio.h>
#include<string.h>
#include<openssl/evp.h>

#define HASH_SIZE 32u
#define SOFTWARE_SIZE 32u
#define E_OK 1
#define E_NOT_OK 0

unsigned char software_hex[SOFTWARE_SIZE]={
    0xA3, 0x7F, 0x2C, 0xD9, 0x4B, 0x1E, 0x88, 0x6A, 
0xF0, 0x3D, 0xB7, 0x5C, 0x9A, 0x0E, 0x14, 0xC2, 
0x6D, 0xE1, 0x93, 0xAF, 0x78, 0x05, 0x39, 0xCB, 
0x12, 0x8F, 0xDA, 0x47, 0x60, 0xBE, 0x25, 0x91
};
unsigned char tampered_software_hex[SOFTWARE_SIZE]={
    0xA3, 0x7F, 0x2C, 0xD9, 0x4B, 0x1E, 0x88, 0x6A, 
0xF0, 0x3D, 0xB7, 0x5C, 0x9A, 0x0E, 0x14, 0xC2, 
0x6D, 0xE1, 0x93, 0xAF, 0x78, 0x05, 0x39, 0xCB, 
0x12, 0x8F, 0xDA, 0x47, 0x60, 0xBE, 0x25, 0x91
};

unsigned char stored_hash[HASH_SIZE];
int verify_sha256(unsigned char *data,size_t datalen,unsigned char *output_hash)
{
    EVP_MD_CTX *ctx=EVP_MD_CTX_new();
    
    // initialise the crypto job (choose algo)
    if(!EVP_DigestInit_ex(ctx,EVP_sha256(),NULL))
    {
        return E_NOT_OK;
    }
    // calculate the digest on the data
    if(!EVP_DigestUpdate(ctx,data,datalen))
    {
        return E_NOT_OK;
    }
    int hash_len=0;
    // update the digest in the variable output_hash
    if(!EVP_DigestFinal_ex(ctx,output_hash,&hash_len))
    {
        return E_NOT_OK;
    }
    EVP_MD_CTX_free(ctx);
}


int main()
{
   unsigned char calculated_hash[HASH_SIZE];
     verify_sha256(tampered_software_hex,SOFTWARE_SIZE,calculated_hash);

    printf("Calculated hash is : \n");
    for (int i=0;i<HASH_SIZE;i++)
    {
       printf("%02X",calculated_hash[i]);
    }
     verify_sha256(software_hex,SOFTWARE_SIZE,stored_hash);
    printf("\n");
    printf("stored hash is : \n");
    for (int i=0;i<HASH_SIZE;i++)
    {
       printf("%02X",stored_hash[i]);
    }
    printf("\n");
    if(memcmp(stored_hash,calculated_hash,HASH_SIZE)==0)
    {
        printf("HASH MATCHED PROCEEDING TO FLASH THE SOFTWARE .....\n");
    }
    else{
        printf("HASH MISMATCHED XXXXXX SORRY PLEASE TRY AGAIN LATER!!\n");
    }
}
