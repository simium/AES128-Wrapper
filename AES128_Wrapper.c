#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/aes.h>
#include <openssl/crypto.h>

int main(int argc, char **argv)
{
    int res;
    AES_KEY AESkey;
    //unsigned char KEK[] = {0x10, 0x21, 0x32, 0x43, 0x54, 0x65, 0x76, 0x87, 0x98, 0xA9, 0xBA, 0xCB, 0xDC, 0xED, 0xFE, 0x0F};
    //unsigned char Key[] = {0x20, 0x31, 0x42, 0x53, 0x64, 0x75, 0x86, 0x97, 0xA8, 0xB9, 0xCA, 0xDB, 0xEC, 0xFD, 0x0E, 0x1F};
    unsigned char *outbuf;

    if (argc != 3)
    {
        printf("Usage: ./AES128_Wrapper MasterKey DataKey\n");
        return EXIT_FAILURE;
    }

    const char *KEK_ptr = argv[1];
    unsigned char KEK[16];

    const char *Key_ptr = argv[2];
    unsigned char Key[16];

    size_t count = 0;

    for(count = 0; count < sizeof(KEK)/sizeof(KEK[0]); count++) {
        sscanf(KEK_ptr, "%2hhx", &KEK[count]);
        KEK_ptr += 2;
    }
    for(count = 0; count < sizeof(Key)/sizeof(Key[0]); count++) {
        sscanf(Key_ptr, "%2hhx", &Key[count]);
        Key_ptr += 2;
    }

    outbuf = OPENSSL_malloc(sizeof(Key)+8);

    printf("Master key:    ");
    for (unsigned int i=0; i<sizeof(KEK); i++)
    {
        printf("%02X", KEK[i]);
    }
    printf("\n");

    printf("GUE key:       ");
    for (unsigned int i=0; i<sizeof(Key); i++)
    {
        printf("%02X", Key[i]);
    }
    printf("\n");

    if (AES_set_encrypt_key(KEK, 128, &AESkey) == 0)
    {
        res = AES_wrap_key(&AESkey, 0, outbuf, Key, sizeof(Key));

        if (res == (sizeof(Key)+8))
        {
            printf("AES-128 Wrap:  ");
            for (unsigned int i=0; i<(sizeof(Key)+8); i++)
            {
                printf("%02X", outbuf[i]);
            }
            printf("\n");
        }
        else
        {
            printf("Error wrapping key: res=%d\n", res);
            return EXIT_FAILURE;
        }
    }
    else
    {
        printf("Error setting encryption key.");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
